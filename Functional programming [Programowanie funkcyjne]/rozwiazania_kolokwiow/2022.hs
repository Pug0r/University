-- zad 1 - Kamien, papier, nozyce
import System.IO
import System.Environment

--In summary, let is used for local variable bindings within a block, while <- is used to extract 
--values from monadic actions, especially in the context of the do notation.

-- UWAGA getChar wczytuje charakter i zostawia '\n' w bufferze

roundResult ::  Char -> Char -> String
roundResult 'P' 'K' = "Player"
roundResult 'P' 'N' = "Computer" 
roundResult 'K' 'P' = "Computer" 
roundResult 'K' 'N' = "Player"
roundResult 'N' 'P' = "Player"
roundResult 'N' 'K' = "Computer"
roundResult _ _ = "Tie"


playGame :: String -> Int -> IO ()
playGame "" score = print score
playGame (x:xs) c = do
    putStrLn $ "Computer's score: " ++ show c
    putStrLn "Enter your move {P, K, N}"
    userInput <- getLine
    print x
    let result = roundResult (head userInput) x 
    if result == "Player" then playGame xs (c-1)
    else if result == "Computer" then playGame xs (c+1)
    else playGame xs c
    
-- Odkomentuj zeby odpalic
-- main :: IO ()
-- main = do
--     args <- getArgs
--     playGame (head args) 0


-- fromIntegral - convert Integer to Int ! 
-- zad 2 - Dodawanie punktow z przestrzeni n-wymiarowej
dodajPunkty :: Integer -> [[Integer]] -> [Integer]
dodajPunkty = foldl (zipWith (+)) . flip replicate 0 . fromIntegral
-- dodajPunkty d = foldl (zipWith (+)) (replicate (fromIntegral d) 0)

