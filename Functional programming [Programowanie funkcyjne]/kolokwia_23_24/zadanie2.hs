silnia :: Int -> Double
silnia = foldl (*) 1.0 . flip take [1..] 

liczbaEulera :: Int -> Double
liczbaEulera = foldl (\x y -> x + (1.0 / (silnia y)) ) 0.0 . flip take [0..]

-- chce wypchnac n na koniec wiec flip i odwracam kolejnosc argumentow i zeby uwolnic 
-- to wyrazenie z map dodaje "." Przy silni to samo rozumowanie.

