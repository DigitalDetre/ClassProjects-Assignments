# Phong Nguyenho - ph094398

# Returns a 1 if it's a valid word and 0 if it's invalid
def helperSmith(inStr, checker):
	vowels = 'aeiouy'
	check = 0
	sLength = 0
	length = len(inStr)

	# Goes through every letter in the word
	for c in inStr:
		if not (c.isalpha()):
			sLength += 1
		else:
			for n in checker:
				if c == n:
					check = 1
					break
		if (length - sLength) < 4:
			sLength = 0
			return 0

	# Checks the first letter of the word
	for v in vowels:
		if inStr[0].lower() == v:
			return 1
	return check

def word_smith(inStr, checker):
	# Checks for null
	if inStr == None:
		return 0
	elif checker == None:
		checker = ''

	# Gets an array of valid words and sums them
	words = [helperSmith(x, checker) for x in inStr.split(" ") if len(x) > 3]
	return sum(words)

# Recursively gets the quarternary value
def helperBase(decimal):
	if decimal < 4:
		return decimal
	else:
		return helperBase(decimal//4) * 10 + decimal%4

# Recursively gets the sum of the quarternary values
def helperBuilder(base):
	if base < 5:
		return base
	else:
		return helperBuilder(base//10) + base%10

# Gateway to recursive function
def base_builder(decimal):
	# Checks for null
	if decimal == 0 or decimal == None:
		return (0, 0)

	# Gets quaternary value first
	base = helperBase(decimal)

	# Gets the sum of the quarternary value representation
	if decimal < 5:
		return (helperBuilder(base), base)
	else:
		return (helperBuilder(base), base)