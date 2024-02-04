data Wnr a = Wnr [[a]] deriving Show

wp :: Wnr a
wp = Wnr [[]]

dl :: Num a => Wnr a -> a -> Wnr a
dl (Wnr (x:xs)) el = Wnr ((el:x):xs)

ts :: Wnr a -> Wnr a
ts (Wnr l) = if null (head l) then (Wnr l) else Wnr ([]:l)

-- jak starczy czasu to wroc tu bo filter hcyba nieptrzbeny
wmax :: Ord a => Wnr a -> [a]
wmax (Wnr (x:xs)) = if null x then map maximum xs else map maximum (x:xs)

wmin :: Ord a => Wnr a -> [a]
wmin (Wnr (x:xs)) = if null x then map minimum xs else map minimum (x:xs)