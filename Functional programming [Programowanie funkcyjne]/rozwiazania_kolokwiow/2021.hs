import System.IO
import System.Environment

drawNTimes :: Int -> String -> IO ()
drawNTimes 0 _ = return ()
drawNTimes n toDraw = do 
    putStr toDraw 
    drawNTimes (n-1) toDraw
        

-- zad 1 - CHOINKA 
drawTree :: Int -> Int -> IO ()
drawTree height curLevel 
    | curLevel == 1 = do 
            drawNTimes (((height*2)-2)`div`2) " "
            putStr "/\\"
            drawNTimes (((height*2)-2)`div`2) " "
            putStr "\n"
            drawTree height (curLevel+1)
    | curLevel == height+1 = do 
                drawNTimes (height*2) "^"
                putStr "\n"
                drawNTimes (((height*2)-2)`div`2) " "
                putStr "||"
                drawNTimes (((height*2)-2)`div`2) " "
    | otherwise =  do 
                drawNTimes (height-curLevel) " "
                putStr "/"
                drawNTimes ((curLevel-1)*2) " "
                putStr "\\\n"
                drawTree height (curLevel+1)

main :: IO ()
main = do
    putStrLn "Podaj wysokosc choinki"
    userInput <- getLine
    let userInputInt = read userInput :: Int
    drawTree userInputInt 1
    putStr "\n"


-- zad 2 
f :: [(Int, Int)] -> Int -> Int
f (x:xs) u = foldl (*) u (map (uncurry (-))  (x:xs))




        
    