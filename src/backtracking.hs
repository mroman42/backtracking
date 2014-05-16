-- Función de Backtracking
{- Genera todas las posibles soluciones a un problema de backtracking.
   Pide una función que devuelve los nodos hijos de una pseudosolución
   y una función de poda que devuelva verdadero o falso sobre cada
   pseudosolución.

   Las soluciones sin pseudosoluciones hijas se consideran soluciones finales.
 -}
backtracking :: (a -> [a]) -> (a -> Bool) -> a -> [a]
backtracking nodes pred x
    | (pred x && (length (nodes x) == 0)) = [x]
    | pred x = concat $ map (backtracking nodes pred) (nodes x)
    | otherwise = []
    
{- Mochila -}
type Mochila = ([Int], Int)
mochilaBT :: [Int] -> [Int] -> Int -> Mochila -> [Mochila]
mochilaBT weights benefits limit x = backtracking push isFull x
          where
            totalWeight x = foldr (+) 0 (map (weights !!) x)
            isFull (xs,k) = ((totalWeight xs) > limit)
            push (xs,k)
              | k < (length benefits) = [((xs:k),k+1), (xs,k+1)]
              | otherwise = []
