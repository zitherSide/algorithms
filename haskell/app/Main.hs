module Main (main) where

import Graph 
import BellmanFord

main :: IO ()
main = do 
    -- print $ calcShortestPathCosts 1 testData
    -- print testData
    print $ bellmanFord testData 0
    return ()

