// Phong Nguyenho - ph094398

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

#define BUFFER 1024

// Counts the words in the trie
int wordCount(TrieNode *root)
{
	int i = 0, count = 0;

	if (root == NULL)
		return 0;

	if (root->count >= 1)
		count += root->count;

	for (i = 0; i < 26; i++)
	{
		if (root->children[i] != NULL)
			count += wordCount(root->children[i]);
	}

	return count;
}

// Helper function for getMostFrequentWord.
void frequentHelper(TrieNode *root, char *buffer, char *str, int *count, int j)
{
	if (root == NULL)
		return;
	else if (root->count > *count)
	{
		// Gets the count and also the frequently used word.
		*count = root->count;
		strcpy(str, buffer);
	}

	int i = 0;

	buffer[j + 1] = '\0';

	// Goes through every child node for a max count.
	for (i = 0; i < 26; i++)
	{
		buffer[j] = i + 'a';
		frequentHelper(root->children[i], buffer, str, count, j + 1);
	}	

	buffer[j] = '\0';
}

//  Takes a string and removes all punctuation from the string.
void stripPunctuators(char *str)
{
	if (str == NULL)
		return;

	int i = 0, j = 0, len = strlen(str);
	char *tempStr = malloc(sizeof(char) * len);

	// Goes through each character and checks for letters.
	// Saves into a temp and string copies into str.
	while(i < len)
	{
		if (isalpha(str[i]))
		{
			tempStr[j] = str[i];
			j++; 
		}
		i++;
	}
	tempStr[j] = '\0';
	strcpy(str, tempStr);
	free(tempStr);
}

// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// Creates trie and initializes all children nodes to NULL.
TrieNode *createTrieNode(void)
{
	return calloc(1, sizeof(TrieNode));
}

void *insertString(TrieNode *root, char *str)
{
	int i, index, len = strlen(str);

	TrieNode *temp = root;

	for (i = 0; i < len; i++)
	{
		// If it's not a letter then move on to next iteration
		if (!isalpha(str[i]))
			continue;

		index = tolower(str[i]) - 'a';

		// Creates a child node if it does not exist.
		if (temp->children[index] == NULL)
			temp->children[index] = createTrieNode();

		// Move temp to next temp child index.
		temp = temp->children[index];
	}

	// Increment at the last index to show that there is a string there.
	temp->count++;
}

TrieNode *buildTrie(char *filename)
{
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL)
		return NULL;

	TrieNode *root = createTrieNode();
	TrieNode *temp = root;

	char buffer[BUFFER];

	// Inserts word one at a time.
	// Strips the punctuations first.
	while (fscanf(file, "%s", buffer) != EOF)
	{
		stripPunctuators(buffer);
		insertString(root, buffer);

		if (temp->subtrie == NULL)
			temp->subtrie = createTrieNode();
		insertString(temp->subtrie, buffer);

		temp = getNode(root, buffer);
	}

	fclose(file);
	return root;
}

int processInputFile(TrieNode *root, char *filename)
{
	if (root == NULL)
		return 1;

	FILE *file;
	if ((file = fopen(filename, "r")) == NULL)
		return 1;

	int i = 0, num, check = 0;
	char buffer[BUFFER];
	char tempStr[BUFFER];
	TrieNode *temp = NULL;

	while (fscanf(file, "%s", buffer) != EOF)
	{
		// Prints the entire trie
		if (buffer[0] == '!')
			printTrie(root, 0);

		// Prints the word and the next number of predicted words
		else if (buffer[0] == '@')
		{
			fscanf(file, "%s", tempStr);
			fscanf(file, "%s", buffer);
			num = atoi(buffer);
		}

		// Prints the word if it's within the trie and its subtries
		else if (buffer == buffer)
		{
			printf("%s\n", buffer);

			temp = getNode(root, buffer);
			if (temp == NULL)
				printf("(INVALID STRING)\n");
			else if (temp->subtrie == NULL)
				printf("(EMPTY)\n");
			//printTrie(temp->subtrie, 1);
		}
	}

	fclose(file);
	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
	if (root == NULL)
		return NULL;

	int i;

	// Recursive free the children.
	for (i = 0; i < 26; i++)
		destroyTrie(root->children[i]);

	// Frees the subtrie.
	destroyTrie(root->subtrie);

	// Frees the main trie.
	free(root);
	return NULL;
}

// Gets the child node using the string.
TrieNode *getNode(TrieNode *root, char *str)
{
	if (root == NULL || str == NULL || str[0] == '\0')
		return 0;

	int i = 0, index, len = strlen(str);
	TrieNode *temp = root;

	for (i = 0; i < len; i++)
	{
		// If it's not a letter then move on to next iteration
		if (!isalpha(str[i]))
			continue;

		index = tolower(str[i]) - 'a';

		// Checks if next node exists. If not, create it.
		if (temp->children[index] == NULL)
			return NULL;

		// Move temp to next temp index.
		temp = temp->children[index];
	}

	if (temp->count < 1)
		return NULL;

	return temp;
}

void getMostFrequentWord(TrieNode *root, char *str)
{
	if (root == NULL) 
	{
		strcpy(str, "");
		return;
	}
	else if (str == NULL || str[0] == '\0')
		return;

	int count = 0;
	char buffer[BUFFER];

	// Helper function.
	frequentHelper(root, buffer, str, &count, 0);

	//Incase we can't find the most frequent word
	if (count == 0)
		strcpy(str, "");
}

// Checks if the string is within the trie.
int containsWord(TrieNode *root, char *str)
{
	if (root == NULL || str == NULL || str[0] == '\0')
		return 0;

	int i = 0, index, len = strlen(str);
	TrieNode *temp = root;

	for (i = 0; i < len; i++)
	{
		// If it's not a letter then move on to next iteration
		if (!isalpha(str[i]))
			continue;

		index = tolower(str[i]) - 'a';

		// Checks if next node exists.
		if (temp->children[index] == NULL)
			return 0;

		// Move temp to next temp index.
		temp = temp->children[index];
	}

	if (temp->count < 1)
		return 0;

	return 1;
}

int prefixCount(TrieNode *root, char *str)
{
	if (root == NULL || str == NULL)
		return 0;
	else if (str[0] == '\0')
		return wordCount(root);
	
	int i = 0, j = 0, count = 0, len = strlen(str) - 1;

	// Goes through trie and checks if node exists and if it contains a letter of the string.
	// Then at the end of the string add the count or increment by 1 if there is no count.
	for (i = 0; i < 26; i++)
	{
		if (root->children[i] != NULL)
		{
			if ((i == tolower(str[len]) - 'a') && root->count >= 1)
			{
				j = 0;
				return root->count;
			}
			else if ((i == tolower(str[len]) - 'a') && root->count < 1)
			{
				j = 0;
				return count + 1;
			}
			else if (i == (tolower(str[j]) - 'a'))
			{
				j++;
				count = prefixCount(root->children[i], str);
			}
			count += prefixCount(root->children[i], str);
		}
	}
	return count;
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 50.0;
}

int main(int argc, char **argv)
{
	TrieNode *root = NULL;

	// Incase there are more than or less than three arguments
	if (argc == 3)
	{
		root = buildTrie(argv[1]);
		processInputFile(root, argv[2]);
		destroyTrie(root);
	}

	return 0;
}
