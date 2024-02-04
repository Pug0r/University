-- zad 1 
ce :: [[Int]] -> [Int]
ce = foldl (\x y -> if even (sum y) then x ++ y else x) [] 

-- zad 2 
count :: Eq a => a -> [a] -> Int
count x =  length . filter (==x)

uniques :: Eq a => [a] -> [a] -> [a]
uniques [] buffer = buffer
uniques (x:xs) buffer = if x `elem` buffer then uniques xs buffer else uniques xs (buffer++[x])

processString :: [Char] -> String -> IO ()
processString "" _ = return ()
processString (x:xs) whole = do
        print (x, count x whole)
        processString xs whole

main :: IO ()
main = do
    input <- getLine
    if length input == 1 && head input == '.' then return ()
    else do 
        processString (uniques input []) input
        main
