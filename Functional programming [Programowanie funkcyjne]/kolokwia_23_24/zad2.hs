f :: Integer -> Integer
f n 
    | even n = n `div` 2
    | odd n = 3*n + 1

countTillOne :: Integer -> Integer -> Integer
countTillOne 1 count = count
countTillOne num count = countTillOne (f num) (count+1)

collatz :: Integer -> [Integer]
collatz n = [countTillOne x 0| x <- [1..n]]