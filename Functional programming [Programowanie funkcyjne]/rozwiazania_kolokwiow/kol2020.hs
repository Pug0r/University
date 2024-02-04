-- zad 1
type Point = (Double, Double)

allPairs :: [a] -> [[a]] -> [[a]]
allPairs [] buff = buff
allPairs (x:xs) buff = allPairs xs (buff ++ [[x,y] | y <- xs])

dist :: Point -> Point -> Double
dist (a, b) (c, d) = sqrt (abs((a-c)*(a-c))+abs((b-d)*(b-d)))

minDist :: [Point] -> (Point, Point, Double)
minDist l = (snd(sol)!!0, snd(sol)!!1, fst(sol))
    where 
          sol = foldl minFunc (head zipped) zipped
          pairs = allPairs l []
          pairsDist =  map (\x -> dist (x!!0) (x!!1)) (allPairs l [])
          zipped = zip pairsDist pairs
          minFunc x y 
            | fst x <= fst y = x 
            | otherwise = y 

-- zad 2 

data Tree a = Empty | Node a (Tree a) (Tree a)

findPath :: Eq a => a -> Tree a -> [a]
findPath el tree = findPathHelper el tree []

findPathHelper :: Eq a => a -> Tree a -> [a] -> [a]
findPathHelper el Empty buff = []
findPathHelper el (Node val left right) buff 
  | el == val = buff ++ [val]
  | otherwise = findPathHelper el left (buff++[val]) ++ findPathHelper el right (buff++[val])

-- zad 3
cp :: [Integer] -> [Integer]
cp (x:xs) = helper (x:xs) [] 1 []

helper :: [Integer] -> [Integer] -> Integer -> [Integer] -> [Integer]
helper [] _ _ res = res
helper (x:xs) buf n res 
  | (x > n) || ((containsAll buf n) == False) = helper xs (x:buf) (n+1) res 
  | (x == n) || (containsAll buf n) = helper xs (x:buf) (n+1) (n:res) 
  where containsAll b c = all (==True) $ map (\x -> x `elem` [1..c]) b