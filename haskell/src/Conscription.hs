module Conscription(
    intimacies,
    calcMaxIntimacies,
    calcGraphCost,
    calcOrgCost
) where

import Graph
import Data.List (maximumBy, sortBy)
import Data.Function (on)
import UnionFind
import Debug.Trace

intimacies :: TupleEdgeGraph
intimacies = [
    (4, 3, 6831),
    (1, 3, 4583),
    (0, 0, 6592),
    (0, 1, 3063),
    (3, 3, 4975),
    (1, 3, 2049),
    (4, 2, 2104),
    (2, 2, 781)
    ]

from :: (a, b, c) -> a
from (x, _, _) = x

to :: (a, b, c) -> b
to (_, x, _) = x

cost :: (a, b, c) -> c
cost (_, _, x) = x


numMale :: TupleEdgeGraph -> Int
numMale intimacies = 1 + maxVertex
    where
        maxVertex = from $ maximumBy (compare `on` from) intimacies

numFemale :: TupleEdgeGraph -> Int
numFemale intimacies = let maxVertex = to $ maximumBy (compare `on` to) intimacies in 1 + maxVertex

makeGraph :: TupleEdgeGraph -> TupleEdgeGraph
makeGraph intimacies = map (\(from, to, cost) -> (from, offset + to, -cost)) intimacies
    where offset = numMale intimacies

calcMaxIntimacies :: TupleEdgeGraph -> TupleEdgeGraph --TupleEdgeGraph
calcMaxIntimacies intimacies = kruskal (initTree numVertices) [] graph
    where
        graph = makeGraph intimacies
        maxVertex = maximumBy (compare `on` to) graph
        -- numVertices = 1 + (to maxVertex)
        numVertices = trace ("unionfind size: " ++ show (1 + (to maxVertex))) 1 + (to maxVertex)

kruskal :: Tree -> TupleEdgeGraph -> TupleEdgeGraph -> TupleEdgeGraph
kruskal _ mst [] = mst
kruskal unionTree mst candidates = if isIsolated
    then kruskal (unite unionTree (from minEdge) (to minEdge)) (minEdge: mst) residue
    else kruskal unionTree mst residue
    where
        -- (minEdge: residue) = sortBy (compare `on` cost) candidates
        (minEdge: residue) = trace ("sorted: " ++ show (sortBy (compare `on` cost) candidates)) sortBy (compare `on` cost) candidates
        isIsolated = trace ("isIsolated: " ++ show (not (isSame unionTree (from minEdge) (to minEdge)))) not $ isSame unionTree (from minEdge) (to minEdge)
        -- isIsolated = isSame unionTree (from minEdge) (to minEdge)

calcGraphCost :: TupleEdgeGraph -> Weight
calcGraphCost graph = foldl f 0 graph
    where
        f :: (Int -> (Vertex, Vertex, Weight) -> Int)
        f acc (_, _, x) = acc + x

calcOrgCost :: TupleEdgeGraph -> Weight
calcOrgCost intimacies = cost * numPeople
    where
        cost = 10000
        numPeople = trace ("numPeople: " ++ show ((numMale intimacies) + (numFemale intimacies))) (numMale intimacies) + (numFemale intimacies) 