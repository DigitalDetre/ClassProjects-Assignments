# Phong Nguyenho - ph094398

def getPrimes(n):
	pList = [2]
	check = 3
	while len(pList) < n:
		for prime in pList:
			if check % prime == 0:
				break
		else:
			pList.append(check)
		check += 2

    # Return list of prime numbers
	return pList[-1]

def test2Problem2(n):
	if n == 0:
		return 0
	otherPrimes = [getPrimes(x) for x in range(n*2)]
	return otherPrimes[1::2]
