module BellmanFord
    (
        bellmanFord
    ) where

import Graph
import Data.Array

bellmanFord :: Graph -> Vertex -> Array Vertex (Maybe Weight) -- Array Vertex (Maybe Wight)
bellmanFord graph source = shortestPaths
    where
        vertexRange = bounds graph -- bounds Arrayの有効範囲を返す = vertexの範囲
        vertices = range vertexRange
        numVertices = rangeSize vertexRange

        distances = array vertexRange [(v, if v == source then Just 0 else Nothing) | v <- vertices]   -- v <- x バインド. 非決定性のある値の構築

        relaxEdges :: Array Vertex (Maybe Weight) -> Array Vertex (Maybe Weight)
        relaxEdges dists = foldl relax dists vertices

        relax :: Array Vertex (Maybe Weight) -> Vertex -> Array Vertex (Maybe Weight)
        relax dists u = foldl update dists (graph ! u) -- u頂点のEdgeを抜き出す  -- foldl func seed container
            where 
                update dists (v, weight) = case (dists ! u, dists ! v) of 
                    (Just du, Nothing) -> dists // [(v, Just (du + weight))]    -- array // [...] arrayの該当部分を更新
                    (Just du, Just dv) -> dists // [(v, Just (min dv (du + weight)))]
                    _ -> dists

        -- iterate func seed 無限ループする。A(n+1) = func(A(n)): A(0) = seed となる漸化式に等しい
--         ghci> take 5 $ iterate (map (\x -> x+1)) seed
--          [[0,0,0,0],[1,1,1,1],[2,2,2,2],[3,3,3,3],[4,4,4,4]]
        shortestPaths = iterate relaxEdges distances !! (numVertices + 1) -- Array !! index

        -- snd = second, (isJust . snd) = 関数合成
        detectNegativeCycle :: Array Vertex (Maybe Weight) -> Bool
        detectNegativeCycle dists = any (isJust . snd) $ zip vertices (relaxEdges dists)
