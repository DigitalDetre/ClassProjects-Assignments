// Phong Nguyenho - ph094398
#include <stdio.h>
#include <stdlib.h>

#define sizeOfPage 256
#define VMSize 256
#define sizeOfTLB 16
#define BUFFER_SIZE 1000

int main(int argc, char **argv)
{
	FILE *bstore = fopen("BACKING_STORE.bin", "rb");
	FILE *aFile = fopen(argv[1], "r");

	int tableNumbers[sizeOfPage];
	int tableFrames[sizeOfPage];
	int memory[VMSize][sizeOfPage];
	int pageNumberOfTLB[sizeOfTLB];
	int frameOfTLB[sizeOfTLB];

	int misses = 0;
	int hits = 0;
	int firstFrame = 0;
	int firstTableNumber = 0; 
	int entries = 0;
	int address;
	char line[BUFFER_SIZE];
	char buffer[sizeOfPage];
	int totalAddresses = 0;

	while (fgets(line, BUFFER_SIZE, aFile) != NULL) 
	{
		address = atoi(line);

		int pageNumber = (address & 0xFFFF) >> 8;
		int offset = address & 0xFF;
		int frameNumber = -1;

		// Tries to find a hit
		for(int i = 0; i < sizeOfTLB; i++)
			if(pageNumberOfTLB[i] == pageNumber)
			{   
				frameNumber = frameOfTLB[i];  
				hits++;
			}

		// If it was a miss
		if(frameNumber == -1)
		{
			for(int i = 0; i < firstTableNumber; i++)
				if(tableNumbers[i] == pageNumber)
					frameNumber = tableFrames[i];   

			// If it is an initialized frame
			if(frameNumber == -1)
			{
				if (fseek(bstore, pageNumber * sizeOfPage, SEEK_SET) != 0) 
					fprintf(stderr, "Error seeking in backing store\n");

				if (fread(buffer, sizeof(char), sizeOfPage, bstore) == 0) 
					fprintf(stderr, "Error reading from backing store\n");        

				for(int i = 0; i < sizeOfPage; i++)
					memory[firstFrame][i] = buffer[i];

				tableNumbers[firstTableNumber] = pageNumber;
				tableFrames[firstTableNumber] = firstFrame;

				firstFrame++;
				firstTableNumber++;
				misses++;
				frameNumber = firstFrame - 1;
			}
		}

		int i;

		// If the page number is already in the TLB then break
		for(i = 0; i < entries; i++)
			if(pageNumberOfTLB[i] == pageNumber)
				break;

		// If the index is equal to the number of entries
		if(i == entries)
			if(entries < sizeOfTLB)
			{
				pageNumberOfTLB[entries] = pageNumber;
				frameOfTLB[entries] = frameNumber;
			}
			else
			{
				for(i = 0; i < sizeOfTLB - 1; i++)
				{
					pageNumberOfTLB[i] = pageNumberOfTLB[i + 1];
					frameOfTLB[i] = frameOfTLB[i + 1];
				}
				pageNumberOfTLB[entries - 1] = pageNumber;
				frameOfTLB[entries - 1] = frameNumber;
			}
		else
		{
			for(i = i; i < entries - 1; i++)
			{
				pageNumberOfTLB[i] = pageNumberOfTLB[i + 1];
				frameOfTLB[i] = frameOfTLB[i + 1];
			}
			if(entries < sizeOfTLB)
			{
				pageNumberOfTLB[entries] = pageNumber;
				frameOfTLB[entries] = frameNumber;
			}
			else
			{
				pageNumberOfTLB[entries - 1] = pageNumber;
				frameOfTLB[entries - 1] = frameNumber;
			}
		}

		// If there is available space in the array
		if(entries < sizeOfTLB)
			entries++;

		char value = memory[frameNumber][offset];
		printf("Virtual address: %d Physical address: %d Value: %d\n", address, (frameNumber << 8) | offset, value);
		totalAddresses++;
	}

	// Calculates the rates
	double missRate = (double)misses / (double)totalAddresses;
	double hitRate = (double)hits / (double)totalAddresses;

	// Prints the statistics
	printf("Page Faults = %d\t\tTLB Hits = %d\n", misses, hits);
	printf("Page Fault Rate = %.3f\t\tTLB Hit Rate = %.3f\n", missRate, hitRate);

	// Closes the files
	fclose(aFile);
	fclose(bstore);

	return 0;
}