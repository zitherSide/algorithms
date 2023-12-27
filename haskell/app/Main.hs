module Main (main) where

-- import Graph 
-- import BellmanFord
-- import Dijkstra
-- import FloydWarshall
-- import Prim
-- import Kruskal
-- import RoadBlock
-- import Conscription
-- import Layout
-- import CrazyRow
import BribePrisoners

main :: IO ()
main = do 
    print "The Result is: "
    -- print $ calcShortestPathCosts 1 testData
    -- print testData
    -- print $ dijkstra testData2 0
    -- printCost $ floydWarshall 7 testData3
    -- print $ prim testData4
    -- print $ kruskal testData4
    -- print $ calcSecondShortest 0 6 testData
    -- let orgCost= calcOrgCost intimacies
    --     reduction = calcGraphCost $ calcMaxIntimacies intimacies
    -- print $ orgCost + reduction
    -- print (show $ calcLongestLayout 4 [(0, 2, 10), (1, 3, 20)] [(1, 2, 3)] )
    -- print $ calcMinimumSteps CrazyRow.testData
    print $ calcMinBribe 20 [3, 6, 14]
    return ()

