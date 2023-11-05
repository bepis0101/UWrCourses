#lang racket

(define (negatives n)
  (build-list n (lambda (n) (* -1 (+ n 1)))))

(define (reciprocals n)
  (build-list n (lambda (n) (/ 1 (+ n 1)))))

(define (evens n)
  (build-list n (lambda (n) (* 2 n))))

(define (identityM n)
  (build-list n
              (lambda (col) (build-list n
                                        (lambda (rows)
                                          (if (= col rows) 1
                                              0))))))


(identityM 53)