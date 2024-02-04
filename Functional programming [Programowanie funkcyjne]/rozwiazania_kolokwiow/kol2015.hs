-- zad 1
-- 'kazde slowo zlozone z a i b, czyli dlugosc conajmniej 2
-- Albo w poleceniu jest blad, albo przyklady sa zle dobrane, bo mowa o przepisywaniu ostatniej
-- litery w wyrazach o nieparzystej dlugosci! 

dlugosc :: String -> Int
dlugosc s = dlugoscHelper (oddHelper s) 0

oddHelper :: String -> String
oddHelper (x:xs) = if (length (x:xs) `mod` 2 == 1) then (x:xs) ++ [last xs] else (x:xs)

dlugoscHelper :: String -> Int -> Int
dlugoscHelper (x:xs) step 
    | null xs || all (=='a') (x:xs) = step
    | otherwise = dlugoscHelper (rules (x:xs) "") (step+1)

rules :: String -> String -> String
rules "" buff = buff
rules (x:y:xs) buff
    | x == 'a' && y == 'b' = rules xs (buff++['a'])
    | x == 'b' && y == 'a' = rules xs (buff++['b'])
    | x == 'b' && y == 'b' = rules xs (buff++['a'])
    | x == 'a' && y == 'a' = rules xs (buff++"aaa")

-- zad 2

val :: Integer -> Integer -> Integer
val a b = lastOrEmpty $ takeWhile (\x -> a `mod` b^x == 0) [1..]
    where 
        lastOrEmpty :: [Integer] -> Integer
        lastOrEmpty l
            | null l = 0
            | otherwise = last l 

g :: Integer -> Integer -> [Integer]
g k v = [n | n <- [2..], (val n k) == v]


-- zad 3 
data Klos a = Klos [a] [a] deriving Show

wnpk :: Klos a -> a -> Klos a
wnpk (Klos p k) el = Klos (el:p) k 

wnkk :: Klos a -> a -> Klos a
wnkk (Klos p k) el = Klos p (el:k) 

k2list :: Klos a -> [a]
k2list (Klos p k) = p ++ (reverse k)