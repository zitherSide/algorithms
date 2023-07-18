-- module Dijkstra
--     (
--         dijkstra
--     ) where

-- import Graph
-- import Data.Array
-- import Data.Ord (comparing)
-- import Data.List (minimumBy)

-- dijkstra :: Graph -> Vertex -> Array Vertex (Maybe Weight, Bool)
-- dijkstra graph start = shortestPaths
--     where
--         vertexRange = bounds graph
--         vertices = range vertexRange

--         costs = array vertexRange [(v, (if v == start then Just 0 else Nothing, False)) | v <- vertices]
--         -- shortestPaths = costs

--         chooseBaseVertex :: Array Vertex (Maybe Weight, Bool) ->  Vertex
--         chooseBaseVertex costs = minVertex
--             where
--                 unuseds = filter (\(_, (_, used)) -> not used) $ assocs costs
--                 (minVertex, _) = minimumBy (comparing snd) unuseds
        
--         relaxEdges :: Array Vertex (Maybe Weight, Bool) -> Array Vertex (Maybe Weight, Bool)
--         relaxEdges costs = updated
--             where
--                 base = chooseBaseVertex costs
--                 adjacentEdges = graph ! base
--                 updated = relaxEdge base adjacentEdges costs
--                 -- updated // [(base, snd (updated !! base), True)]
 
--         relaxEdge :: Vertex -> [(Vertex, Weight)] -> Array Vertex (Maybe Weight, Bool) -> Array Vertex (Maybe Weight, Bool)
--         relaxEdge base' edges prevCosts = foldl updateCost prevCosts edges
--             where
--                 updateCost :: Array Vertex (Maybe Weight, Bool) -> (Vertex, Weight) -> Array Vertex (Maybe Weight, Bool)
--                 updateCost prevCosts edge = newCosts
--                     where
--                         (to, cost) = edge
--                         prevCost = prevCosts !! to
--                         newCost = (prevCosts !! base') + cost
--                         newCosts = if(newCost < prevCost)
--                             then prevCost // [(to, (newCost, False))]
--                             else prevCost
                    
--         shortestPaths = relaxEdges costs