module Graph
    (
        Vertex,
        Weight,
        Graph, 
        MapGraph,
        TupleGraph,
        TupleEdgeGraph,
        TupleEdge,
        testData,
        testData2,
        testData3,
        testData4,
        infinity
    ) where

import Data.Array
import Data.Map

type Vertex = Int
type Weight = Int
type Graph = Array Vertex [(Vertex, Weight)] -- Array [IndexType] [ValueType]
type MapGraph = Map Vertex [(Vertex, Weight)]
type TupleGraph = Map (Vertex, Vertex) Weight
type TupleEdge = (Vertex, Vertex, Weight)
type TupleEdgeGraph = [TupleEdge]

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

testData2 :: MapGraph
testData2 = fromList $ Data.Array.assocs testData

testData3 :: TupleGraph
testData3 = fromList [   -- array range [elements]
    ((0, 1), 2),
    ((0, 2), 5),
    ((1, 0), 2),
    ((1, 2), 4),
    ((1, 3), 6),
    ((1, 4), 10),
    ((2, 0), 5),
    ((2, 1), 4),
    ((2, 3), 2),
    ((3, 1), 6),
    ((3, 2), 2),
    ((3, 5), 1),
    ((4, 1), 10),
    ((4, 5), 3),
    ((4, 6), 5),
    ((5, 3), 1),
    ((5, 4), 3),
    ((5, 6), 9),
    ((6, 4), 5),
    ((6, 5), 9)
    ]

testData4 :: TupleEdgeGraph
testData4 = [
    (0, 1, 2),
    (0, 2, 5),
    -- (1, 0, 2),
    (1, 2, 4),
    (1, 3, 6),
    (1, 4, 10),
    -- (2, 0, 5),
    -- (2, 1, 4),
    (2, 3, 2),
    -- (3, 1, 6),
    -- (3, 2, 2),
    (3, 5, 1),
    -- (4, 1, 10),
    (4, 5, 3),
    (4, 6, 5),
    -- (5, 3, 1),
    -- (5, 4, 3),
    (5, 6, 9)
    -- (6, 4, 5),
    -- (6, 5, 9)
    ]

infinity :: Int
infinity = maxBound `div` 2 -- maxBound整数型, / は浮動小数点演算なのでNGだが divは整数型を受け取れるのでOK