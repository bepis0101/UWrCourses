#lang racket
(define-struct queue (prefix suffix) #:transparent)
(define (pref? q) (if (null? (queue-prefix q))
                      #f
                      #t))
(define empty-queue (queue '() '() ))
(define (empty? q) (null? (queue-suffix q)))

(define (push x q)
  (if (pref? q)
      (queue (queue-prefix q) (cons x (queue-suffix q)))
      (queue (reverse (cons x (queue-suffix q))) '())))
(define (front q)
  (car (queue-prefix q)))
(define (pop q)
  (if (null? (cdr(queue-prefix q)))
      (queue (reverse (queue-suffix q)) '())
      (queue (cdr (queue-prefix q)) (queue-suffix q))))

(define q (push 5 (push 4 (push 2 empty-queue))))
(front q)