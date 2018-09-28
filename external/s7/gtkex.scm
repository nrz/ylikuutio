;;; this is not ready for use 
(if (provided? 'gtk4)
    (gtk_init)
    (gtk_init 0 #f))

(let ((shell (gtk_window_new GTK_WINDOW_TOPLEVEL))
      (s7-prompt "s7> ")
      (return-key GDK_KEY_Return))
  
  (g_signal_connect (G_OBJECT shell) "delete_event"
		    (lambda (window event data)
		      (gtk_main_quit)
		      (exit)))
  (g_signal_connect (G_OBJECT shell) "destroy" 
		    (lambda (window data)
		      (gtk_main_quit)
		      (exit)))
  
  (gtk_window_set_title (GTK_WINDOW shell) "s7")

  (let ((scrolled_window (gtk_scrolled_window_new #f #f)))
    
    (gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW scrolled_window) GTK_POLICY_AUTOMATIC GTK_POLICY_AUTOMATIC)
    (gtk_container_add (GTK_CONTAINER shell) scrolled_window)
    
    (let* ((repl (gtk_text_view_new))
	   (repl_buf (gtk_text_buffer_new #f))
	   (prompt_not_editable #f))

      (define repl-key-press 
	(let ((evaluate-expression 
	       (lambda (expr)
		 (let ((pos (GtkTextIter))
		       (result (catch #t
				 (lambda ()
				   (object->string (eval-string expr (rootlet)))) ; default is (curlet)
				 (lambda args
				   (format #f "~A: ~S" (car args) (apply format #f (cadr args)))))))
		   (gtk_text_buffer_get_end_iter repl_buf pos)
		   (gtk_text_buffer_insert repl_buf pos "\n" 1)
		   (gtk_text_buffer_insert repl_buf pos result (length result)))))

	      (get-current-expression
	       (lambda ()
		 (let ((m (gtk_text_buffer_get_insert repl_buf))
		       (pos (GtkTextIter))
		       (previous (GtkTextIter))
		       (next (GtkTextIter))
		       (temp (GtkTextIter)))
		   (gtk_text_buffer_get_iter_at_mark repl_buf pos m)
		   (if (not (gtk_text_iter_backward_search pos s7-prompt 0 temp previous #f))
		       ""
		       (begin
			 (if (not (gtk_text_iter_forward_search pos s7-prompt 0 next temp #f))
			     (gtk_text_buffer_get_end_iter repl_buf next)
			     (begin
			       (gtk_text_iter_backward_search next "\n" 0 pos temp #f)
			       (gtk_text_iter_backward_search pos "\n" 0 next temp #f)))
			 (gtk_text_buffer_get_text repl_buf previous next #t)))))))

	  (lambda (w event data)
	    (let ((key (gtk_event_keyval event)))
	      (if (equal? key return-key)
		  (let ((pos (GtkTextIter)))
		    
		    (evaluate-expression (get-current-expression))
		    
		    (gtk_text_buffer_get_end_iter repl_buf pos)
		    (gtk_text_buffer_insert_with_tags repl_buf pos
						      (string-append (string #\newline) s7-prompt) 
						      (+ 1  (length s7-prompt))
						      (list prompt_not_editable))
		    (gtk_text_buffer_place_cursor repl_buf pos)
		    (gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW repl) 
							(gtk_text_buffer_get_insert repl_buf))
		    (g_signal_stop_emission (GPOINTER w)
					    (g_signal_lookup "key_press_event" 
							     (G_OBJECT_TYPE (G_OBJECT w))) 
					    0)))
	      #f))))
      
      (gtk_container_add (GTK_CONTAINER scrolled_window) repl)
      (gtk_text_view_set_buffer (GTK_TEXT_VIEW repl) repl_buf)
      (gtk_text_view_set_editable (GTK_TEXT_VIEW repl) #t)
      (gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW repl) GTK_WRAP_NONE)
      (gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW repl) #t)
      (gtk_text_view_set_left_margin (GTK_TEXT_VIEW repl) 4)
      
      (g_signal_connect (G_OBJECT repl) "key_press_event" repl-key-press)
      ;; TODO in gtk4 I think repl-key-press receives 2 args

      (gtk_widget_show repl)
      (gtk_widget_show scrolled_window)
      (gtk_widget_show shell)
      
      (set! prompt_not_editable 
	    (gtk_text_buffer_create_tag repl_buf "prompt_not_editable" 
					(list "editable" 0 "weight" PANGO_WEIGHT_BOLD)))
      (let ((pos (GtkTextIter)))
	(gtk_text_buffer_get_end_iter repl_buf pos)
	(gtk_text_buffer_insert_with_tags repl_buf pos 
					  s7-prompt (length s7-prompt)
					  (list prompt_not_editable)))
      (gdk_window_resize (gtk_widget_get_window shell) 400 200)
      (gtk_main))))


#|
;;; here is the calling C program:

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "s7.h"
void libgtk_s7_init(s7_scheme *sc);

int main(int argc, char **argv)
{
  s7_scheme *sc;

  sc = s7_init();  
  libgtk_s7_init(sc);

  s7_load(sc, "gtkex.scm");
}

;;; here is how I build it in linux:

gcc -c libgtk_s7.c -o libgtk_s7.o -I. -fPIC `pkg-config --libs gtk+-3.0 --cflags` -lm -ldl
gcc libgtk_s7.o -shared -o libgtk_s7.so
gcc -o gtkex gtkex.c s7.o /home/bil/cl/libgtk_s7.so -lm -I. -Wl,-export-dynamic `pkg-config --libs gtk+-3.0 --cflags` -lm -ldl

|#

