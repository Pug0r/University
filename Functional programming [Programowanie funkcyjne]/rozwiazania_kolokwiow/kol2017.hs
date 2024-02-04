-- zad 1
rd :: Integer -> [Integer]
rd 1 = [x | x <- [1..], sum (helperRd x) == 1+x]
rd n = [x | x <- [1..(n*n)], sum (helperRd x) == n+x]

helperRd :: Integer -> [Integer]
helperRd n = [x | x <- [1..n], n `mod` x == 0]

-- zad 2
repl :: Eq a => [a] -> [(a,a)] -> [a]
repl m l = reverse $ foldl (\x y -> swap x y l) [] m

swap :: Eq a => [a] -> a -> [(a,a)] -> [a]
swap prev el l
    | el `elem` map fst l = (translate el l):prev
    | otherwise = el:prev

translate :: Eq a => a -> [(a,a)] -> a
translate z l = snd $ head $ filter (\x -> (fst x) == z) l 

-- zad 3 
data Sdb a = Sdb [a] deriving (Show)

el :: Eq a => Sdb a -> a -> Bool
el (Sdb tree) el = el `elem` tree

eq :: Eq a => Sdb a -> Sdb a -> Bool
eq (Sdb k) (Sdb l) = helperEq k l  
    
helperEq :: Eq a => [a] -> [a] -> Bool
helperEq (x:xs) (y:ys) 
    | lx /= ly = False
    | x /= y = False
    | lx == 1 = True
    | lx == 2 = (head xs) == (head ys)
    | lx == 3 = compTwo xs ys
    | otherwise = helperEq (drop 3 (x:xs)) (drop 3 (x:xs))
    where  
        lx = length (x:xs)
        ly = length (y:ys)

compTwo :: Eq a => [a] -> [a] -> Bool
compTwo (x:xs) (y:ys) = ((x == y) && (head xs == head ys)) || ((x == head ys) && (y == head xs))

sdb2list :: Sdb a -> [a]
sdb2list (Sdb l) = l


    
