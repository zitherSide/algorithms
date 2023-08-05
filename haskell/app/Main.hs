module Main (main) where

import Graph 
-- import BellmanFord
-- import Dijkstra
-- import FloydWarshall
import Prim

main :: IO ()
main = do 
    -- print $ calcShortestPathCosts 1 testData
    -- print testData
    -- print $ dijkstra testData2 0
    -- printCost $ floydWarshall 7 testData3
    print $ prim testData4
    return ()

