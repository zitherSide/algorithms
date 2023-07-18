module Main (main) where

import Graph 
import BellmanFord
import Dijkstra

main :: IO ()
main = do 
    -- print $ calcShortestPathCosts 1 testData
    -- print testData
    print $ dijkstra testData2 0
    return ()

