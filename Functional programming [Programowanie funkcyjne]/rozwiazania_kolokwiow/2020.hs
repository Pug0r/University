-- zad 1 
f :: [Int] -> [Int]
-- f list = map (\(a,b) -> 3 * (a+b)) (zip list [1..10])
-- mozna usunac map zastepujac ja zipWith:
-- f list = zipWith (\ a b -> 3 * (a + b)) list [1 .. 10]
-- teraz wystarczy zamienic miejscami list i [1..10] 
-- f list = zipWith (\ a b -> 3 * (a + b)) [1 .. 10] list
-- i bezpunktowo:
f = zipWith (\ a b -> 3 * (a + b)) [1 .. 10] 


-- zad 2
usun :: String -> String -> String 
usun a b = foldl helper "" a
    where
        helper :: String -> Char -> String
        helper "" r = [r]
        helper l r = if r `elem` b then l else l++[r]