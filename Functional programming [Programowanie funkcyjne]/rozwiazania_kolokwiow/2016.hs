-- zad 2
funcmap list y = foldl (\a b -> a ++ [b (tail a)]) [y] list