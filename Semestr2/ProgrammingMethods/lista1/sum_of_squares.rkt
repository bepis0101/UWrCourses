#lang racket
(require rackunit)

(define (sum_of_squares a b c)
  (cond [ (and (> a b) (> c b)) (+ (* a a) (* c c)) ]
        [ (and (> b a) (> c a)) (+ (* b b) (* c c)) ]
        [ else (+ (* a a) (* b b)) ] ))

(check-equal? (sum_of_squares 3 4 5) 41)
(check-equal? (sum_of_squares 6 4 5) 61)
(check-equal? (sum_of_squares 2 1 1) 5)