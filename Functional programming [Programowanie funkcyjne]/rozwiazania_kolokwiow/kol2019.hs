-- zad 1
sevens :: Int -> [Int]
sevens n = take n [x | x <- [7..], checkSeven x]

checkSeven :: Int -> Bool
checkSeven x 
        | xMod == 7 && xMod == x = True
        | xMod == x = False
        | otherwise = checkSeven (sumOfDigits x)
        where xMod = x `mod` 10

sumOfDigits :: Int -> Int
sumOfDigits x 
    | x == (x `mod` 10) = x
    | otherwise = (x `mod` 10) + sumOfDigits (x `div` 10)

-- zad 2

-- 1) sprawdzic podzielnosc przez 4
-- 2) wygenerowac wszystkie ciagi ab o dlugosci n/2
-- 3) zmapowac zeby odbic wzgledem ostatniej literki

bp :: Int -> [String]
bp n 
    | n `mod` 4 /= 0 = []
    | otherwise = map (\x -> x ++ reverse x) (filter (\x -> count 'a' x == count 'b' x) (allPerms (n `div` 2)))

allPerms :: Int -> [[Char]]
allPerms 0 = [[]]
allPerms n = [x:xs | x <- ['a','b'], xs <-allPerms(n-1)]

count   :: Eq a => a -> [a] -> Int
count x =  length . filter (==x)

-- zad 3

data Mb a = Mb [a] [a]

dnp :: Mb a -> a -> Mb a 
dnp (Mb p k) el = Mb (el:p) k 

dnk :: Mb a -> a -> Mb a 
dnk (Mb p k) el = Mb p (el:k) 

mb2list :: Mb a -> [a]
mb2list (Mb p k) = p ++ (reverse k)

ull :: Mb a -> Mb a
ull (Mb p k) = Mb [] k 

upl :: Mb a -> Mb a
upl (Mb p k) = Mb p []