func :: Int -> [String]
func n = filter condition (allPerms (3*n))

condition :: [Char] -> Bool
condition l = 2 * count 'a' l == (count 'b' l + count 'c' l)

allPerms :: Int -> [[Char]]
allPerms 0 = [[]]
allPerms n = [x:xs | x <- ['a','b', 'c'], xs <-allPerms(n-1)]

count :: Eq a => a -> [a] -> Int
count x =  length . filter (==x)