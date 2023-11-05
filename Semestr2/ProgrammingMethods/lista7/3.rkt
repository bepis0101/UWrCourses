#lang racket

(define/contract (suffixes-contract xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (cond
    [(empty? xs) (list '())]
    [else (cons '() (map (lambda (ys) (cons (first xs) ys)) (suffixes-contract (rest xs))))]))


(define (suffixes xs)
  (cond
    [(empty? xs) (list '())]
    [else (cons '() (map (lambda (ys) (cons (first xs) ys)) (suffixes (rest xs))))]))

(define start (current-inexact-milliseconds))
(define t1 (suffixes (range 3000)))
(define stop (current-inexact-milliseconds))
(- stop start)

(define start-c (current-inexact-milliseconds))
(define t2 (suffixes-contract (range 3000)))
(define stop-c (current-inexact-milliseconds))
(- stop-c start-c)