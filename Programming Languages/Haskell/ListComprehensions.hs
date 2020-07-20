-- Phong Nguyenho
-- ph094398

multipleOf5 x = [x | x <- [1..x], mod x 5 == 0]

multipleOf7Or11 x = [x | x <- [1..x], mod x 7 == 0 || mod x 11 == 0]

multipleOf3And7 x = [x | x <- [1..x], mod x 3 == 0 && mod x 7 == 0]