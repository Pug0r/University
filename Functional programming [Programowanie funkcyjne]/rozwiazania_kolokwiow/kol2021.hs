-- zad 1 
type DirectedGraph = ([Int], Int -> Int -> Bool)

-- atDistance :: DirectedGraph -> Int -> Int -> [Int]
-- atDistance g d v = last 
--     where 
--         graph = genGraph g 

atDistance :: DirectedGraph -> Int -> [Int] -> [Int]
atDistance _ _ [] = []
atDistance g 1 v = step v (genGraph g)
atDistance g d v = atDistance g (d-1) (step v (genGraph g))

allPairs :: [a] -> [[a]] -> [[a]]
allPairs [] buff = buff
allPairs (x:xs) buff = allPairs xs (buff ++ [[x,y] | y <- xs])

step :: [Int] ->  [[Int]] -> [Int]
step [] _ = []
step (y:ys) graph = (map (!!1) $ head [filter (\x -> (head x) == y) graph]) ++ (step ys graph)

genGraph :: DirectedGraph -> [[Int]]
genGraph g  = filter graph (allPairs (fst g) [] ++ (map (\x -> [x!!1, x!!0]) (allPairs (fst g) [])))
    where 
        graph (x:y:s) = (snd g) x y
        
grapher :: Int -> Int -> Bool
grapher j k 
    | j == 1 && k == 2 = True
    | j == 1 && k == 4 = True
    | j == 4 && k == 5 = True
    | j == 2 && k == 3 = True
    | j == 5 && k == 1 = True
    | otherwise = False

-- zad 2
wIluListach :: Int -> [[Int]] -> [Int]
wIluListach n l = [length $ filter (\x -> m `elem` x) l | m <- [1..n]]

-- zad 3
data Wr a = Wr [[a]] Bool Integer deriving Show

dg :: Wr a -> [a] -> Wr a
dg (Wr main wasBranched len) g = Wr (g:main) True (len+1)

ug :: Wr a -> Wr a
ug (Wr (x:xs) wasBranched len) = Wr xs wasBranched (len-1)

de :: Wr a -> a -> Wr a
de (Wr (x:xs) wasBranched len) g = Wr ([g:x] ++ xs) False len

ue :: Wr a -> Wr a
ue (Wr (x:xs) wasBranched len) 
    | wasBranched = Wr (x:xs) wasBranched len
    | otherwise = Wr ([drop 1 x] ++ xs) wasBranched len

lg :: Wr a -> Integer
lg (Wr l wasBranched len) = len 

wr2l :: Wr a -> [a]
wr2l (Wr l wasBranched len) = concat l