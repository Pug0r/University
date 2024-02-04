-- zad1 
oddbins :: Int -> [[Int]]
oddbins n = concat [removeDuplicates $ permutate $ nOnes x n | x <- [1, 3..n]]

nOnes :: Int -> Int -> [Int]
nOnes n up = [1 | _ <- [1..n]] ++ [0 | _ <- [1..(up-n)]]

permutate :: (Eq a) => [a] -> [[a]]
permutate [] = [[]]
permutate l = [a:x | a <- l, x <- permutate (deleteFirstOccurence a l [])]

deleteFirstOccurence :: (Eq a) => a -> [a] -> [a] -> [a]
deleteFirstOccurence _ [] buff = buff 
deleteFirstOccurence num (x:xs) buff 
    | x == num = buff ++ xs
    | otherwise = deleteFirstOccurence num xs (buff ++ [x])

removeDuplicates :: Eq a => [a] -> [a]
removeDuplicates [] = []
removeDuplicates (x:xs) = x : removeDuplicates (filter (/= x) xs)

-- O WIELE LATWIEJ I ZWINNIEJ I PIEKNIEJ, ALE NICZEGO NIE ZALUJE:)
oddbins2 :: Int -> [[Int]]
oddbins2 n = filter oddCount (generateBinarySequences n)

generateBinarySequences :: Int -> [[Int]]
generateBinarySequences 0 = [[]]
generateBinarySequences n = [x:xs | x <- [0,1], xs <- generateBinarySequences (n-1)]

oddCount :: [Int] -> Bool
oddCount xs = odd (sum xs)

-- zad 2
diffsums :: [[Int]] -> [[Int]]
diffsums = foldl helper [[]]

helper :: [[Int]] -> [Int] -> [[Int]]
helper left right 
    | rightSum `elem` leftSum = left
    | otherwise = left ++ [right]
    where 
        leftSum = map sum left 
        rightSum = sum right

-- zad 3
compref :: Eq a => [a] -> [a] -> Int
compref = ((length . filter (uncurry (==))) .) . zip