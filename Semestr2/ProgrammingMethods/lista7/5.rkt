#lang racket

(define/contract (foldl-map f a xs)
  (parametric->/c [x y acc]
                  (-> (-> x acc (cons/c y acc)) acc (listof x)
                      (cons/c (listof y) acc)))
  ( define ( it a xs ys )
     (if ( null? xs )
         ( cons ( reverse ys ) a )
         (let [( p ( f ( car xs ) a ) ) ]
           ( it ( cdr p )
                ( cdr xs )
                ( cons ( car p ) ys ) ) ) ) )
  ( it a xs null) )
