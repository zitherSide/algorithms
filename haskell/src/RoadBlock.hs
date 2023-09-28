module RoadBlock(
    calcSecondShortest
) where

import Graph
import Data.Array (Array, array, range, (!), bounds, (//), assocs)
import Data.Function (on)
import Data.List (minimumBy, sortBy)
import Debug.Trace
import Data.Ix (Ix)
import Data.Ord (Ord)

type Costs = Array Vertex Weight

data VertexCost = VertexCost {
    vertex :: Vertex,
    cost :: Weight
} deriving (Show)

calcSecondShortest :: Vertex -> Vertex -> Graph -> Weight
calcSecondShortest start end graph = seconds ! end
    where
        vRange = (start, end)
        iniShortests = array vRange [(v, if v == start then 0 else infinity) | v <- range vRange]
        iniSeconds = array vRange [(v, infinity) | v <- range vRange]
        (_, seconds) = dijkstra2 [VertexCost{vertex=start, cost=0}] graph iniShortests iniSeconds

update :: VertexCost -> (Costs, Costs, [VertexCost])-> (Vertex, Weight) -> (Costs, Costs, [VertexCost])
update VertexCost{vertex = _, cost =fromCost} (shortests, seconds, unused) edge  = (newShortests, newSeconds, newUnused)
    where
        (next, nextCost) = edge
        newCost = fromCost + nextCost
        oldCost = shortests ! next
        updates = newCost < oldCost
        newShortests = if updates then shortests // [(next, newCost)] else shortests
        unused' = if updates then (VertexCost{vertex = next, cost = newCost}: unused) else unused
        
        new2ndCost = maximum [newCost, oldCost]
        old2ndCost = seconds ! next
        updates2nd = new2ndCost < old2ndCost
        newSeconds = if updates2nd then seconds // [(next, new2ndCost)] else seconds
        newUnused = if updates2nd then (VertexCost{vertex = next, cost = new2ndCost}: unused') else unused'
    

dijkstra2 :: [VertexCost] -> Graph -> Costs-> Costs -> (Costs, Costs)
dijkstra2 [] _ shortests seconds = (shortests, seconds)
dijkstra2 unused graph shortests seconds 
    = dijkstra2 newUnused graph updatedShortests updatedSeconds 
        where
            current :: VertexCost
            residue :: [VertexCost]
            (current: residue) = sortBy (\x y -> compare (cost x) (cost y)) unused

            edges :: [(Vertex, Weight)]
            edges = graph ! (vertex current)

            (updatedShortests', updatedSeconds', newUnused) = foldl (update current) (shortests, seconds, residue) edges
            updatedShortests = trace ("shortests: " ++ show updatedShortests') updatedShortests'
            updatedSeconds = trace ("seconds: " ++ show updatedSeconds') updatedSeconds'
            
thd :: (a, b, c) -> c
thd (_, _, x) = x