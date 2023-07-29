module Main (main) where

import Graph 
-- import BellmanFord
-- import Dijkstra
import FloydWarshall

main :: IO ()
main = do 
    -- print $ calcShortestPathCosts 1 testData
    -- print testData
    -- print $ dijkstra testData2 0
    printCost $ floydWarshall 7 testData3
    return ()

