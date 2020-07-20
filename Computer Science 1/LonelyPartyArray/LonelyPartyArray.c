// Phong Nguyenho - ph094398

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	if (num_fragments <= 0 || fragment_length <= 0)
	{
		return NULL;
	}

	int i, j;
	LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));	
	party->size = 0;
	party->num_active_fragments = 0;
	party->num_fragments = num_fragments;
	party->fragment_length = fragment_length;
	party->fragments = malloc(sizeof(int*) * num_fragments);
	party->fragment_sizes = malloc(sizeof(int) * (fragment_length + 1));

	// Checks if malloc has failed
	if (party == NULL)
	{
		return NULL;
	}
	if (party->fragments == NULL)
	{
		free(party);
		return NULL;
	}
	if (party->fragment_sizes == NULL)
	{
		free(party->fragments);
		free(party);
		return NULL;
	}

	// Initializes fragments and fragment sizes to NULL and 0 respectively
	for (i = 0; i < num_fragments; i++)
	{
		party->fragments[i] = NULL;
	}
	for (i = 0; i < fragment_length; i++)
	{
		party->fragment_sizes[i] = 0;
	}

	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", 
	(num_fragments * fragment_length), num_fragments);

	return party;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;

	for (i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
	}

	free(party->fragments);
	free(party->fragment_sizes);
	free(party);

	if (party != NULL)
	{
		printf("-> The LonelyPartyArray has returned to the void.\n");
	}

	return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}

	int i = index / party->fragment_length;
	int j = index % party->fragment_length;
	int k;

	// Checks if out of bounds
	if (party->num_fragments <= i || index < 0)
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, i, j);
		return LPA_FAILURE;
	}

	// Checks if fragment is NULL then allocate memory and puts key into right slot
	// Increments active frag when allocating
	// Increments size if memory has been allocated or if inserted into an UNUSED slot 
	// Increments frag size if UNUSED or allocated
	if (party->fragments[i] == NULL)
	{
		party->fragments[i] = malloc(sizeof(int) * party->fragment_length);

		for (k = 0; k < party->fragment_length; k++)
		{
			party->fragments[i][k] = UNUSED;
		}

		party->size++;
		party->num_active_fragments++;
		party->fragments[i][j] = key;
		party->fragment_sizes[i] += 1;

		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", i, 
			party->fragment_length, ((party->fragment_length) * i), (((party->fragment_length) * (i + 1)) - 1));
		
		return LPA_SUCCESS;
	}
	else if (party->fragments[i][j] == UNUSED)
	{
		party->size++;
		party->fragments[i][j] = key;
		party->fragment_sizes[i] += 1;
		return LPA_SUCCESS;
	}
	else
	{
		party->fragments[i][j] = key;
		return LPA_SUCCESS;
	}

	return LPA_FAILURE;
}

int get(LonelyPartyArray *party, int index)
{
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}

	int i = index / party->fragment_length;
	int j = index % party->fragment_length;

	// Checks if index is out of bounds and if fragment has been allocated, if not return UNUSED
	// If it has been allocated and in bounds then return fragment
	if (party->num_fragments <= i || index < 0)
	{
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, i, j);
		return LPA_FAILURE;
	}
	else if (party->fragments[i] == NULL)
	{
		return UNUSED;
	}
	else
	{
		return party->fragments[i][j];
	}

	return LPA_FAILURE;
}

int delete(LonelyPartyArray *party, int index)
{
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	int i = index / party->fragment_length;
	int j = index % party->fragment_length;

	// Checks if index is out of bounds
	// If in bounds sets fragment cell to UNUSED and decrements fragment sizes and sizes
	if (party->num_fragments <= i || index < 0)
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, i, j);
		return LPA_FAILURE;
	}
	else if (party->fragments[i] == NULL || party->fragments[i][j] == UNUSED)
	{
		return LPA_FAILURE;
	}
	else
	{
		party->fragments[i][j] = UNUSED;
		party->fragment_sizes[i] -= 1;
		party->size--;
	}

	// Checks if there is any cell is being used in fragments by using fragment sizes
	// Frees fragment if all cells in that fragment are UNUSED then set to NULL
	if (party->fragment_sizes[i] == 0)
	{
		party->num_active_fragments--;
		free(party->fragments[i]);
		party->fragments[i] = NULL;
		printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", i, 
			party->fragment_length, ((party->fragment_length) * i), (((party->fragment_length) * (i + 1)) - 1));
	}

	return LPA_SUCCESS;
}

int printIfValid(LonelyPartyArray *party, int index)
{
	if (party == NULL || index < 0)
	{
		return LPA_FAILURE;
	}

	int i = index / party->fragment_length;
	int j = index % party->fragment_length;

	// Checks if out of bounds and UNUSED then prints value if in bounds and not UNUSED
	if (party->num_fragments <= i)
	{
		return LPA_FAILURE;
	}
	else if (party->fragments[i] == NULL || party->fragments[i][j] == UNUSED)
	{
		return LPA_FAILURE;
	}
	else
	{
		printf("%d\n", party->fragments[i][j]);
		return LPA_SUCCESS;
	}

	return LPA_FAILURE;
}

// Makes the party fresh again (It's almost like throwing another party)
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return NULL;
	}

	int i;

	// Puts fragments back to initial state
	for (i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
		party->fragments[i] = NULL;
	}

	// Puts fragment sizes back to initial state
	for (i = 0; i < party->fragment_length; i++)
	{
		party->fragment_sizes[i] = 0;
	}

	party->size = 0;
	party->num_active_fragments = 0;
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", 
		(party->num_fragments * party->fragment_length), party->num_fragments);

	return party;
}

int getSize(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}

	return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}

	// Returns maximum number of integer cells
	return (party->num_fragments * party->fragment_length);
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return -1;
	}

	// Returns maximum number of integer cells without allocating new array fragments
	return (party->fragment_length * party->num_active_fragments);
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return 0;
	}

	// Returns traditional array size, Capacity * sizeof(int)
	return ((long long unsigned int)party->num_fragments * party->fragment_length * sizeof(int));
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return 0;
	}	

	// Returns the optimized array size
	// Party members + party + party pointers + party frags + party length * frags
	return (sizeof(*party) + sizeof(party) + 
		((long long unsigned int)party->num_fragments * sizeof(int*)) + 
		((long long unsigned int)party->num_fragments * sizeof(int)) + 
		((long long unsigned int)party->fragment_length * (party->num_active_fragments) * sizeof(int)));
}

// Makes another party with the same stuff as the party passed through
// (Throwing a very similar party parallel to the original without affecting it)
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
	if (party == NULL)
	{
		return NULL;
	}

	int i, j;
	LonelyPartyArray *clone = malloc(sizeof(LonelyPartyArray));
	clone->size = party->size;
	clone->num_active_fragments = party->num_active_fragments;
	clone->num_fragments = party->num_fragments;
	clone->fragment_length = party->fragment_length;
	clone->fragments = malloc(sizeof(int*) * clone->num_fragments);
	clone->fragment_sizes = malloc(sizeof(int) * ((clone->fragment_length) + 1));
	
	// Checks if malloc has failed
	if (clone == NULL)
	{
		return NULL;
	}
	if (clone->fragments == NULL)
	{
		free(clone);
		return NULL;
	}
	if (clone->fragment_sizes == NULL)
	{
		free(clone->fragments);
		free(clone);
		return NULL;
	}

	// Uses party fragment sizes to figure out which fragments to allocate
	for (i = 0; i < clone->num_fragments; i++)
	{
		clone->fragments[i] = NULL;
		if (party->fragment_sizes[i] > 0)
		{
			clone->fragments[i] = malloc(sizeof(int) * party->fragment_length);
			for (j = 0; j < party->fragment_length; j++)
			{
				clone->fragments[i][j] = party->fragments[i][j];
			}		
		}
	}

	for (i = 0; i < clone->fragment_length; i++)
	{
		clone->fragment_sizes[i] = party->fragment_sizes[i];
	}

	printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n", 
		(clone->num_fragments * clone->fragment_length), clone->num_fragments);

	return clone;
}

double difficultyRating(void)
{
	return 4.3;
}

double hoursSpent(void)
{
	return 35.0;
}