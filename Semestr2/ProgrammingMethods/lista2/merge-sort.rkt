#lang racket
(define (split xs)
  (define (create-pair lista xs)
    (if (null? xs)
        lista
        (create-pair (append (list (car lista)) (list (car xs))) (cdr (cdr xs)))
        (create-pair (append (list (cdr lista)) (list (car (cdr xs))