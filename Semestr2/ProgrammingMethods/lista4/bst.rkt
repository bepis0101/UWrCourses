#lang racket
(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)
(define (tree? x)
  (cond [(leaf? x) #t]
        [(node? x) (and (tree? (node-l x))
                        (tree? (node-r x)))]
        [else #f]))
(define (fold-tree t f x)
  (cond [(leaf? t) x]
        [(node? t) (f
                    (fold-tree (node-l t) f x)
                    (node-elem t)
                    (fold-tree (node-r t) f x))]))

(define (tree-span t)
  (cons (fold-tree t (lambda (x y z) (if (leaf? x)
                                         y
                                         x)) (leaf))
        (fold-tree t (lambda (x y z) (if (leaf? z)
                                         y
                                         z)) (leaf))))
(define example-tree
  (node (node (leaf) 1 (leaf))
        2
        (node (node (leaf) 3 (leaf))
              4
              (leaf))))
(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond 
                [(< x (node-elem t))
                 (node (insert-bst x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst x (node-r t)))])]))
(define (treesort xs)
  (define (list->bst xs)
    (if (null? xs)
        (leaf)
        (insert-bst (car xs) (list->bst (cdr xs)))))
  (define (flatten-better t)
    (define (flat-append t xs)
      (if (leaf? t)
          xs
          (flat-append (node-l t) (cons (node-elem t) (flat-append (node-r t) xs)))))
    (flat-append t '()))
  (flatten-better (list->bst xs)))
(treesort '(3 2 5 6 2))

(define (delete x t)
  (cond [(leaf? t) (leaf)]
        [(= x (node-elem t))
         (cond [(leaf? (node-r t)) (node-l t)]
               [(leaf? (node-l t)) (node-r t)]
               [else (node (node-l t)
                           (car (tree-span (node-r t)))
                           (delete (car (tree-span (node-r t))) (node-r t)))])]
        [(< x (node-elem t))
         (node (delete x (node-l t))
               (node-elem t)
               (node-r t))]
        [else
         (node (node-l t)
               (node-elem t)
               (delete x (node-r t)))]))
(delete 3 example-tree)