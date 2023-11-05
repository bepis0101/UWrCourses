#lang racket
( define-struct ord ( val priority ) #:transparent )
( define-struct hleaf () )
( define-struct hnode ( elem rank l r ) #:transparent )
( define ( make-node elem heap-a heap-b )
   (if (<= (rank heap-a) (rank heap-b))
       (hnode elem (+ 1 (rank heap-a)) heap-b heap-a)
       (hnode elem (+ 1 (rank heap-b)) heap-a heap-b)
   ))
( define ( hord? p h )
   (or ( hleaf? h )
       (<= p ( ord-priority ( hnode-elem h ) ) ) ) )
( define ( rank h )
   (if ( hleaf? h )
       0
       ( hnode-rank h ) ) )
( define ( heap? h )
   (or ( hleaf? h )
       (and ( hnode? h )
            ( heap? ( hnode-l h ) )
            ( heap? ( hnode-r h ) )
            (<= ( rank ( hnode-r h ) )
                ( rank ( hnode-l h ) ) )
            (= ( hnode-rank h ) (+ 1 ( hnode-rank ( hnode-r h ) ) ) )
            ( hord? ( ord-priority ( hnode-elem h ) )
                    ( hnode-l h ) )
            ( hord? ( ord-priority ( hnode-elem h ) )
                    ( hnode-r h ) ) ) ) )
(define (heap_min_prior heap) (ord-priority (hnode-elem heap)))

(define (heap-merge h1 h2)
    (cond
        [(hleaf? h1) h2]
        [(hleaf? h2) h1]
        [else
            (let   ((h (if (>  (heap_min_prior h1) (heap_min_prior h2)) h1 h2))
                    (H (if (<= (heap_min_prior h1) (heap_min_prior h2)) h1 h2))
                    (e (if (<= (heap_min_prior h1) (heap_min_prior h2)) (hnode-elem h1) (hnode-elem h2))))
                (make-node e (hnode-l H) (heap-merge (hnode-r H) h)))]))


(define empty-pq (hleaf))

(define (pq-empty? h)
    (hleaf? h))

(define (pq-insert val h)
    (heap-merge (hnode (ord "x" val) 1 (hleaf) (hleaf)) h))

(define (pq-pop h)
    (if (pq-empty? h) (empty-pq)
        (heap-merge (hnode-l h) (hnode-r h))))
    
(define (pq-min h)
    (if (pq-empty? h) null
    (ord-priority (hnode-elem h))))


(define (pq-sort xs)
    (define (create-pq pq elem xs)
        (cond 
            [(null? xs) (pq-insert elem empty-pq)]
            [else (pq-insert elem (create-pq pq (car xs) (cdr xs)))]))
    (define (pq->list pq xs)
        (cond
            [(pq-empty? pq) xs]
            [else (cons (pq-min pq) (pq->list (pq-pop pq) xs))]))
    (if (null? xs) '()
        (pq->list (create-pq empty-pq (car xs) (cdr xs)) '())))
