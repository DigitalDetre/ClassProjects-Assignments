// Phong Nugyenho - ph094398
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	long long unsigned int mapAddr = atoll(argv[1]);
	long long unsigned int page = mapAddr / 4096;
	long long unsigned int offset = mapAddr % 4096;

	printf("The address %llu contains:\n", mapAddr);
	printf("page number = %llu\n", page);
	printf("offset = %llu\n", offset);
	return 0;
}