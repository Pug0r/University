-- samogloski: a e i o u y + wielkie litery!!

czyParzyscieSamoglosek :: String -> Bool
czyParzyscieSamoglosek = even . length . filter (\x -> x `elem` "aeiouyAEIOUY") 

main :: IO ()
main = do
    putStrLn "Witaj, rozmawiasz z HaskGPT. Zadaj pytanie"
    userInput <- getLine
    if czyParzyscieSamoglosek userInput then putStrLn "Tak."
    else putStrLn "Nie."