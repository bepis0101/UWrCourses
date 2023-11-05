#lang racket

(define/contract (f1 a b)
  (parametric->/c [a b] (-> a b a))
  a)
(f1 1 "b")

(define/contract (f2 fabc fab a)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (fabc a (fab a)))
(f2 + identity 2)

(define/contract (f3 fbc fab)
  (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
  (lambda (a) ((fab a) fbc)))

(define/contract (f4 ffaa->a)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  (ffaa->a identity))
