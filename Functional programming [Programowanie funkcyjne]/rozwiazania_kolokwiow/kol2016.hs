
-- zad 1 
pownum :: Integer -> [Integer]
pownum n = [x | x <- [1..], (sum $ map (^5) (pownumHelper x)) == x]

pownumHelper :: Integer -> [Integer]
pownumHelper 0 = []
pownumHelper l = (l `mod` 10) : pownumHelper (l `div` 10)

-- zad 2
ps :: [a] -> [[a]]
ps l = [foldl helper [] (take n l) | n <- [1..(length l)]] ++ [foldl helper [] (drop n l) | n <- [1..(length l)-1]]
    where
        helper :: [a] -> a -> [a]
        helper x y = x ++ [y]


-- zad 3 

data Rd a = Node a [Rd a] deriving Show

el :: Eq a => Rd a -> a -> Bool
el (Node value children) x = x == value || any (\child -> el child x) children

subst :: Eq a => a -> a -> Rd a -> Rd a
subst old new (Node value children) =
  Node (if value == old then new else value) (map (subst old new) children)

rd2list :: Rd a -> [a]
rd2list (Node value children) = value : concatMap rd2list children

