;;; various #i #e #d and funny exponent tests
;;; these no longer work in s7

(format *stderr* "old-numbers...~%")

(test (eqv? #i3/5 #i3/5) #t)
(test (eqv? #e0.6 #e0.6) #t)

(test (case 1.0 ((#i1) 2) ((1e0) 3) ((1.0) 4) (else 5)) 2)
(test (case 1 ((#i1) 2) ((1e0) 3) ((1.0) 4) (else 5)) 5)

;(num-test (string->number "#e#t11.3") 53/4)
;(num-test (string->number "#t#e1.5") 17/12)
;(num-test (string->number "#i#t1a") 22.0)
;(num-test (string->number "#t#i1a") 22.0) ; ??? this is analogous to #x#i1a = 26.0

(when with-bignums
  (num-test (max 12345678901234567890 12345678901234567891) 12345678901234567891)
  (num-test (max 9223372036854776/9223372036854775807 #i9223372036854775/9223372036854775000) 1.000000000000000020925101928970235578612E-3)
  (num-test (max #i9223372036854776/9223372036854775807 9223372036854775/9223372036854775000) 1.000000000000000020925101928970235578612E-3)
  (num-test (max #i92233720368547757/9223372036854775807 92233720368547758/9223372036854775807) 9.999999999999999992410584792601468961145E-3)
  (num-test (max 92233720368547757/9223372036854775807 #i92233720368547758/9223372036854775807) 9.999999999999999992410584792601468961145E-3)
  
  ;; in these cases, the non-gmp s7 can't win:
  ;;    :(max 9223372036854776/9223372036854775807 #i9223372036854775/9223372036854775000)
  ;;    9223372036854776/9223372036854775807
  ;;    :(max #i9223372036854776/9223372036854775807 9223372036854775/9223372036854775000)
  ;;    0.001
  ;;    :(max #i92233720368547757/9223372036854775807 92233720368547758/9223372036854775807)
  ;;    0.01
  ;;    :(max 92233720368547757/9223372036854775807 #i92233720368547758/9223372036854775807)
  ;;    92233720368547757/9223372036854775807
  )

(test (= #i3/5 #i3/5) #t)

(test (string->number "#i") #f)
(test (string->number "#e") #f)
(num-test (string->number "#i1@01" 16) 16.0)
(num-test (string->number "#d.0@-11" 10) 0.0)
(num-test (string->number "#i+1@002" 10) 100.0)
(test (= #i3/5 (string->number "#i3/5")) #t)

(when with-bignums
  (test (number? (string->number "#e1.0e564")) #t)
  (test (number? (string->number "#e1.0e307")) #t)
  (test (number? (string->number "#e1.0e310")) #t)
  (num-test (string->number "#e1624540914719833702142058941") 1624540914719833702142058941)
  (num-test (string->number "#i1624540914719833702142058941") 1.624540914719833702142058941E27)
  (num-test (string->number "#e8978167593632120808315265/5504938256213345873657899") 8978167593632120808315265/5504938256213345873657899)
  (num-test (string->number "#i8978167593632120808315265/5504938256213345873657899") 1.630929753571457437099527114342760854299E0)
  (num-test (string->number "#i119601499942330812329233874099/12967220607") 9.223372036854775808414213562473095048798E18)
  ;; this next test needs more bits to compare with other schemes -- this is the result if 128 bits
  (num-test (string->number "#e005925563891587147521650777143.74135805596e05") 826023606487248364518118333837545313/1394)
  (num-test (string->number "#e-1559696614.857e28") -15596966148570000000000000000000000000)
  (test (integer? (string->number "#e1e310")) #t)
  (test (number? (string->number "#e1.0e310")) #t))
;; in the non-gmp case #e1e321 is a read error -- should s7 return NaN silently?

(when (not with-bignums)
  (test (string->number "#e1e307") #f)
  (test (eval-string "(number? #e1.0e564)") 'error)
  (test (string->number "#e005925563891587147521650777143.74135805596e05") #f)
  (test (string->number "#e78.5e65") #f)
  (test (string->number "#e1e543") #f)
  (test (string->number "#e120d21") #f)
  (test (string->number "#e-2.2e021") #f)
  (if (provided? '@-exponent)
      (test (infinite? (string->number "9221.@9129" 10)) #t))
  (test (string->number "#e120@21" 12) #f)
  (test (string->number "#d#e120@21") #f)
  (test (string->number "#b#e120@21") #f)
  (test (string->number "#e#b120@21") #f)
  (test (string->number "#e#d120@21") #f)
  (test (nan? (string->number "0f0/00" 16)) #t)
  (test (string->number "#e-1559696614.857e28") #f)
  (test (string->number "#e1+1i") #f)
  (test (= 0 00 -000 #e-0 0/1 #e#x0 #b0000 #e#d0.0 -0 +0) #t))

(num-test #i1.0e8 100000000.0)

(test (string->number "#b#i0/0") #f)
(test (string->number "#b#e0/0") #f)
(test (string->number "#b#e1/0+i") #f) ; inf+i?
(test (string->number "#e#b0/0") #f)
(test (string->number "#i#b0/0") #f)
(test (string->number "#e0/0") #f)
(test (number? (string->number "#i0/0")) #t) ; nan since (number? 0/0) is #t
(test (string->number "#e#b1/0") #f)
(test (string->number "#i#b1/0") #f)
(test (string->number "#e1/0") #f)
(test (number? (string->number "#i1/0")) #t)
(test (string->number "#e#b1/0+i") #f)
(test (string->number "#i#b1/0+i") #f) ; inf+i?
(test (string->number "#e1/0+i") #f)
(test (number? (string->number "#i1/0+i")) #t) 
(test (number? (string->number "#i0/0+i")) #t) 
(test (nan? #i0/0) #t) ; but #i#d0/0 is a read error?

(num-test (string->number "#b#e11e30") 3221225472) ; very confusing!
(num-test (string->number "#b#i11e30") 3221225472.0)
(num-test (string->number "#e#b11e30") 3221225472) 
(num-test (string->number "#i#b11e30") 3221225472.0)
(num-test (string->number "#b#e+1e+1+0e+10i") 2)
(num-test (string->number "#e+.0e-00-0i") 0)
(num-test (string->number "#e-0/1110010") 0)
(num-test (string->number "#x#e00110e") 4366)
(num-test (string->number "#e#x-e/001") -14)
(num-test (string->number "#e.001e-11") 0)
(num-test (string->number "#x#e00/00e") 0)
(num-test (string->number "#e#x+1e.01e10100") 65366158/2178339)
(num-test (string->number "#i#x0e10-000i") 3600.0)
(num-test (string->number "#x0/e010-e/1i") 0-14i)
(num-test (string->number "#i-1/1-1.0e1i") -1-10i)
(num-test (string->number "#e#x001ee11e1") 32379361)
(num-test (string->number "#e#x010e10.e1") 17699041/256)
(num-test #b#i.110e-1 0.375)
(num-test #e01.1e1+00.i 11)

(when (provided? 'dfls-exponents)
  (num-test (string->number "#d.0d1+i") 0+1i)
  (num-test (string->number "+.0d-1+i") 0+1i)
  (num-test (string->number "#d1d+0-1d-1i") 1-0.1i)
  (num-test (string->number "#i+1+0.d-0i") 1.0)
  (num-test (string->number "#o#i-101d+0") -65.0)
  (num-test (string->number "+001.110d+1") 11.1)
  (num-test (string->number "#e01+0d000i") 1)
  (num-test (string->number "#d1d0-0.d0i") 1.0)
  (num-test (string->number "#d#i001d+00") 1.0)
  (num-test (string->number "#o0010111/1") 4169)
  (num-test (string->number "0d00-0.d+0i") 0.0)
  (num-test (string->number "#o1.d0+10.d00i") 1+8i)
  (num-test (string->number "0d+01+1e+1i") 0+10i)
  (num-test (string->number "10.d-005" 2) 0.0625)
  (num-test (string->number "+7f2-73i" 8) 448-59i))

(num-test (string->number "#i#d1e1+.0i") 10.0)
(num-test (string->number "#i#d+1e+1+1e+1i") 10+10i)
(test (string->number "#e+1e+1+1e+1i") #f)
;; these depend on rationalize's default error I think
;; and they cause valgrind to hang!!
;;(num-test (string->number "#e.1e-11") 0)
;;(num-test (string->number "#e1e-12") 0)
(num-test (string->number "#e1e-11") 1/90909090910)
(test (string->number "#e#f1") #f)

(when with-bignums
  (test (= (string->number "#e1e19") (string->number "#e.1e20")) #t)
  (test (= (string->number "#e1e19") (* 10 (string->number "#e1e18"))) #t)
  (test (= (string->number "#e1e20") (* 100 (string->number "#e1e18"))) #t)
  (num-test (string->number "#b#e-11e+111") -7788445287802241442795744493830144)
  (num-test (string->number "#i#b-11e+111") -7.788445287802241442795744493830144E33)
  (num-test (string->number "#b#i-11e+111") -7.788445287802241442795744493830144E33)
  (num-test (string->number "#i3e+111") 3.0e111)
  (num-test (string->number "#e3e30") 3000000000000000000000000000000)
  (num-test (string->number "#i3e30") 3.000E30)
  (num-test (string->number "#b#e11e80") 3626777458843887524118528)
  (num-test (string->number "#b#i11e80") 3626777458843887524118528.0)
  (num-test (string->number "#e#b11e80") 3626777458843887524118528)
  (num-test (string->number "#i#b11e80") 3626777458843887524118528.0))

(test (= #i1e19 #i.1e20) #t)
(num-test #b#e-.1 -1/2)
(num-test #o#e-.1 -1/8)
(num-test #d#e-.1 -1/10)
(num-test #x#e-.1 -1/16)
(num-test #b#e1.1e2 6)
(num-test #o#e1.1e2 72)
(num-test #d#e1.1e2 110)
(num-test #b#i-1.1e-2 -0.375)
(num-test #o#i-1.1e-2 -0.017578125)
(num-test #d#i-1.1e-2 -0.011)
(num-test #e#b1e-10 1/1024)
(num-test #e#b+1.1 3/2)
(num-test #e#o+1.1 9/8)
(num-test #e#d+1.1 11/10)
(num-test #e#x+1.1 17/16)
(num-test #e#b+1.1e+2 6)
(num-test #e#o+1.1e+2 72)
(num-test #e#d+1.1e+2 110)
(num-test #i#b.001 0.125)
(num-test #i#b000000000011 3.0)
(num-test #i#b-000000000011e1 -6.0)
(num-test #i#b-000000000011e+11 -6144.0)
;;(num-test #b#e0+i 0+1i)    ; these 2 are now read-errors (#e0+i is an error because inexact->exact does not accept complex args in s7)
;;(num-test #b#e0+1.1i 0+1.5i) 
(test (string->number "#b#e0+i") #f)
(num-test #i#xf/c 1.25)
(num-test #e#x1.4 5/4)
(num-test #e2/3 2/3)
(num-test #b#e+.1e+1 1)
(num-test #b#e.011-0.i 3/8)
(num-test #b#i1.1e0-.0i 1.5)
(num-test #b#e1.1e0-.0i 3/2)
(num-test #b#e-1.00e+001 -2)
(num-test #b#e+.01011100 23/64)
(num-test #b#i-00-0/001i 0.0)
(num-test #e#x1234/12 (string->number "#x#e1234/12"))
(num-test #x#e.1 #e#x.1)

(num-test #e-.0 0)
(num-test #e-123.0 -123)
(num-test #i-123 -123.0)
(num-test #e+123.0 123)
(num-test #i+123 123.0)
(num-test #i-0 0.0)
(num-test #e-0.0 0)
;;; in guile #e1e-10 is 7737125245533627/77371252455336267181195264

(num-test #d#i1/10 #i#d1/10)

(num-test #b#i0-0i 0.0)
(num-test #b#e1e01 2)
(num-test #b#e1e-0 1)
(num-test #b#e11e-1 3/2)
;;(num-test #b#e-0/1+i 0+1i)
(test (string->number "#b#e-1/1+01.1e1i") #f)
(test (string->number "#d#i0/0") #f)
(test (string->number "#i#x0/0") #f)
(test (exact? #i#b1) #f)
(test (exact? #e#b1) #t)
(num-test #x#e1.5 21/16)
(num-test #x#i3 3.0)

(test (exact? #i1) #f)
(test (exact? #e1.0) #t)
(test (exact? #i1.0) #f)
(test (exact? #e1) #t)

(num-test #x#if 15.0)
(num-test #i1/1 1.0)
(test (< (abs (- #i3/2 1.5)) 1e-12) #t)
(test (< (abs (- #i1 1.0)) 1e-12) #t)
(test (< (abs (- #i-1/10 -0.1)) 1e-12) #t)
(test (< (abs (- #i1.5 1.5)) 1e-12) #t)

(when (provided? 'dfls-exponents)
  (num-test (string->number "#i1s0") 1.0) ; need the s->n to avoid confusing reader in non-dfls case
  (num-test -0d-0 0.0)
  (num-test +1d+1 10.0)
  (num-test +1s00 1.0))

(num-test (string->number "#i-0.e11" 2) 0.0)
(num-test (string->number "#i+9/9" 10) 1.0)
(num-test (string->number "#e9e-999" 10) 0)
(num-test (string->number "#e-9.e-9" 10) -1/111098767)
(num-test (string->number "#e-.9e+9" 10) -900000000)
(num-test (string->number "#e-.9e+9" 10) -900000000)
(num-test #e+32/1-0.i 32)
(num-test #e+32.-0/1i 32)
(num-test #e-32/1+.0i -32)
(num-test #e+2.-0/31i 2)
(num-test #b#e.01 1/4)
(num-test #e#b.01 1/4)
(num-test #b#e10. 2)
(num-test #e#b10. 2)
(num-test #b#e0.e11 0)
(num-test #b#e1.e10 1024)
(num-test #b#e-0.e+1 0)
(num-test #b#e+.1e-0 1/2)
(num-test #b#e+1.e-0 1)
(num-test #b#e-1.e+0 -1)

(num-test (string->number "#e87" 16) 135)
(num-test (string->number "#e87" 10) 87)
(num-test (string->number "#e#x87" 10) 135)
(num-test (string->number "#e#x87" 16) 135)
(num-test (string->number "#x#e87" 10) 135)
(num-test (string->number "#i87" 16) 135.0)
(num-test (string->number "#i87" 12) 103.0)
(num-test (string->number "#ee" 16) 14)
(num-test (string->number "#if" 16) 15.0)

(num-test (string->number "#e10.01" 2) 9/4)
(num-test (string->number "#e10.01" 6) 217/36)
(num-test (string->number "#e10.01" 10) 1001/100)
(num-test (string->number "#e10.01" 14) 2745/196)
(num-test (string->number "#i10.01" 2) 2.25)
(num-test (string->number "#i10.01" 6) 6.0277777777778)
(num-test (string->number "#i10.01" 10) 10.01)
(num-test (string->number "#i10.01" 14) 14.005102040816)
(num-test (string->number "#i-.c2e9" 16) -0.76136779785156)

(num-test (string->number "#i\x32\x38\x36") 286.0)
(let ((string->number-2 (lambda (str radix)
			  (let ((old-str (if (string? str) (string-copy str) str)))
			    (let ((val (string->number str radix)))
			      (if (not (string=? str old-str))
				  (error 'string->number-messed-up)
				  val)))))
      (string->number-1 (lambda (str)
			  (let ((old-str (if (string? str) (string-copy str) str)))
			    (let ((val (string->number str)))
			      (if (not (string=? str old-str))
				  (error 'string->number-messed-up)
				  val))))))
  (test (string->number-1 "#i1-1ei") #f)
  (test (string->number-1 "#i-2e+i") #f)
  (test (string->number-1 "#i1+i1i") #f)
  (test (string->number-1 "#i1+1") #f)
  (test (string->number-1 "#i2i.") #f)
  (num-test (string->number-1 "#x#e-2e2") -738))

(do ((i 0 (+ i 1)))
    ((= i 30))
  (for-each
   (lambda (lst)
     (for-each
      (lambda (str)
	(let ((val (catch #t (lambda () (string->number str)) (lambda args 'error))))
	  (if (or (not (number? val))
		  (> (abs (- val 1.0)) 1.0e-15))
	      (format-logged #t ";(string->number ~S) = ~A?~%" str val))))
      lst))
   (list
    (list "1")
    
    (list "01" "+1" "1.")
    
    (list "001" "+01" "#e1" "#i1" "1/1" "#b1" "#x1" "#d1" "#o1" "1.0" "1e0" "9/9" "01." "+1." "1E0")
    
    (list "0001" "+001" "#e01" "#i01" "1/01" "#b01" "#x01" "#d01" "#o01" "#e+1" "#i+1" "#b+1" "#x+1" "#d+1" "#o+1" ".1e1" "01/1" "+1/1" "1.00" "1e00" "01.0" "+1.0" "1e+0" "1e-0" "01e0" "+1e0" "1.e0" "9/09" "09/9" "+9/9" "001." "+01." "#e1." "#i1." "1+0i" "1-0i" "#d1.")
    
    (list "11/11" "00001" "+0001" "#e001" "#i001" "1/001" "#b001" "#x001" "#d001" "#o001" "#e+01" "#i+01" "#b+01" "#x+01" "#d+01" "#o+01" ".1e01" "01/01" "+1/01" "91/91" ".1e+1" "10e-1" "0.1e1" "+.1e1" ".10e1" "#b#e1" "#x#e1" "#d#e1" "#o#e1" "#b#i1" "#x#i1" "#d#i1" "#o#i1" "001/1" "+01/1" "#e1/1" "#i1/1" "#b1/1" "#x1/1" "#d1/1" "#o1/1" "#e#b1" "#i#b1" "#e#x1" "#i#x1" "#e#d1" "#i#d1" "#e#o1" "#i#o1" "10/10" "1.000" "1e000" "01.00" "+1.00" "1e+00" "1e-00" "01e00" "+1e00" "1.e00" "90/90" "001.0" "+01.0" "#e1.0" "#i1.0" "01e+0" "+1e+0" "1.e+0" "01e-0" "+1e-0" "1.e-0" "001e0" "+01e0" "#e1e0" "#i1e0" "1.0e0" "01.e0" "+1.e0" "19/19" "9/009" "09/09" "+9/09" "99/99" "009/9" "+09/9" "#e9/9" "#i9/9" "#x9/9" "#d9/9" "0001." "+001." "#e01." "#i01." "#e+1." "#i+1." "#xe/e" "1+00i" "1-00i" "1+.0i" "1-.0i" "01+0i" "+1+0i" "1.+0i" "01-0i" "+1-0i" "1.-0i" "1+0.i" "1-0.i" "#xb/b" "#xd/d" "#xf/f")
    
    ;; remove "9":
    
    (list "11/011" "011/11" "+11/11" "000001" "+00001" "#e0001" "#i0001" "1/0001" "#b0001" "#x0001" "#d0001" "#o0001" "#e+001" "#i+001" "#b+001" "#x+001" "#d+001" "#o+001" ".1e001" "01/001" "+1/001" ".1e+01" "10e-01" "0.1e01" "+.1e01" ".10e01" "#b#e01" "#x#e01" "#d#e01" "#o#e01" "#b#i01" "#x#i01" "#d#i01" "#o#i01" "001/01" "+01/01" "#e1/01" "#i1/01" "#b1/01" "#x1/01" "#d1/01" "#o1/01" "#e#b01" "#i#b01" "#e#x01" "#i#x01" "#e#d01" "#i#d01" "#e#o01" "#i#o01" "0.1e+1" "+.1e+1" ".10e+1" "#b#e+1" "#x#e+1" "#d#e+1" "#o#e+1" "#b#i+1" "#x#i+1" "#d#i+1" "#o#i+1" "#e#b+1" "#i#b+1" "#e#x+1" "#i#x+1" "#e#d+1" "#i#d+1" "#e#o+1" "#i#o+1" "010e-1" "+10e-1" "10.e-1" "00.1e1" "+0.1e1" "#e.1e1" "#i.1e1" "0.10e1" "+.10e1" ".100e1" "0001/1" "+001/1" "#e01/1" "#i01/1" "#b01/1" "#x01/1" "#d01/1" "#o01/1" "#e+1/1" "#i+1/1" "#b+1/1" "#x+1/1" "#d+1/1" "#o+1/1" "10/010" "010/10" "+10/10" "1.0000" "1e0000" "01.000" "+1.000" "1e+000" "1e-000" "01e000" "+1e000" "1.e000" "001.00" "+01.00" "#e1.00" "#i1.00" "01e+00" "+1e+00" "1.e+00" "01e-00" "+1e-00" "1.e-00" "001e00" "+01e00" "#e1e00" "#i1e00" "1.0e00" "01.e00" "+1.e00" "0001.0" "+001.0" "#e01.0" "#i01.0" "#e+1.0" "#i+1.0" "001e+0" "+01e+0" "#e1e+0" "#i1e+0" "1.0e+0" "01.e+0" "+1.e+0" "001e-0" "+01e-0" "#e1e-0" "#i1e-0" "1.0e-0" "01.e-0" "+1.e-0" "0001e0" "+001e0" "#e01e0" "#i01e0" "#e+1e0" "#i+1e0" "1.00e0" "01.0e0" "+1.0e0" "001.e0" "+01.e0" "#e1.e0" "#i1.e0" "00001." "+0001." "#e001." "#i001." "#e+01." "#i+01." "#xe/0e" "#x0e/e" "#x+e/e" "1+0e1i" "1-0e1i" "1+0/1i" "1-0/1i" "1+000i" "1-000i" "1+.00i" "1-.00i" "01+00i" "+1+00i" "1.+00i" "01-00i" "+1-00i" "1.-00i" "1+0.0i" "1-0.0i" "01+.0i" "+1+.0i" "1.+.0i" "01-.0i" "+1-.0i" "1.-.0i" "001+0i" "+01+0i" "#e1+0i" "#i1+0i" "1/1+0i" "1.0+0i" "1e0+0i" "01.+0i" "+1.+0i" "001-0i" "+01-0i" "#e1-0i" "#i1-0i" "1/1-0i" "1.0-0i" "1e0-0i" "01.-0i" "+1.-0i" "1+0e0i" "1-0e0i" "1+00.i" "1-00.i" "01+0.i" "+1+0.i" "1.+0.i" "01-0.i" "+1-0.i" "1.-0.i" "#xb/0b" "#x0b/b" "#x+b/b" "#xd/0d" "#x0d/d" "#x+d/d" "#xf/0f" "#x0f/f" "#x+f/f")
    
    (list "111/111" "11/0011" "011/011" "+11/011" "0011/11" "+011/11" "#e11/11" "#i11/11" "#b11/11" "#x11/11" "#d11/11" "#o11/11" "101/101" "0000001" "+000001" "#e00001" "#i00001" "1/00001" "#b00001" "#x00001" "#d00001" "#o00001" "#e+0001" "#i+0001" "#b+0001" "#x+0001" "#d+0001" "#o+0001" ".1e0001" "01/0001" "+1/0001" ".1e+001" "10e-001" "0.1e001" "+.1e001" ".10e001" "#b#e001" "#x#e001" "#d#e001" "#o#e001" "#b#i001" "#x#i001" "#d#i001" "#o#i001" "001/001" "+01/001" "#e1/001" "#i1/001" "#b1/001" "#x1/001" "#d1/001" "#o1/001" "#e#b001" "#i#b001" "#e#x001" "#i#x001" "#e#d001" "#i#d001" "#e#o001" "#i#o001" "0.1e+01" "+.1e+01" ".10e+01" "#b#e+01" "#x#e+01" "#d#e+01" "#o#e+01" "#b#i+01" "#x#i+01" "#d#i+01" "#o#i+01" "#e#b+01" "#i#b+01" "#e#x+01" "#i#x+01" "#e#d+01" "#i#d+01" "#e#o+01" "#i#o+01" "010e-01" "+10e-01" "10.e-01" "1.00000" "1e00000" "01.0000" "+1.0000" "1e+0000" "1e-0000" "01e0000" "+1e0000" "1.e0000" "001.000" "+01.000" "#e1.000" "#i1.000" "#d1.000" "01e+000" "+1e+000" "1.e+000" "01e-000" "+1e-000" "1.e-000" "001e000" "+01e000" "#e1e000" "#i1e000" "#d1e000" "1.0e000" "+1.e000" "0001.00" "+001.00" "#e01.00" "#i01.00" "#d01.00" "#e+1.00" "#i+1.00" "#d+1.00" "001e+00" "+01e+00" "#e1e+00" "#i1e+00" "#d1e+00" "1.0e+00" "01.e+00" "+1.e+00" "001e-00" "+01e-00" "#e1e-00" "#i1e-00" "#d1e-00" "1.0e-00" "01.e-00" "+1.e-00" "000001." "+00001." "#e0001." "#i0001." "#d0001." "#e+001." "#i+001." "#d+001." "#d#e01." "#d#i01." "#e#d01." "#i#d01." "#d#e+1." "#d#i+1." "#e#d+1." "#i#d+1." "#x1e/1e" "#xe/00e" "#x0e/0e" "#x+e/0e" "#xee/ee" "#x00e/e" "#x+0e/e" "#x#ee/e" "#x#ie/e" "#e#xe/e" "#i#xe/e" "#xbe/be" "#xde/de" "1+0e11i" "1-0e11i" "1+0/11i" "1-0/11i" "1+0e01i" "1-0e01i" "1+0/01i" "1-0/01i" "1+0e+1i" "1-0e+1i" "1+0e-1i" "1-0e-1i" "1+00e1i" "1-00e1i" "1+.0e1i" "1-.0e1i" "01+0e1i" "+1+0e1i" "1.+0e1i" "01-0e1i" "+1-0e1i" "1.-0e1i" "1+0.e1i" "1-0.e1i" "1+00/1i" "1-00/1i" "01+0/1i" "+1+0/1i" "1.+0/1i" "01-0/1i" "+1-0/1i" "1.-0/1i" "1+0e10i" "1-0e10i" "1+0/10i" "1-0/10i" "1+0000i" "1-0000i" "1+.000i" "1-.000i" "01+000i" "+1+000i" "1.+000i" "01-000i" "+1-000i" "1.-000i" "1+0.00i" "1-0.00i" "01+.00i" "+1+.00i" "1.+.00i" "01-.00i" "+1-.00i" "1.-.00i" "001+00i" "+01+00i" "#e1+00i" "#i1+00i" "1/1+00i" "#b1+00i" "#x1+00i" "#d1+00i" "#o1+00i" "1.0+00i" "1e0+00i" "01.+00i" "+1.+00i" "001-00i" "+01-00i" "#e1-00i" "#i1-00i" "1/1-00i" "#b1-00i" "#x1-00i" "#d1-00i" "#o1-00i" "1.0-00i" "1e0-00i" "01.-00i" "+1.-00i" "1+0e00i" "1-0e00i" "1+00.0i" "1-00.0i" "01+0.0i" "+1+0.0i" "1.+0.0i" "01-0.0i" "+1-0.0i" "1.-0.0i" "001+.0i" "+01+.0i" "#e1+.0i" "#i1+.0i" "1/1+.0i" "#d1+.0i" "1.0+.0i" "1e0+.0i" "01.+.0i" "+1.+.0i" "001-.0i" "+01-.0i" "#e1-.0i" "#i1-.0i" "1/1-.0i" "#d1-.0i" "1.0-.0i" "1e0-.0i" "01.-.0i" "+1.-.0i" "0001+0i" "+001+0i" "#e01+0i" "#i01+0i" "1/01+0i" "#b01+0i" "#x01+0i" "#d01+0i" "#o01+0i" "#e+1+0i" "#i+1+0i" "#b+1+0i" "#x+1+0i" "#d+1+0i" "#o+1+0i" ".1e1+0i" "01/1+0i" "+1/1+0i" "1.00+0i" "1e00+0i" "01.0+0i" "+1.0+0i" "1e+0+0i" "1e-0+0i" "01e0+0i" "+1e0+0i" "1.e0+0i" "001.+0i" "+01.+0i" "#e1.+0i" "#i1.+0i" "#d1.+0i" "1+0e+0i" "1-0e+0i" "0001-0i" "+001-0i" "#e01-0i" "#i01-0i" "1/01-0i" "#b01-0i" "#x01-0i" "#d01-0i" "#o01-0i" "#e+1-0i" "#i+1-0i" "#b+1-0i" "#x+1-0i" "#d+1-0i" "#o+1-0i" ".1e1-0i" "01/1-0i" "+1/1-0i" "1.00-0i" "1e00-0i" "01.0-0i" "+1.0-0i" "1e+0-0i" "1e-0-0i" "01e0-0i" "+1e0-0i" "1.e0-0i" "001.-0i" "+01.-0i" "#e1.-0i" "#i1.-0i" "#d1.-0i" "1+0e-0i" "1-0e-0i" "1+00e0i" "1-00e0i" "1+.0e0i" "1-.0e0i" "01+0e0i" "+1+0e0i" "1.+0e0i" "01-0e0i" "+1-0e0i" "1.-0e0i" "1+0.e0i" "1-0.e0i"	"1+000.i" "1-000.i" "01+00.i" "+1+00.i" "1.+00.i" "01-00.i" "+1-00.i" "1.-00.i" "001+0.i" "+01+0.i" "#e1+0.i" "#i1+0.i" "1/1+0.i" "#d1+0.i" "1.0+0.i" "1e0+0.i" "+1.+0.i" "001-0.i" "+01-0.i" "#e1-0.i" "#i1-0.i" "1/1-0.i" "#d1-0.i" "1.0-0.i" "1e0-0.i" "01.-0.i" "+1.-0.i" "#xb/00b" "#x0b/0b" "#x+b/0b" "#xeb/eb" "#x00b/b" "#x+0b/b" "#x#eb/b" "#x#ib/b" "#e#xb/b" "#i#xb/b" "#xbb/bb" "#xdb/db" "#xd/00d" "#x0d/0d" "#x+d/0d" "#xed/ed")
    
;;; selected ones...
    
    (list "#i+11/011" "+101/0101" "#o#e11/11" "#d+11/011" "#e1/0001" "#e#b+001" "#e10e-1"
	  "#x#e1/001" "000000001" "#i+.1e+01" "#d+.1e+01" "00.10e+01" "+0.10e+01" "#e.10e+01" "#i.10e+01" "#d.10e+01"
	  "#e.10e+01" "#i10.0e-01" "+010.e-01" "#e10.e-01" "#e00.1e01" "#e#d.1e01" "#i#d1e0+0e0i" 
	  "#e#d10e-1+0e-2i" "#e#d1e0+0e-2i" "#i#d+0.001e+03+0.0e-10i" "#i#d+1/1-0/1i"
	  )
    )))
  
(for-each
 (lambda (str)
   (let ((val (catch #t (lambda () (string->number str)) (lambda args 'error))))
     (if (or (not (number? val))
	     (= val 1))
	 (format-logged #t ";(string->number ~S = ~A?~%" str val))))
 (list "011e0" "11e-00" "00.e01-i" "+10e10+i" "+1.110+i" "10011-0i" "-000.111" "0.100111" "-11.1111" "10.00011" "110e00+i" 
       "1e-011+i" "101001+i" "+11e-0-0i" "11+00e+0i" "-11101.-i" "1110e-0-i"))

(for-each
 (lambda (str)
   (test (string->number str) #f)) ; an error but string->number is not supposed to return an error -- just #f or a number
 (list "#e1+i" "#e1-i" "#e01+i" "#e+1+i" "#e1.+i" "#e01-i" "#e+1-i" "#e1.-i" "#e1+1i" "#e1-1i"))

(num-test (let ((0- 1) (1+ 2) (-0+ 3) (1e 4) (1/+2 5) (--1 6)) (+ 0- 1+ -0+ 1e 1/+2 --1)) 21)

(for-each
 (lambda (str)
   (let ((val (catch #t (lambda () (string->number str)) (lambda args 'error))))
     (if val ;(number? val)
	 (format-logged #t ";(string->number ~S) = ~A?~%" str val))))
 (list "#b#e#e1" "#x#e#e1" "#d#e#e1" "#o#e#e1" "#b#i#e1" "#x#i#e1" "#d#i#e1" "#o#i#e1" "#e#b#e1" "#i#b#e1" "#e#x#e1" "#i#x#e1" 
       "#e#d#e1" "#i#d#e1" "#e#o#e1" "#i#o#e1" "#e#b#i1" "#e#x#i1" "#e#d#i1" "#e#o#i1" "#b#e#b1" "#x#e#b1" "#d#e#b1" "#o#e#b1" 
       "#b#i#b1" "#x#i#b1" "#d#i#b1" "#o#i#b1" "#b#e#x1" "#x#e#x1" "#d#e#x1" "#o#e#x1" "#b#i#x1" "#x#i#x1" "#d#i#x1" "#o#i#x1" 
       "#b#e#d1" "#x#e#d1" "#d#e#d1" "#o#e#d1" "#b#i#d1" "#x#i#d1" "#d#i#d1" "#o#i#d1" "#b#e#o1" "#x#e#o1" "#d#e#o1" "#o#e#o1" 
       "#b#i#o1" "#x#i#o1" "#d#i#o1" "#o#i#o1"  
       
       "+1ei" "-1ei" "+0ei" "-0ei" "+1di" "-1di" "+0di" "-0di" "+1fi" "-1fi" "+0fi" "-0fi" "0e-+i" "1d-+i" 
       "0d-+i" "1f-+i" "0f-+i" "1e++i" "0e++i" "1d++i" ".10-10." "-1.e++i" "0e--01i" "1-00." "0-00." "#xf+b" 
       "#x1+d" "0f++1i" "1+0d-i" ".0f--i" "1-0d-i" "#xe-ff" "0-" "0-e0"
       
       "-#b1" "#b.i" "#b+i" "#b1e.1" "#b1+1" "#b#e#e1" "#b#ee1" "#b#e0e" "#d#d1" "#d#1d1"
       "#b+1ei" "#b-1ei" "#b+0ei" "#b-0ei" "#b+1di" "#b-1di" "#b+0di" "#b-0di" "#b+1fi" "#b-1fi" "#b+0fi" "#b-0fi" "#b0e-+i" "#b1d-+i" 
       ))
(num-test #i00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001/00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 1.0)

(test (cadr '(1 .#d2)) '.#d2)

(when (provided? 'dfls-exponents)
  ;; proof that these exponents should be disallowed
  (num-test (string->number "1l1") 10.0)
  (num-test (string->number "1l1+1l1i") 10+10i)
  (num-test (string->number "1l11+11l1i") 100000000000+110i)
  (num-test (string->number "#d1d1") 10.0)
  (num-test (string->number "#d0001d0001") 10.0))
(test (#|#<|# = #|#f#|# #o#e0 #|#>|# #e#o0 #|#t#|#) #t)

(num-test #d9223372036854775807 most-positive-fixnum)
(num-test #d-9223372036854775808 most-negative-fixnum)
(num-test #d1.0e8 100000000.0)
(num-test (string->number "#e#d+11.e-0") 11)
(num-test (string->number "#d.0e011110") 0.0)

(when with-bignums (num-test (string->number "#d3000000000000000000000000000000") 3000000000000000000000000000000))
(num-test #d-1/2 -1/2)
(num-test #d+1/2 1/2)
(num-test #d1.0e-8 1.0e-8)
(num-test #d-.1 -0.1)
(num-test #d+.1 +0.1)
(num-test #d+.1e+1 1.0)
(num-test #d1/2 1/2)
(num-test #d3/4 3/4)
(num-test #d11/2 11/2)
(num-test #d9223372036854775807/7 1317624576693539401)
(num-test (string->number "#d9.11" 16) 9.11)
(num-test (string->number "#d9.11" 10) 9.11)

;; nutty: #e+inf.0 #e+nan.0 
;;    these don't arise in s7 because we don't define inf.0 and nan.0
(if with-bignums (num-test #e9007199254740995.0 9007199254740995))

(test (= 1 #e1 1/1 #e1/1 #e1.0 #e1e0 #b1 #x1 #o1 #d1 #o001 #o+1 #o#e1 #e#x1 #e1+0i #e10e-1 #e0.1e1 #e+1-0i #e#b1) #t)
;(test (= 0.3 3e-1 0.3e0 3e-1) #t)
(test (= 0 +0 0.0 +0.0 0/1 +0/24 0+0i #e0 #b0 #x0 #o0 #e#b0) #t)

(let ((things (vector 123 #e123 #b1111011 #e#b1111011 #b#e1111011 #o173 #e#o173 #o#e173 
		      #x7b #e#x7b #x#e7b (string->number "123") 246/2 #e123/1 #d123 #e#d123 #d#e123)))
  (do ((i 0 (+ i 1)))
      ((= i (- (vector-length things) 1)))
    (do ((j (+ i 1) (+ j 1)))
	((= j (vector-length things)))
      (if (not (eqv? (vector-ref things i) (vector-ref things j)))
	  (begin
	    (display "(eqv? ") (display (vector-ref things i)) (display " ") (display (vector-ref things j)) (display ") -> #f?") (newline))))))

(for-each
 (lambda (p)
   (let ((sym (car p))
	 (num (cdr p)))
     (let ((tag (catch #t (lambda () (string->number sym)) (lambda args 'error))))
       (if (not (equal? num tag))
	   (format-logged #t ";(string->number ~S) = ~A [~A]~%" sym tag num)))))
 '(("#xe/d" . 14/13) ("#xb/d" . 11/13) ("#xf/d" . 15/13) ("#x1/f" . 1/15) ("#xd/f" . 13/15) ("#xe/f" . 14/15) ("#d.1" . .1) ("#d01" . 1)
   ("#d+1" . 1) ("#d+0" . 0) ("#d0+i" . 0+i) ("#xe+i" . 14.0+1.0i) ("#xf+i" . 15.0+1.0i) ("#d1-i" . 1.0-1.0i)))

(num-test #d0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e300 1.0)


(test (char? #e1) #f)
(test (eval-string "(char? #\\x#e0.0") 'error)
(test (eval-string "(char? #\\x#e0e100") 'error)
(test (eval-string "(char? #\\x#e0.0)") 'error)
(test (eval-string "(char? #\\x#e0e100)") 'error)

(test (= 1/2 '#e#b1e-1) #t)
(num-test `,#e.1 1/10)
;(num-test (string->number "#e#x-142.1e-1") -554/49)
;(num-test (string->number "#e#ta.a") 65/6)
;(num-test (string->number "#e#t11.6") 27/2)

(test (integer? #e.1e010) #t)
;#e4611686018427388404.0 -> 4611686018427387904

(when with-bignums
  (num-test #e9007199254740995.0 9007199254740995)
  (num-test #e4611686018427388404.0 4611686018427388404))

(num-test (lognot #e10e011) -1000000000001)
(num-test (ceiling #e-01-0i ) -1)
(test (lcm 1 ' #e1.(logior )) 0) ; (lcm 1 1 0)
;(test (= (string->number "#e.1e20") 1e19) #t)
(num-test (expt #e1 -111) 1)
(num-test (expt -0(quasiquote #e0)) 1)
(num-test (string->number "#e0a" 16) 10)
(num-test #e1.0e8 100000000)

(test (string->number "#o#e10.+1.i") #f)
(test (string->number "#x#e1+i") #f)
(test (string->number "#x#1+#e1i") #f)
(test (string->number "#x#e1+#e1i") #f)
(test (string->number "#b#e1+i") #f)
(test (string->number "#o#e1-110.i") #f)
(num-test (string->number "#e1+0i") 1)
(num-test (string->number "#x#e1+0i") 1)
(num-test (string->number "#e#x1+0i") 1)

(num-test #e0.1 1/10)
(test (equal? #e1.5 3/2) #t)
(test (equal? #e1.0 1) #t)
(test (equal? #e-.1 -1/10) #t)
(test (equal? #e1 1) #t)
(test (equal? #e3/2 3/2) #t)
(num-test (string->number "#e8/2" 11) 4)
;(num-test (string->number "#eb8235.9865c01" 13) 19132998081/57607)
; this one depends on the underlying size (32/64)

(num-test #e0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e300 1)
(num-test #e0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e309 1)
(num-test #e0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000123e309 123/100)
(num-test #e-.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000123456e314 -123456)

(num-test #e1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-300 1)
(num-test #e1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-309 1)
(num-test #e-1234000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-309 -617/500)

(num-test #e1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-300 1)
(num-test #e1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-309 1)
(num-test #e1.0e0000000000000000000000000000000000001 10)
(num-test #e1.0e-0000000000000000000000000000000000001 1/10)
(num-test #e00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 10)

(when with-bignums
  (test (bignum? (bignum "#e1.5")) #t))

(when (provided? 'dfls-exponents)
  (num-test (tanh 1s13)    1s0)
  (num-test (tanh 1s3)     1s0)
  (num-test (tanh 1s2)     1s0)
  (num-test (tanh 1s1)     1s0)
  (num-test (tanh 1l0)     0.7615941559557648881L0)
  (num-test (tanh 1l1)     0.9999999958776927636L0)
  (num-test (tanh 1l100)   1L0)
  (num-test (tanh 1f10)    1f0)
  (num-test (tanh 1L-10)   1L-10)
  (num-test (tanh 1L-17)   1L-17)
  (num-test (tanh 1L-47)   1L-47))

(when (provided? 'dfls-exponents)
  (test (> 1.0L10 1.0e9) #t)
  (test (> 1.0l10 1.0e9) #t)
  (test (> 1.0s10 1.0e9) #t)
  (test (> 1.0S10 1.0e9) #t)
  (test (> 1.0d10 1.0e9) #t)
  (test (> 1.0D10 1.0e9) #t)
  (test (> 1.0f10 1.0e9) #t)
  (test (> 1.0F10 1.0e9) #t)
  
  (test (> (real-part 1.0L10+i) 1.0e9) #t)
  (test (> (real-part 1.0l10+i) 1.0e9) #t)
  (test (> (real-part 1.0s10+i) 1.0e9) #t)
  (test (> (real-part 1.0S10+i) 1.0e9) #t)
  (test (> (real-part 1.0d10+i) 1.0e9) #t)
  (test (> (real-part 1.0D10+i) 1.0e9) #t)
  (test (> (real-part 1.0f10+i) 1.0e9) #t)
  (test (> (real-part 1.0F10+i) 1.0e9) #t)
  
  (test (> (imag-part 1.0+1.0L10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0l10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0s10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0S10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0d10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0D10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0f10i) 1.0e9) #t)
  (test (> (imag-part 1.0+1.0F10i) 1.0e9) #t)
  
  (test (> (string->number "1.0L10") 1.0e9) #t)
  (test (> (string->number "1.0l10") 1.0e9) #t)
  (test (> (string->number "1.0s10") 1.0e9) #t)
  (test (> (string->number "1.0S10") 1.0e9) #t)
  (test (> (string->number "1.0d10") 1.0e9) #t)
  (test (> (string->number "1.0D10") 1.0e9) #t)
  (test (> (string->number "1.0f10") 1.0e9) #t)
  (test (> (string->number "1.0F10") 1.0e9) #t)
  
  (test (> (real-part (string->number "1.0L10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0l10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0s10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0S10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0d10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0D10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0f10+i")) 1.0e9) #t)
  (test (> (real-part (string->number "1.0F10+i")) 1.0e9) #t)
  
  (test (> (imag-part (string->number "1.0+1.0L10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0l10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0s10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0S10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0d10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0D10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0f10i")) 1.0e9) #t)
  (test (> (imag-part (string->number "1.0+1.0F10i")) 1.0e9) #t)
  
  (when with-bignums
    (test (> (string->number "1.0L100") 1.0e98) #t)
    (test (> (string->number "1.0l100") 1.0e98) #t)
    (test (> (string->number "1.0s100") 1.0e98) #t)
    (test (> (string->number "1.0S100") 1.0e98) #t)
    (test (> (string->number "1.0d100") 1.0e98) #t)
    (test (> (string->number "1.0D100") 1.0e98) #t)
    (test (> (string->number "1.0f100") 1.0e98) #t)
    (test (> (string->number "1.0F100") 1.0e98) #t)
    (test (> (string->number "1.0E100") 1.0e98) #t)
    
    (test (> 1.0L100 1.0e98) #t)
    (test (> 1.0l100 1.0e98) #t)
    (test (> 1.0s100 1.0e98) #t)
    (test (> 1.0S100 1.0e98) #t)
    (test (> 1.0d100 1.0e98) #t)
    (test (> 1.0D100 1.0e98) #t)
    (test (> 1.0f100 1.0e98) #t)
    (test (> 1.0F100 1.0e98) #t)
    
    (test (> (real-part (string->number "1.0L100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0l100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0s100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0S100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0d100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0D100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0f100+i")) 1.0e98) #t)
    (test (> (real-part (string->number "1.0F100+i")) 1.0e98) #t)
    
    (test (> (real-part 1.0L100+i) 1.0e98) #t)
    (test (> (real-part 1.0l100+i) 1.0e98) #t)
    (test (> (real-part 1.0s100+i) 1.0e98) #t)
    (test (> (real-part 1.0S100+i) 1.0e98) #t)
    (test (> (real-part 1.0d100+i) 1.0e98) #t)
    (test (> (real-part 1.0D100+i) 1.0e98) #t)
    (test (> (real-part 1.0f100+i) 1.0e98) #t)
    (test (> (real-part 1.0F100+i) 1.0e98) #t)
    
    (test (> (imag-part (string->number "1.0+1.0L100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0l100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0s100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0S100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0d100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0D100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0f100i")) 1.0e98) #t)
    (test (> (imag-part (string->number "1.0+1.0F100i")) 1.0e98) #t)
    
    (test (> (imag-part 1.0+1.0L100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0l100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0s100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0S100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0d100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0D100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0f100i) 1.0e98) #t)
    (test (> (imag-part 1.0+1.0F100i) 1.0e98) #t)))

(when (provided? 'dfls-exponents)
  (test (string->number "1D1") 10.0)
  (test (string->number "1S1") 10.0)
  (test (string->number "1F1") 10.0)
  (test (string->number "1L1") 10.0)
  (test (string->number "1d1") 10.0)
  (test (string->number "1s1") 10.0)
  (test (string->number "1f1") 10.0)
  (test (string->number "1l1") 10.0))

(when (provided? 'dfls-exponents)
  (for-each
   (lambda (n)
     (let ((nb 
	    (catch #t
	      (lambda ()
		(number? n))
	      (lambda args
		'error))))
       (if (not nb)
	   (begin
	     (display "(number? ") (display n) (display ") returned #f?") (newline)))))
   
   (list 1 -1 +1 +.1 -.1 .1 .0 0. 0.0 -0 +0 -0. +0.
	 +1.1 -1.1 1.1
	 '1.0e2 '-1.0e2 '+1.0e2
	 '1.1e-2 '-1.1e-2 '+1.1e-2
	 '1.1e+2 '-1.1e+2 '+1.1e+2
	 '1/2 '-1/2 '+1/2
	 '1.0s2 '-1.0s2 '+1.0s2
	 '1.0d2 '-1.0d2 '+1.0d2
	 '1.0f2 '-1.0f2 '+1.0f2
	 '1.0l2 '-1.0l2 '+1.0l2
	 '1.0+1.0i '1.0-1.0i '-1.0-1.0i '-1.0+1.0i
	 '1+i '1-i '-1-i '-1+i
	 '2/3+i '2/3-i '-2/3+i
	 '1+2/3i '1-2/3i '2/3+2/3i '2.3-2/3i '2/3-2.3i
	 '2e2+1e3i '2e2-2e2i '2.0e2+i '1+2.0e2i '2.0e+2-2.0e-1i '2/3-2.0e3i '2e-3-2/3i
	 '-2.0e-2-2.0e-2i '+2.0e+2+2.0e+2i '+2/3-2/3i '2e2-2/3i
	 '1e1-i '1.-i '.0+i '-.0-1e-1i '1.+.1i '0.-.1i
	 '.1+.0i '1.+.0i '.1+.1i '1.-.1i '.0+.00i '.10+.0i '-1.+.0i '.1-.01i '1.0+.1i 
	 '1e1+.1i '-1.-.10i '1e01+.0i '0e11+.0i '1.e1+.0i '1.00-.0i '-1e1-.0i '1.-.1e0i 
	 '1.+.001i '1e10-.1i '1e+0-.1i '-0e0-.1i
	 '-1.0e-1-1.0e-1i '-111e1-.1i '1.1-.1e11i '-1e-1-.11i '-1.1-.1e1i '-.1+.1i)))


(num-test #i00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001/00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 1.0)

(do ((i (char->integer #\") (+ i 1)))
    ((= i 127))
  (when (not (member (integer->char i) '(#\( #\: #\|)))
    (set! *#readers* (cons (cons (integer->char i) (lambda (str) (string->number (substring str 1)))) ()))
    (let ((val (eval (with-input-from-string (string-append "(+ 10 #" (string (integer->char i)) "12)") read))))
      (if (not (equal? val 22)) (format *stderr* "~D (~C): ~A~%" i (integer->char i) val)))))

