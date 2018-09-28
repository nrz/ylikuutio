(define* (show-profile (n 100))
  (let ((info (*s7* 'profile-info)))
    (if (null? info)
	(format *stderr* "no profiling data!~%")
	(let* ((entries (hash-table-entries info))
	       (vect (make-vector entries)))

	  (copy info vect)
	  (set! vect (sort! vect (lambda (a b) (> (cadr a) (cadr b)))))

	  (do ((total 0)
	       (i 0 (+ i 1)))
	      ((= i entries)
	       (format *stderr* "total calls: ~A~%" total)) 
	    (set! total (+ total (cadr (vector-ref vect i)))))
	  
	  (set! n (min n entries))
	  (do ((i 0 (+ i 1)))
	      ((= i n) 
	       (newline *stderr*))
	    (let ((data (vect i)))
	      (let ((expr (caddr data))
		    (count (cadr data))
		    (key (car data))
		    (func (cdddr data)))
		(let ((file (profile-filename key))
		      (line (profile-line-number key)))
		  (if (> line 0)
		      (format *stderr* "~A:~8T~A ~24T~A[~A]: ~48T~A~%" 
			      count 
			      (if (string? func)
				  (format #f " ~A" func)
				  "")
			      file line
			      (if (> (length expr) 60)
				  (string-append (substring expr 0 56) " ...")
				  expr)))))))))))

#|
(define old-version s7-version)
(define (s7-version)
  (show-profile)
  (old-version))
|#
