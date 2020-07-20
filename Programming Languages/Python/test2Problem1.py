# Phong Nguyenho - ph094398

vowels = 'AEIOUYaeiouy'

# Goes through the string and removes the vowels and prints in reverse.
# Does not remove extra spaces because this was not stated in the problem
def test2Problem1(inStr):
	if not inStr:
		return (inStr)
	elif inStr[0] in vowels:
		return (test2Problem1(inStr[1:]))
	return (test2Problem1(inStr[1:]) + inStr[0])
