(require libc.scm)

(define (main)
  ;; load libgtk_s7.so (create it if necessary)
  (when (or (not (defined? '*gtk*))
	    (eq? #<undefined> (*gtk* 'gtk_window_set_title)))
    (unless (file-exists? "libgtk_s7.so")
      (if (file-exists? "libgtk_s7.c")
	  (begin
	    (format *stderr* "building libgtk_s7~%")
	    (system "gcc -c libgtk_s7.c -o libgtk_s7.o -I. -fPIC `pkg-config --libs gtk+-3.0 --cflags gtk+-3.0` -lm -ldl")
	    (system "gcc libgtk_s7.o -shared -o libgtk_s7.so"))
	  (error 'no-such-file "can't find libgtk_s7.c")))
    (load "libgtk_s7.so" (define *gtk* (inlet 'init_func 'libgtk_s7_init))))

  ;; run our script displaying cpu temperatures
  (with-let (sublet *gtk* 
	      :app (GTK_APPLICATION *gtk-app*) ; from the loading environment
	      :*libc* *libc*)

    (define (temps)
      (let loop ((core 1) (lst ()))
	(let ((file-name (string-append "/sys/class/hwmon/hwmon1/temp" (number->string core) "_input")))
	  (if (file-exists? file-name)
	      (let ((temp (let-temporarily (((current-output-port) #f)) ; squelch file size complaints
			    (with-input-from-file file-name read))))
		(loop (+ core 1) (cons (* .001 temp) lst)))
	      (reverse lst)))))

    (define (update-temps data)
      (gtk_label_set_text (GTK_LABEL data) (format #f " ~{~,1F   ~}" (temps)))
      #t)

    (define (hostname) 
      (caddr ((*libc* 'uname))))

    (let ((window (gtk_application_window_new app))
	  (text (format #f " ~{~,1F   ~}" (temps))))
      (gtk_window_set_title (GTK_WINDOW window) (hostname))
      (gtk_window_set_default_size (GTK_WINDOW window) 170 40)
      (let ((label (gtk_label_new text)))
	(gtk_container_add (GTK_CONTAINER window) label)
	(g_timeout_add 1000 update-temps label)
	(gtk_widget_show label)
	(gtk_widget_show window)))))

(main)

