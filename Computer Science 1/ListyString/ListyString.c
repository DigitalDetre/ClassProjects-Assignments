// Phong Nguyenho - ph094398

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListyString.h"

#define BUFFER 1024

// Deletes key from string
void listyDel(ListyString *listy, char key);

int main(int argc, char **argv)
{
	// Incase there are more than or less than two arguments
	if (argc == 2)
		processInputFile(argv[1]);

	return 0;
}

int processInputFile(char *filename)
{
	ListyString *listy;
	FILE *file;
	char buffer[BUFFER];
	char *temp;
	char *tempStr;

	file = fopen(filename, "r");
	if (file == NULL)
		return 1;

	// Gets the string and truncates the null terminator
	// Creates listy with string
	fgets(buffer, BUFFER, file);
	tempStr = malloc(sizeof(char) * (strlen(buffer) - 1));
	sscanf(buffer, "%s", tempStr);
	listy = createListyString(tempStr);
	free(tempStr);

	// Loops through the text file line by line until it hits the end
	while(fgets(buffer, BUFFER, file) != NULL)
	{
		if (buffer[0] == '!')
			printListyString(listy);

		if (buffer[0] == '?')
			printf("%d\n", listy->length);

		// Goes through the line and gets the replace string and truncates the null terminator then
		// Passes through the replace function with key
		if (buffer[0] == '@')
		{
			temp = strtok(buffer, " ");
			temp = strtok(NULL, " ");
			temp = strtok(NULL, " ");
			tempStr = malloc(sizeof(char) * (strlen(temp) - 1));
			sscanf(temp, "%s", tempStr);
			replaceChar(listy, buffer[2], tempStr);
			free(tempStr);
		}

		// Goes through the line and gets the string and truncates the null terminator then
		// Passes through the concatenate function
		if (buffer[0] == '+')
		{
			temp = strtok(buffer, " ");
			temp = strtok(NULL, " ");
			tempStr = malloc(sizeof(char) * (strlen(temp) - 1));
			sscanf(temp, "%s", tempStr);
			listy = listyCat(listy, tempStr);
			free(tempStr);
		}

		// Deletes the key from the list
		if (buffer[0] == '-')
			listyDel(listy, buffer[2]);

		// Reverses the list
		if (buffer[0] == '~')
			reverseListyString(listy);
	}

	fclose(file);
	destroyListyString(listy);
	return 0;
}

ListyString *createListyString(char *str)
{
	if (str == NULL || str[0] == '\0')
	{
		ListyString *listy = malloc(sizeof(ListyString));
		if (listy == NULL)
			return NULL;
		listy->head = NULL;
		listy->length = 0;

		return listy;
	}

	int i = 0;
	ListyNode *temp;

	// Allocates memory for LinkedList and gets length of string
	ListyString *listy = malloc(sizeof(ListyString));
	if (listy == NULL)
		return NULL;
	listy->head = NULL;
	listy->length = strlen(str);

	// If there is just one character in the string then just create a head
	if (listy->length < 2)
	{
		listy->head = malloc(sizeof(ListyNode));
		if (listy->head == NULL)
		{	
			free(listy);
			return NULL;
		}
		listy->head->data = str[i];
		listy->head->next = NULL;

		return listy;
	}

	// Loops through each character of string and inserts at the end
	// If head has nothing then create head first
	while (i < listy->length - 1)
	{
		if (listy->head == NULL)
		{
			listy->head = malloc(sizeof(ListyNode));
			if (listy->head == NULL)
			{	
				free(listy);
				return NULL;
			}
			listy->head->data = str[i];
			listy->head->next = NULL;
			temp = listy->head;
		}
		if (temp->next == NULL)
		{
			temp->next = malloc(sizeof(ListyNode));
			temp->next->data = str[i + 1];
			temp->next->next = NULL;
		}
		temp = temp->next;
		i++;
	}
	return listy;
}
ListyString *destroyListyString(ListyString *listy)
{
	if (listy == NULL)
		return NULL;
	else if (listy->head == NULL)
	{
		free(listy);
		return NULL;
	}

	ListyNode *temp = NULL;

	// Saves listy->head in a temp then sets listy->head to next then frees the temp while keeping
	// Track of the next node and frees listy at the end
	while (listy->head != NULL)
	{
		temp = listy->head;
		listy->head = listy->head->next;
		free(temp);
	}

	free(listy);
	return NULL;
}
ListyString *cloneListyString(ListyString *listy)
{
	if (listy == NULL)
		return NULL;
	else if (listy->head == NULL)
	{
		ListyString *newListy = malloc(sizeof(ListyString));
		if (newListy == NULL)
			return NULL;
		newListy->head = NULL;
		newListy->length = 0;
		return newListy;
	}

	int i = 0;
	ListyNode *tempNewListy;
	ListyNode *tempListy;

	// Allocates memory for NewLinkedList and copies length of string
	ListyString *newListy = malloc(sizeof(ListyString));
	if (newListy == NULL)
		return NULL;
	newListy->head = NULL;
	newListy->length = listy->length;

	// Loops through each node until end of string and copies data from old list
	while (i < newListy->length - 1)
	{
		if (newListy->head == NULL)
		{
			newListy->head = malloc(sizeof(ListyNode));
			if (newListy->head == NULL)
			{	
				free(newListy);
				return NULL;
			}
			newListy->head->data = listy->head->data;
			newListy->head->next = NULL;
			tempNewListy = newListy->head;
			tempListy = listy->head;
		}
		if (tempNewListy->next == NULL)
		{
			tempNewListy->next = malloc(sizeof(ListyNode));
			tempNewListy->next->data = tempListy->next->data;
			tempNewListy->next->next = NULL;
		}
		tempNewListy = tempNewListy->next;
		tempListy = tempListy->next;
		i++;
	}

	return newListy;
}
void replaceChar(ListyString *listy, char key, char *str)
{
	if (listy == NULL || listy->head == NULL)
		return;
	else if (str == NULL || str[0] == '\0')
	{
		listyDel(listy, key);
		return;
	}

	ListyNode *temp = listy->head;
	ListyNode *tempNext = NULL;

	int i = 0, j = 0, num = 0;
	int len = strlen(str);

	// Goes through nodes looking for key, once key is found, replace the character in that node and
	// Cuts the list after the node and then inserts the rest of the new string
	// While saving temp->next in a temp so that it can be append at the end of the inner loop
	// Updates listy->length at the end
	while (i < listy->length)
	{
		if (temp->data == key)
		{
			temp->data = str[0];
			tempNext = temp->next;
			temp->next = NULL;

			while (j < len - 1)
			{
				if (temp->next == NULL)
				{
					temp->next = malloc(sizeof(ListyNode));
					temp->next->data = str[j + 1];
					temp->next->next = NULL;
				}
				temp = temp->next;
				j++;
			}
			j = 0;
			num++;
			temp->next = tempNext;
		}
		temp = temp->next;
		i++;
	}
	listy->length += num * (len - 1);
}
void reverseListyString(ListyString *listy)
{
	if (listy == NULL || listy->head == NULL || listy->length < 2)
		return;

	ListyString *temp = listy;
	ListyNode *tempPrev = NULL;
	ListyNode *tempNext = NULL;

	// Goes through the list and stores the head->next to a tempNext and nulls head->next
	// Stores head in a tempPrev and then sets head to tempNext which holds head->next
	// Sets head to tempPrev at the end
	// (Saves next pointer before setting next pointer to previous thing)
	while (temp->head != NULL)
	{
		tempNext = temp->head->next;
		temp->head->next = tempPrev;
		tempPrev = temp->head;
		temp->head = tempNext;
	}
	temp->head = tempPrev;
}
void listyDel(ListyString *listy, char key)
{
	if (listy == NULL || listy->head == NULL)
		return;
	else if (listy->length < 2 && listy->head->data == key)
	{
		free(listy->head);
		listy->head = NULL;
		listy->length -= 1;
		return;
	}

	int i = 0;
	ListyString *temp = listy;
	ListyNode *tempHead = listy->head;
	ListyNode *tempPrev = NULL;

	// Deletes the instance of key in the head and every consecutive key if it appears after
	// Until it hits a node that doesn't have the key
	while(tempHead != NULL && tempHead->data == key)
	{
		temp->head = tempHead->next;
		free(tempHead);
		tempHead = NULL;
		tempHead = temp->head;
		i++;
	}

	// Deletes every instance of key after head
	while (tempHead != NULL)
	{
		while (tempHead != NULL && tempHead->data != key)
		{
			tempPrev = tempHead;
			tempHead = tempHead->next;
		}

		if (tempHead == NULL)
			break;

		tempPrev->next = tempHead->next;
		free(tempHead);
		tempHead = NULL;
		tempHead = tempPrev->next;
		i++;
	}
	listy->length -= i;
}
ListyString *listyCat(ListyString *listy, char *str)
{
	if (listy == NULL && str == NULL)
		return NULL;
	else if (listy == NULL && str[0] == '\0')
	{
		ListyString *newListy = malloc(sizeof(ListyString));
		if (newListy == NULL)
			return NULL;
		newListy->head = NULL;
		newListy->length = 0;

		return newListy;
	}
	else if (listy == NULL && str != NULL)
		return createListyString(str);
	else if (str == NULL || str[0] == '\0')
		return listy;

	int i = 0;
	int len = strlen(str);
	ListyNode *temp = NULL;

	// Checks if listy is an empty string if it is then inserts string
	if (listy->head == NULL)
	{
		listy->length = strlen(str);
		while(i < listy->length - 1)
		{
			if (listy->head == NULL)
			{
				listy->head = malloc(sizeof(ListyNode));
				if (listy->head == NULL)
				{	
					free(listy);
					return NULL;
				}
				listy->head->data = str[i];
				listy->head->next = NULL;
				temp = listy->head;
			}
			if (temp->next == NULL)
			{
				temp->next = malloc(sizeof(ListyNode));
				temp->next->data = str[i + 1];
				temp->next->next = NULL;
			}
			temp = temp->next;
			i++;
		}
		return listy;
	}

	temp = listy->head;

	// Goes to the end of the list and then inserts new string
	// Updates listy->length at the end
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			while (i < len)
			{
				if (temp->next == NULL)
				{
					temp->next = malloc(sizeof(ListyNode));
					temp->next->data = str[i];
					temp->next->next = NULL;
				}
				temp = temp->next;
				i++;
			}
			break;
		}
		temp = temp->next;
	}
	listy->length += len;
	return listy;
}
int listyCmp(ListyString *listy1, ListyString *listy2)
{
	if (listy1 == NULL && listy2 == NULL)
	{
		return 0;
	}
	else if ((listy1 == NULL && listy2->head == NULL) || (listy1->head == NULL && listy2 == NULL))
	{
		return 1;
	}
	else if (listy1->head == NULL && listy2->head == NULL)
	{
		return 0;
	}
	else if ((listy1->length > listy2->length) || (listy1->length < listy2->length))
	{
		return 1;
	}

	int check = 0;
	ListyNode *temp1 = listy1->head;
	ListyNode *temp2 = listy2->head;

	// Goes through both list if they are the same length and checks if the data are the same
	while (temp1 != NULL && temp2 != NULL)
	{
		check++;
		if (temp1->data == temp2->data)
		{
			check = 0;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	if (check != 0)
		return 1;
	return 0;
}
int listyLength(ListyString *listy)
{
	if (listy == NULL)
	{
		return -1;
	}
	else if (listy->head == NULL)
	{
		return 0;
	}
	return listy->length;
}
void printListyString(ListyString *listy)
{
	if (listy == NULL || listy->head == NULL)
	{
		printf("(empty string)\n");
		return;
	}
	ListyNode *temp = listy->head;

	while (temp != NULL)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

double difficultyRating(void)
{
	return 4.5;
}
double hoursSpent(void)
{
	return 50.0;
}
