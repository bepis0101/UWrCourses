#lang racket
(define (my-foldl f x xs)
 (define (it xs acc)
   (if (null? xs)
       acc
       (it (cdr xs) (f (car xs) acc))))
 (it xs x))

(define (my-sum2 xs)
  (my-foldl + 0 xs))
(define (my-product xs)
  (my-foldl * 1 xs))