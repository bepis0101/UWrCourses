#lang racket

(define (square x)
  (* x x))
(define (inc x)
  (+ x 1))
(define (my-compose f g x)
  (f (g x)))
(my-compose inc square 5)
(my-compose square inc 5)