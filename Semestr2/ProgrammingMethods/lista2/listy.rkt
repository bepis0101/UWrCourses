#lang racket
(require rackunit)

(define (elem? x xs)
  (if (null? xs)
      #f
      (if (= (car xs) x)
          #t
          (elem? x (cdr xs)))))

(define (maximum xs)
  (define (find-max xs maks)
    (if (null? xs)
        maks
        (if (> (car xs) maks)
            (find-max (cdr xs) (car xs))
            (find-max (cdr xs) maks))))
  (find-max xs -inf.0))

(define (suffixes xs)
    (if (null? xs)
        (append (list xs) '())
        (append (list xs) (suffixes (cdr xs)))))

(suffixes (list 1 2 3 4))

(define (sorted? lista)
  (if (null? (cdr lista))
      #t
      (if (> (car lista) (car (cdr lista)))
          #f
          (sorted? (cdr lista)))))
(sorted? (list 1 3 3 1 5))

(define (minimum xs)
  (define (find-min xs min)
    (if (null? xs)
        min
        (if (< (car xs) min)
            (find-min (cdr xs) (car xs))
            (find-min (cdr xs) min))))
  (find-min xs +inf.0))

(define (select xs)
  (define (build-list new-lista xs elem)
    (if (null? xs)
        new-lista
        (if (= (car xs) elem) 
            (build-list (append new-lista (cdr xs)) null elem)
            (build-list (append new-lista (list (car xs))) (cdr xs) elem))))
  
  (build-list (list (minimum xs)) xs (minimum xs)))


(select (list 5 4 1 1 3))
(define (select-sort xs)
  (define (create-list lista xs) 
    (if (null? xs)
        lista
        (create-list (append lista (list (car (select xs)))) (cdr (select xs)))))
  (create-list (list) xs))
      
(select-sort (list 5 4 0 1 2))
  
  
    
  