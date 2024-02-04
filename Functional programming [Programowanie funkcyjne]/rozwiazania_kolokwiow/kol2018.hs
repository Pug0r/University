-- zad 1

a :: Integer -> Integer
a 0 = 1
a n = (n-1) * (b (n-1)) - 3 * (a (n-1))

b :: Integer -> Integer
b 0 = 1
b n = 3 * (b (n-1)) + (n-1)*(n-1)*(a (n-1)) - (n-1)*(n-1)

helperSum :: Integer -> Integer
helperSum n = sum [a m | m <- [1..n]]

seqIndex :: Integer -> Integer
seqIndex m = head [k | k <- [1..], (helperSum k) >= m]

-- zad 2
data Expr a = Value a
    | Add (Expr a) (Expr a)
    | Mul (Expr a) (Expr a)
    | Sub (Expr a) (Expr a)
    | P




-- zad 3

-- cykl :: [a] -> Int -> [[a]]
-- cykl (x:xs) i 
--     | (length (x:xs)) == (i) = []
--     | otherwise = foldl f [x] xs : cykl (xs++[x]) (i+1)
--     where
--         f a b = a ++ [b]

cykl :: [a] -> Int -> [[a]]
cykl _ 0 = []
cykl (x:xs) i = foldl (\x y -> x++[y]) [x] xs : (cykl (xs++[x]) (i-1))



