#lang racket

(define (fib-rec n)
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (+ (fib-rec (- n 1)) (fib-rec(- n 2)))]))

;(fib-rec 40)

(define (fib-it n)
  (define (it a b m)
    (if (= m 0) a
    (it b (+ a b) (- m 1))))
  (it 0 1 n))
