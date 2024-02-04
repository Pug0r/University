-- zad 1 
numocc :: Eq a => a -> [[a]] -> [Int]
numocc = helper 
    where helper v = map (length . filter (==v))

-- zad 2
data Op = Add | Mul | Neg
data CT a = Empty | Leaf a | Join (CT a) Op (CT a)

wf :: CT a -> Bool
wf Empty = False
wf (Leaf a) = True
wf (Join Empty Add _) = False
wf (Join Empty Mul _) = False
wf (Join _ Add Empty) = False
wf (Join _ Mul Empty) = False
wf (Join l Neg r) = ((not (wf l)) && wf r) || (wf l && (not (wf r))) 
wf (Join l _ r) = wf l && wf r

eval :: Num a => CT a -> a 
eval Empty = error ("bad tree boy") 
eval (Leaf a) = a 
eval (Join l Neg r) 
    | not (wf (Join l Neg r)) = error ("bad tree boy")
    | wf l = - (eval l)
    | otherwise = - (eval r)
eval (Join l op r) 
    | isCorrect = (operand op) (eval l) (eval r) 
    | otherwise = error ("bad tree boy") 
    where 
        isCorrect = wf (Join l op r)
        operand Add = (+)
        operand Mul = (*)




-- zad 3
h :: [a] -> [a]
h = helper
    where helper l = [l!!i | i <- [0,2..length l -1]]
