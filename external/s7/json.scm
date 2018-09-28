(define json->s7
  (let ()
    (define (strlet . args)            ; inlet with keys as strings
      (apply inlet (do ((p args (cddr p))
			(fields ()))
		       ((null? p)
			(reverse! fields))
		     (set! fields (cons (cadr p) 
					(cons (symbol (car p)) 
					      fields))))))
    (let ((jlet (curlet)))
      (lambda (str)
	(do ((p (open-output-string))
	     (len (length str))
	     (i 0 (+ i 1)))
	    ((= i len)
	     (let ((result (eval-string (get-output-string p) jlet))) ; jlet so that strlet is defined
	       (close-output-port p)
	       result))
	  
	  (case (str i)
	    ((#\{)                      ; {...} -> (inlet ...) via strlet above
	     (display "(strlet " p))
	    
	    ((#\[)                      ; [...] -> (vector ...)
	     (display "(vector " p))
	    
	    ((#\} #\]) 
	     (write-char #\) p))
	    
	    ((#\: #\,) 
	     (write-char #\space p))
	    
	    ((#\")
	     (let ((qpos (char-position #\" str (+ i 1))))
	       (if (not qpos)
		   (format *stderr* "no close quote: ~S ~S~%" (substring str 0 i) (substring str i)))
	       (if (char=? (str (- qpos 1)) #\\)                    ; stopgap...
		   (set! qpos (char-position #\" str (+ qpos 1))))
	       (display (substring str i (+ qpos 1)) p)
	       (set! i qpos)))
	    
	    ((#\t)                       ; true -> #t
	     (if (and (< i (- len 3))
		      (string=? (substring str i (+ i 4)) "true"))
		 (begin
		   (display "#t" p)
		   (set! i (+ i 3)))
		 (format *stderr* "bad entry: ~S~%" (substring str i))))
	    
	    ((#\n)                       ; null -> ()
	     (if (and (< i (- len 3))
		      (string=? (substring str i (+ i 4)) "null"))
		 (begin
		   (display "()" p)
		   (set! i (+ i 3)))
		 (format *stderr* "bad entry: ~S~%" (substring str i))))
	    
	    ((#\f)                       ; false -> #f
	     (if (and (< i (- len 4))
		      (string=? (substring str i (+ i 5)) "false"))
		 (begin
		   (display "#f" p)
		   (set! i (+ i 4)))
		 (format *stderr* "bad entry: ~S~%" (substring str i))))

	    (else 
	     (write-char (str i) p))))))))

;;; TODO: in the strings we need to support the 4-digit stuff (\\uxxxx I think)
;;;   (json->s7 "{\"test\" : \"a\\u1234b\"}") -> (inlet 'test "a\x1234;b")

(define* (s7->json obj (port (current-output-port)))
  (case (type-of obj)
    ((integer? float?) 
     (display obj port))

    ((string?)
     (write obj port))

    ((vector? float-vector? int-vector? byte-vector?)
     (let ((len (length obj)))
       (if (zero? len)
	   (display "[]" port)
	   (begin
	     (write-char #\[ port)
	     (do ((i 0 (+ i 1)))
		 ((= i (- len 1))
		  (s7->json (obj i) port)
		  (write-char #\] port))
	       (s7->json (obj i) port)
	       (display ", " port))))))

    ((let?)
     (let ((len (length obj)))
       (if (zero? len)
	   (display "{}" port)
	   (let ((slot-ctr 1))
	     (write-char #\{ port)
	     (for-each (lambda (slot)
			 (write (symbol->string (car slot)) port)
			 (display " : " port)
			 (s7->json (cdr slot) port)
			 (if (< slot-ctr len)
			     (display ", " port)
			     (write-char #\} port))
			 (set! slot-ctr (+ slot-ctr 1)))
		       (reverse obj))))))
    (else
     (format *stderr* "bad entry: ~S~%" obj))))


#|
;;; -------------------------------- tests --------------------------------

(display (with-output-to-string (lambda () (s7->json (vector 1 2))))) (newline) ; "[1, 2]"
(display (with-output-to-string (lambda () (s7->json (vector "asdf" #i(1 2)))))) (newline) ; "[\"asdf\", [1, 2]]"
(display (with-output-to-string (lambda () (s7->json (inlet 'a 2))))) (newline) ; "{\"a\" : 2}

(display 
 (with-output-to-string
   (lambda ()
     (s7->json (json->s7 "{\"title\": \"Person\", \"type\": \"object\"}")))))
(newline)


(write (json->s7 "{\"test\":\"a\\\\b\"}")) (newline) ; (inlet 'test "a\\b") = (#\a #\\ #\b)
(write (json->s7 "{\"test\" : \"a\tb\"}")) (newline) ; (string->list ((inlet 'test "a\x09b") 'test)) = (#\a #\tab #\b)
(write (json->s7 "{\"test\":\"a\fb\"}")) (newline)   ; (inlet 'test "a\x0cb")
(write (json->s7 "{\"test\":\"a\rb\"}")) (newline)   ; (inlet 'test "a\x0db")
(write (json->s7 "{\"test\":\"a\bb\"}")) (newline)   ; (inlet 'test "a\x08b")
(write (json->s7 "{\"test\":\"a\/b\"}")) (newline)   ; (inlet 'test "a/b")

(write (json->s7 "[123 321]")) (newline)
(write (json->s7 "{\"asdf\" : 123}")) (newline)
(write (json->s7 "{\"asdf\":123}")) (newline)
(write (json->s7 "[1 {\"asdf\" : \"fsda\"} 2]")) (newline)
(write (json->s7 "[1.2 [3 [\"asdf\"]]]")) (newline)
(write (json->s7 "[{} [] \"\"]")) (newline)

;; some examples from json-schema.org and another site -- sitepoint?
(write (json->s7 "{
    \"title\": \"Person\",
    \"type\": \"object\",
    \"properties\": {
        \"firstName\": {
            \"type\": \"string\"
        },
        \"lastName\": {
            \"type\": \"string\"
        },
        \"age\": {
            \"description\": \"Age in years\",
            \"type\": \"integer\",
            \"minimum\": 0
        }
    },
    \"required\": [\"firstName\", \"lastName\"]
}"))
(newline)

(write (json->s7 "{ \"id\": \"http://json-schema.org/geo\", \"$schema\": \"http://json-schema.org/draft-06/schema#\", \"description\": \"A geographical coordinate\", \"type\": \"object\", \"properties\": { \"latitude\": { \"type\": \"number\" }, \"longitude\": { \"type\": \"number\" } } }")) (newline)

(write (json->s7 "{ \"$schema\": \"http://json-schema.org/draft-06/schema#\", \"description\": \"A representation of a person, company, organization, or place\", \"type\": \"object\", \"required\": [\"familyName\", \"givenName\"], \"properties\": { \"fn\": { \"description\": \"Formatted Name\", \"type\": \"string\" }, \"familyName\": { \"type\": \"string\" }, \"givenName\": { \"type\": \"string\" }, \"additionalName\": { \"type\": \"array\", \"items\": { \"type\": \"string\" } }, \"honorificPrefix\": { \"type\": \"array\", \"items\": { \"type\": \"string\" } }, \"honorificSuffix\": { \"type\": \"array\", \"items\": { \"type\": \"string\" } }, \"nickname\": { \"type\": \"string\" }, \"url\": { \"type\": \"string\", \"format\": \"uri\" }, \"email\": { \"type\": \"object\", \"properties\": { \"type\": { \"type\": \"string\" }, \"value\": { \"type\": \"string\", \"format\": \"email\" } } }, \"tel\": { \"type\": \"object\", \"properties\": { \"type\": { \"type\": \"string\" }, \"value\": { \"type\": \"string\", \"format\": \"phone\" } } }, \"adr\": { \"$ref\": \"http://json-schema.org/address\" }, \"geo\": { \"$ref\": \"http://json-schema.org/geo\" }, \"tz\": { \"type\": \"string\" }, \"photo\": { \"type\": \"string\" }, \"logo\": { \"type\": \"string\" }, \"sound\": { \"type\": \"string\" }, \"bday\": { \"type\": \"string\", \"format\": \"date\" }, \"title\": { \"type\": \"string\" }, \"role\": { \"type\": \"string\" }, \"org\": { \"type\": \"object\", \"properties\": { \"organizationName\": { \"type\": \"string\" }, \"organizationUnit\": { \"type\": \"string\" } } } } } ")) (newline)

(write (json->s7 "{ \"$schema\": \"http://json-schema.org/draft-06/schema#\", \"description\": \"A representation of an event\", \"type\": \"object\", \"required\": [ \"dtstart\", \"summary\" ], \"properties\": { \"dtstart\": { \"format\": \"date-time\", \"type\": \"string\", \"description\": \"Event starting time\" }, \"dtend\": { \"format\": \"date-time\", \"type\": \"string\", \"description\": \"Event ending time\" }, \"summary\": { \"type\": \"string\" }, \"location\": { \"type\": \"string\" }, \"url\": { \"type\": \"string\", \"format\": \"uri\" }, \"duration\": { \"format\": \"time\", \"type\": \"string\", \"description\": \"Event duration\" }, \"rdate\": { \"format\": \"date-time\", \"type\": \"string\", \"description\": \"Recurrence date\" }, \"rrule\": { \"type\": \"string\", \"description\": \"Recurrence rule\" }, \"category\": { \"type\": \"string\" }, \"description\": { \"type\": \"string\" }, \"geo\": { \"$ref\": \"http://json-schema.org/geo\" } } } ")) (newline)

(write (json->s7 "{ \"$schema\": \"http://json-schema.org/draft-06/schema#\", \"description\": \"An Address following the convention of http://microformats.org/wiki/hcard\", \"type\": \"object\", \"properties\": { \"post-office-box\": { \"type\": \"string\" }, \"extended-address\": { \"type\": \"string\" }, \"street-address\": { \"type\": \"string\" }, \"locality\":{ \"type\": \"string\" }, \"region\": { \"type\": \"string\" }, \"postal-code\": { \"type\": \"string\" }, \"country-name\": { \"type\": \"string\"} }, \"required\": [\"locality\", \"region\", \"country-name\"], \"dependencies\": { \"post-office-box\": [\"street-address\"], \"extended-address\": [\"street-address\"] } } ")) (newline)

(write (json->s7 "{
    \"id\": 1,
    \"name\": \"A green door\",
    \"price\": 12.50,
    \"tags\": [\"home\", \"green\"]
}")) (newline)

(write (json->s7 "[
    {
        \"id\": 2,
        \"name\": \"An ice sculpture\",
        \"price\": 12.50,
        \"tags\": [\"cold\", \"ice\"],
        \"dimensions\": {
            \"length\": 7.0,
            \"width\": 12.0,
            \"height\": 9.5
        },
        \"warehouseLocation\": {
            \"latitude\": -78.75,
            \"longitude\": 20.4
        }
    },
    {
        \"id\": 3,
        \"name\": \"A blue mouse\",
        \"price\": 25.50,
        \"dimensions\": {
            \"length\": 3.1,
            \"width\": 1.0,
            \"height\": 1.0
        },
        \"warehouseLocation\": {
            \"latitude\": 54.4,
            \"longitude\": -32.7
        }
    }
]"))
(newline)

(write (json->s7 "{
    \"id\": \"http://some.site.somewhere/entry-schema#\",
    \"$schema\": \"http://json-schema.org/draft-06/schema#\",
    \"description\": \"schema for an fstab entry\",
    \"type\": \"object\",
    \"required\": [ \"storage\" ],
    \"properties\": {
        \"storage\": {
            \"type\": \"object\",
            \"oneOf\": [
                { \"$ref\": \"#/definitions/diskDevice\" },
                { \"$ref\": \"#/definitions/diskUUID\" },
                { \"$ref\": \"#/definitions/nfs\" },
                { \"$ref\": \"#/definitions/tmpfs\" }
            ]
        },
        \"fstype\": {
            \"enum\": [ \"ext3\", \"ext4\", \"btrfs\" ]
        },
        \"options\": {
            \"type\": \"array\",
            \"minItems\": 1,
            \"items\": { \"type\": \"string\" },
            \"uniqueItems\": true
        },
        \"readonly\": { \"type\": \"boolean\" }
    },
    \"definitions\": {
        \"diskDevice\": {
            \"properties\": {
                \"type\": { \"enum\": [ \"disk\" ] },
                \"device\": {
                    \"type\": \"string\",
                    \"pattern\": \"^/dev/[^/]+(/[^/]+)*$\"
                }
            },
            \"required\": [ \"type\", \"device\" ],
            \"additionalProperties\": false
        },
        \"diskUUID\": {
            \"properties\": {
                \"type\": { \"enum\": [ \"disk\" ] },
                \"label\": {
                    \"type\": \"string\",
                    \"pattern\": \"^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}$\"
                }
            },
            \"required\": [ \"type\", \"label\" ],
            \"additionalProperties\": false
        },
        \"nfs\": {
            \"properties\": {
                \"type\": { \"enum\": [ \"nfs\" ] },
                \"remotePath\": {
                    \"type\": \"string\",
                    \"pattern\": \"^(/[^/]+)+$\"
                },
                \"server\": {
                    \"type\": \"string\",
                    \"oneOf\": [
                        { \"format\": \"hostname\" },
                        { \"format\": \"ipv4\" },
                        { \"format\": \"ipv6\" }
                    ]
                }
            },
            \"required\": [ \"type\", \"server\", \"remotePath\" ],
            \"additionalProperties\": false
        },
        \"tmpfs\": {
            \"properties\": {
                \"type\": { \"enum\": [ \"tmpfs\" ] },
                \"sizeInMB\": {
                    \"type\": \"integer\",
                    \"minimum\": 16,
                    \"maximum\": 512
                }
            },
            \"required\": [ \"type\", \"sizeInMB\" ],
            \"additionalProperties\": false
        }
    }
}
")) (newline)


(write (json->s7 "{
  \"aliceblue\": [240, 248, 255, 1],
  \"antiquewhite\": [250, 235, 215, 1],
  \"aqua\": [0, 255, 255, 1],
  \"aquamarine\": [127, 255, 212, 1],
  \"azure\": [240, 255, 255, 1],
  \"beige\": [245, 245, 220, 1],
  \"bisque\": [255, 228, 196, 1],
  \"black\": [0, 0, 0, 1],
  \"blanchedalmond\": [255, 235, 205, 1],
  \"blue\": [0, 0, 255, 1],
  \"blueviolet\": [138, 43, 226, 1],
  \"brown\": [165, 42, 42, 1],
  \"burlywood\": [222, 184, 135, 1],
  \"cadetblue\": [95, 158, 160, 1],
  \"chartreuse\": [127, 255, 0, 1],
  \"chocolate\": [210, 105, 30, 1],
  \"coral\": [255, 127, 80, 1],
}"))
(newline)
|#
