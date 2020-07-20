-- Phong Nguyenho
-- ph094398

isqrt = floor.sqrt.fromIntegral
isPrime 1 = False
isPrime n = isPrimeHelper n [2..(isqrt n)]
    where isPrimeHelper n [] = True
          isPrimeHelper n (x:xs)
           | mod n x == 0 = False
           | otherwise = isPrimeHelper n (xs)

factorial n = go n 1
    where go n ret
           | n > 1 = go (n - 1) (ret * n)
           | otherwise = ret

fibonacci n = [1]++ go n 0 1
    where go n f s
           | n <= 1 = []
           | otherwise = (f + s):go (n - 1) s (f + s)