module FloydWarshall(
    floydWarshall,
    printCost
) where

import Graph
import Data.Map (lookup)
import Data.Array (Array, range, array, (!), bounds)

type Costs = Array (Vertex, Vertex) Weight

initialize :: Int -> TupleGraph -> Costs
initialize numVertices edges = array bounds [((i, j), if i == j then 0 else value edges (i, j)) | (i, j) <- range bounds]
    where
        bounds = ((0, 0), (numVertices-1, numVertices-1))
        value e ij = case Data.Map.lookup ij e of
            Just v -> v
            Nothing -> infinity

floydWarshall :: Int -> TupleGraph -> Costs
floydWarshall numVertices graph = updateCosts numVertices $ initialize numVertices graph

updateCosts :: Int -> Costs -> Costs
updateCosts numVertices costs = foldl update costs [0..numVertices-1]
    where
        update acc newVertex = array bounds [((i, j), value acc ij i j newVertex) | ij@(i, j) <- range bounds]
            where
                bounds = ((0, 0), (numVertices-1, numVertices-1))
                value c ij i j k = min (c ! ij) ((c ! (i,k)) + (c ! (k, j)))

printCost :: Costs -> IO ()
printCost costs = do
    putStrLn "Costs: "
    putStrLn $ unlines 
        [unwords 
            [if d == infinity then "INF" else show d 
            | j <- [0..numVertices], 
            let d = costs ! (i, j)] 
        | i <- [0..numVertices]
        ]
    where
        numVertices :: Int
        numVertices = snd $ snd $ bounds costs

-- ghci> func all@(x:_) = all ++ [x]
-- ghci> func "Hello"
-- "HelloH"
-- ghci> f ij@(i,j) = (ij, i, j)
-- ghci> f (2,3)
-- ((2,3),2,3)
-- ghci> b = ((0,0),(3,3))
-- ghci> b
-- ((0,0),(3,3))
-- ghci> range b
-- [(0,0),(0,1),(0,2),(0,3),(1,0),(1,1),(1,2),(1,3),(2,0),(2,1),(2,2),(2,3),(3,0),(3,1),(3,2),(3,3)]

-- ghci> unlines ["abc", "def", "ghi"]
-- "abc\ndef\nghi\n"

-- ghci> words "abc def ghi"
-- ["abc","def","ghi"]
-- ghci> unwords ["abc", "def", "ghi"]
-- "abc def ghi"