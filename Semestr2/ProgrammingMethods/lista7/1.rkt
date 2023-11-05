#lang plait

(define-type (BalancedBST 'a)
  (leaf)
  (node2 (l : (BalancedBST 'a)) (elem : 'a) (r :  (BalancedBST 'a)))
  (node3 (l : (BalancedBST 'a)) (eleml : 'a) (mid : (BalancedBST 'a)) (elemr : 'a) (r :  (BalancedBST 'a))))

(define example-tree
    (node3
        (node3 (leaf) 2 (leaf) 3 (leaf))
        5
        (node2 (leaf) 6 (leaf))
        9
        (node2 (leaf) 10 (leaf))))

(define (3= a b c) (and (= a b) (= b c)))
(define (3< a b c) (and (< a b) (< b c)))
(define (4< a b c d) (and (< a b) (< b c) (< c d)))

(define (BalancedBST?? t)
  (local(
         (define (check-order minimum maksimum t)
           (type-case (BalancedBST 'a) t
             [(leaf) #t]
             [(node2 l elem r)
              (and
               (3< minimum elem maksimum)
               (check-order minimum elem l)
               (check-order elem maksimum r))]
             [(node3 l el elem er r)
              (and
               (4< minimum el er maksimum)
               (check-order minimum el l)
               (check-order el er elem)
               (check-order er maksimum r))]))

         (define (t? x) (not (= x -inf.0)))
         (define (height t)
           (type-case (BalancedBST 'a) t
             [(leaf) 0]
             [(node2 l elem r)
              (let [(h-l (height l)) (h-r (height r))]
                (if (and (t? h-l) (t? h-r) (= h-r h-l)) (+ h-l 1) -inf.0))]
             [(node3 l el mid er r)
              (let [(h-l (height l)) (h-m (height mid)) (h-r (height r))]
                (if (and (t? h-l) (t? h-m) (t? h-r) (3= h-l h-m h-r)) (+ h-l 1) -inf.0))])))
    (and
     (check-order -inf.0 +inf.0 t)
     (t? (height t)))))
                
               