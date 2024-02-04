-- zad 1 
divBy3 :: Int -> Bool
divBy3 = (==) 0 . flip mod 3 

f :: [[Int]] -> Int
-- f x =  length $ filter divBy3 $ map (length . filter divBy3) x
f =  length . filter divBy3 . map (length . filter divBy3) 

-- zad 2
main :: IO ()
main = do
    input <- getLine
    if length input == 1 && head input == '.' then return ()
    else do 
        print $ reverse input
        main
