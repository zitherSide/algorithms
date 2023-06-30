module Graph
    (
        Vertex,
        Weight,
        Graph, 
        testData
    ) where

import Data.Array

type Vertex = Int
type Weight = Int
type Graph = Array Vertex [(Vertex, Weight)] -- Array [IndexType] [ValueType]

testData :: Graph
testData = array(0, 6)  [   -- array range [elements]
    (0, [
        (1, 2),
        (2, 5)
        ]),
    (1, [
        (0, 2),
        (2, 4),
        (3, 6),
        (4, 10)
        ]),
    (2, [
        (0, 5),
        (1, 4),
        (3, 2)
        ]),
    (3, [
        (1, 6),
        (2, 2),
        (5, 1)
    ]),
    (4, [
        (1, 10),
        (5, 3),
        (6, 5)
    ]),
    (5, [
        (3, 1),
        (4, 3),
        (6, 9)
    ]),
    (6, [
        (4, 5),
        (5, 9)
    ])
     
    ]