#lang plait
( define-type ( Formula 'v )
( var [ var : 'v ])
( neg [ f : ( Formula 'v ) ])
( conj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ])
( disj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ]) )

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

(define (nnf-neg v)
  (cond [(nnf-conj? v) (nnf-disj (nnf-neg (nnf-conj-l v)) (nnf-neg (nnf-conj-r v)))]
        [(nnf-disj? v) (nnf-conj (nnf-neg (nnf-disj-l v)) (nnf-neg (nnf-disj-r v)))]
        [else (nnf-lit (not (nnf-lit-polarity v)) (nnf-lit-var v))]))

(define (to-NNF v)
  (cond [(var? v) (nnf-lit #t (var-var v))]
        [(neg? v) (nnf-neg (to-NNF (neg-f v)))]
        [(conj? v) (nnf-conj (to-NNF (conj-l v)) (to-NNF(conj-r v)))]
        [(disj? v) (nnf-disj (to-NNF (disj-l v)) (to-NNF(disj-r v)))]
        ))

(define formula-nnf (nnf-conj (nnf-disj (nnf-lit #t "p") (nnf-lit #f "q"))
                          (nnf-disj (nnf-lit #t "s") (nnf-lit #t "t"))))

(define formula (conj (disj (var "p") (neg (var "q")))
                      (disj (var "s") (var  "t"))))

(to-NNF formula)
formula-nnf

