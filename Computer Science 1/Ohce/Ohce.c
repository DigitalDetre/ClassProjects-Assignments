// Phong Nguyenho - ph094398

#include <stdio.h>
#include <string.h>
#include "Ohce.h"

int main(int argc, char **argv)
{
	int i, j, counter = 0;
	// Checks if there is an argument after argv[0] (./a.out)
	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			int wordCount, minCount = 0;
			wordCount = strlen(argv[i]) - 1;

			// Prints each argument backwards (does not print argv[0])
			for (j = wordCount; j >= 0; j--)
			{
				printf("%c", argv[i][j]);
			}

			// Puts a space after each argument except for the last one
			if (i != (argc - 1))
			{
				printf(" ");
			}

			// Checks for substring "echo" within the string
			while (minCount < wordCount)
			{
				if ((argv[i][minCount] == 'e' || argv[i][minCount] == 'E') && 
					(argv[i][minCount + 1] == 'c' || argv[i][minCount + 1] == 'C') && 
					(argv[i][minCount + 2] == 'h' || argv[i][minCount + 2] == 'H') && 
					(argv[i][minCount + 3] == 'o' || argv[i][minCount + 3] == 'O'))
				{
					counter++;
				}
				else if ((minCount + 3) >= wordCount)
				{
					break;
				}
				minCount++;
			}
		}
		printf("\n");
		if (counter > 0)
		{
			printf("Echo, echo, echo!\n");
		}
	}
	return 0;
}

double difficultyRating(void)
{
	return 3.5;
}

double hoursSpent(void)
{
	return 9.0;
}