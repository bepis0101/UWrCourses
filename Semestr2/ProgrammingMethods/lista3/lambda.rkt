#lang racket

(( lambda ( x y ) (+ x (* x y ) ) ) 1 2)
(( lambda ( x ) x ) ( lambda ( x ) x ) )