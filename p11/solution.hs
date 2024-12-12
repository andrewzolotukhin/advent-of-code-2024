transform :: Int -> [Int] 
transform 0 = [1] 
transform x 
      | even len = let mid = len `div` 2 in [ read $ take (mid) xTxt, read $ drop mid xTxt] 
      | otherwise = [x * 2024] 
    where 
      xTxt = show x 
      len = length $ xTxt

transformStep :: [Int] -> Int -> [Int] 
transformStep arr step 
        | step == 0 = arr 
        | otherwise = concat $ map transform $ transformStep arr (step - 1) 

main :: IO () 
main = do 
  let input = [1750884, 193, 866395, 7, 1158, 31, 35216, 0] 
  print $ length $ transformStep input 25
