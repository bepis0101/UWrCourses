#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)
(define (tree? x)
  (cond [(leaf? x) #t]
        [(node? x) (and (tree? (node-l x))
                        (tree? (node-r x)))]
        [else #f]))

(define example-tree
  (node (node (leaf) 1 (leaf))
        2
        (node (node (leaf) 3 (leaf))
              4
              (leaf))))
(define (sorted? xs)
  (if (null? (cdr xs)) #t
      (if (> (car xs) (car (cdr xs)))
          #f
          (sorted? (cdr xs)))))


(define (fold-tree t f x)
  (cond [(leaf? t) x]
        [(node? t) (f
                    (fold-tree (node-l t) f x)
                    (node-elem t)
                    (fold-tree (node-r t) f x))]))

(define (tree-sum t)
  (fold-tree t + 0))

(tree-sum example-tree)

(define (tree-flip t)
  (fold-tree t (lambda (x y z) (node z y x)) (leaf)))  

(tree-flip example-tree)

(define (tree-height t)
  (fold-tree t (lambda (x y z) (max (+ 1 x) (+ 1 z))) 0))

(tree-height example-tree)

(define (tree-span t)
  (cons (fold-tree t (lambda (x y z) (if (leaf? x)
                                         y
                                         x)) (leaf))
        (fold-tree t (lambda (x y z) (if (leaf? z)
                                         y
                                         z)) (leaf))))
(tree-span example-tree)

(define (flatten t)
  (fold-tree t (lambda (a b c) (append a (cons b c))) '()))

(flatten example-tree)

(define (bst? t)
  (sorted? (flatten t)))
(bst? example-tree)

(define (sum-paths t)
  (define (suma t sum)
    (if (leaf? t)
        (leaf)
        (node (suma (node-l t) (+ sum (node-elem t)))
              (+ sum (node-elem t))
              (suma (node-r t) (+ sum (node-elem t))))))
  (suma t 0))

(sum-paths example-tree)


(define (flatten-better t)
  (define (flat-append t xs)
    (if (leaf? t)
        xs
        (flat-append (node-l t) (cons (node-elem t) (flat-append (node-r t) xs)))))
  (flat-append t '()))
(flatten-better example-tree)