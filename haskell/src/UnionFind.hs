module UnionFind(
    isSame,
    unite,
    initTree,
    Tree
) where

import Graph
import Data.Array (Array, array, (!), (//))
type Tree = Array Vertex Vertex

initTree :: Int -> Tree
initTree numVertices = array (0, numVertices-1) [(i, i) | i <- [0..numVertices - 1]]

isSame :: Tree -> Vertex -> Vertex -> Bool
isSame tree from to = let root' = root tree in (root' from) == (root' to)

unite :: Tree -> Vertex -> Vertex -> Tree
unite tree from to = tree // [(root tree from, to)]

root :: Tree -> Vertex -> Vertex
root tree src
    | isLeaf = src
    | otherwise = let root' = root tree in root' (tree ! src)
    where isLeaf = src == (tree ! src)