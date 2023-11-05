#lang plait

(define (sorted? xs)
  (if (empty? (rest xs))
      #t
      (if (<= (first xs) (first (rest xs)))
          (sorted? (rest xs))
          #f)))

(define (insert x xs)
  (if (empty? xs)
      xs
      (if (> (first xs) x)
          (cons x xs)
          (cons (first xs) (insert x (rest xs))))))

(insert 4 (list 1 4 4 7 8 12))

#|
(sorted? xs)=#t => (sorted? (rest xs))=#t

|#