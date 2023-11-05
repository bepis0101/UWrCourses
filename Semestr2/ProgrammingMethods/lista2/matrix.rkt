#lang racket
(define-struct matrix(a b c d) #:transparent)
;zad 3
(define (matrix-mult m n)
  (matrix
   (+ (* (matrix-a m) (matrix-a n)) (* (matrix-b m) (matrix-c n)))
   (+ (* (matrix-a m) (matrix-b n)) (* (matrix-b m) (matrix-d n)))
   (+ (* (matrix-c m) (matrix-a n)) (* (matrix-d m) (matrix-c n)))
   (+ (* (matrix-c m) (matrix-b n)) (* (matrix-d m) (matrix-d n)))
   )
  )
(define matrix-id (matrix 1 0 0 1))
(define (matrix-exp m k)
  (cond [(= k 1) m]
        [(= k 0) matrix-id]
        [else (matrix-mult m (matrix-exp m (- k 1)))]))

(matrix-exp (matrix 2 0 0 2) 10)

(define fib-matrix (matrix 1 1 1 0))

(define (fib k)
  (matrix-b (matrix-exp fib-matrix k)))

(fib 7)
;zad 4
(define (matrix-exp-fast n)
  (define (it m k res)
    (if (= k 0) res
        (if (= (modulo k 2) 0) (it (matrix-mult m m) (floor(/ k 2)) res)
            (it m (- k 1) (matrix-mult res m)))))
  (it fib-matrix n matrix-id))


            
(define (elem-fib n)
  (matrix-b (matrix-exp-fast n)))
  

(elem-fib 7)