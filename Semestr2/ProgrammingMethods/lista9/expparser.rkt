#lang racket
(require "parsing.rkt")
(require (only-in plait s-exp-content))
(define (parse-Exp s)
  (parse-exp (s-exp-content s)))