-- zad 1
cztery :: [Int] -> Int
cztery (x:xs) = foldl max 0 (map length (filter (\x -> (foldl (+) 0 x) `mod` 4 == 0) (podlisty (x:xs))))

podlisty :: [Int] -> [[Int]]
podlisty [] = [[]]
podlisty (x:xs) = [take n (x:xs) | n <- [1..(length (x:xs))]] ++ podlisty xs

-- zad 2
-- wyniki :: Double -> [(String, Double)] -> [(String, String)]
-- wy
wyniki :: Double -> [(String, Double)] -> [(String, String)]
wyniki maks lista = map (\x -> (helperSpacja (fst x), helperWynik (snd x))) lista
    where 
        helperWynik :: Double -> String
        helperWynik n 
            | 100 < n || n < 0 = "Nieprawidlowe dane"
            | (90 < n) && (n <= 100) = "5.0"
            | (80 < n) && (n <= 90) = "4.5"
            | (70 < n) && (n <= 80) = "4.0"
            | (60 < n) && (n <= 70) = "3.5"
            | (50 < n) && (n <= 60) = "3.0"
            | n <= 50 = "2.0"
            where 
                procentowy = (n / maks) * 100

helperSpacja :: String -> String
helperSpacja s 
    | first == ' ' && back == ' ' = init (tail s)
    | first == ' ' = tail s 
    | back == ' ' = init s 
    | otherwise = s
    where 
        first = head s
        back = last s
 
-- zad 3

data Bsk a = Pusty | Bnp [a] a Integer

de :: Eq a => Bsk a -> a -> Bsk a
de Pusty x = Bnp [x] x 1
de (Bnp xs p n) x = Bnp (x:xs) p (if x == p then (n+1) else n)

oe :: Bsk a -> a
oe (Bnp xs p n) = p

ue :: Bsk a -> Bsk a
ue (Bnp (x:xs) p n) = Bnp xs p (n-1)

le :: Eq a => Bsk a -> Integer
le (Bnp (x:xs) p n) = n

bsk2l :: Bsk a -> [a]
bsk2l (Bnp (x:xs) p n) = (x:xs)
