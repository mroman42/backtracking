{- Función de Backtracking -}
backtracking :: (a -> [a]) -> (a -> Bool) -> a -> [a]
backtracking nodes pred x 
    | (pred x && nodes x == []) = x  
    | pred x = concat map backtracking (nodes x)
    | otherwise = []
                  
{- Mochila -}
type Mochila = [Int]

mochila :: [Int] -> [Int] -> Mochila -> [Mochila]
mochila weights benefits x = backtracking push full x
          where
            push x = 
            