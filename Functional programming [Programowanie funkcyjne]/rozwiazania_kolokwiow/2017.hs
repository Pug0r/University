prefixes :: [a] -> [[a]]
prefixes = foldl (\x y -> x ++ [last x ++ [y]]) [[]]
-- prefixes x = [take n x | n <- [0..length x]]