// Phong Nguyenho - ph094398
/* Modified Sobel.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int row = 256, col = 256;
int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int masky[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
double ival[256][256];

int main(int argc, char **argv)
{
    int i, j, sum1, sum2;
    int p = 0, q = 0, black = 0, white = 255;
    int col = 256, row = 256;

    // Temp to store the first three lines so that the output doesn't shift
    char fixShift[100];

    // Mask Radius
    int mr = 1;

    double maxival = 0;

    FILE *fp1, *fo1, *fo2, *fo3;

    // Input image
    fp1 = fopen(argv[1], "rb");
    if (fp1 == NULL)
    {
    	printf("Unable to open up file to read in.\n");
    	return 1;
    }

    // Loop that gets the first three lines of the input file
    for (i = 0; i < 3; i++)
    	fgets(fixShift, sizeof(fixShift), fp1);

    // Output image - Magnitude
	fo1 = fopen(argv[2], "wb");
    if (fo1 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo1\n");
    	return 1;
    }

    // Output image - Lo Threshold
    fo2 = fopen(argv[3], "wb");
    if (fo2 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo2\n");
    	return 1;
    }

    // Output image - Hi Threshold
    fo3 = fopen(argv[4], "wb");
    if (fo3 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo3\n");
    	return 1;
    }

    // Gets the thresholds 40 and 110
	double loThreshold = atof(argv[5]);
	double hiThreshold = atof(argv[6]);

    for (i = 0; i < 256; i++)
    	for (j = 0; j < 256; j++)
        	pic[i][j] = getc(fp1);

    // You're done with the input file
    fclose(fp1);

    // Adds the headers to the output files
	fprintf(fo1, "P5\n%d %d\n255\n", row, col);
	fprintf(fo2, "P5\n%d %d\n255\n", row, col);
	fprintf(fo3, "P5\n%d %d\n255\n", row, col);

	// Optimized the scanning code and the magnitude code by combining them
    for (i = mr; i < (256 - mr); i++)
    {
    	for (j = mr; j < (256 - mr); j++)
    	{
    		sum1 = 0;
    		sum2 = 0;

        	for (p =- mr; p <= mr; p++)
            {
            	for (q =- mr; q <= mr; q++)
                {
                	sum1 += pic[i + p][j + q] * maskx[p + mr][q + mr];
                	sum2 += pic[i + p][j + q] * masky[p + mr][q + mr];
                }
            }

            outpicx[i][j] = sum1;
            outpicy[i][j] = sum2;
        }

    	for (j = mr; j < (256 - mr); j++)
        {
            ival[i][j] = sqrt((double)((outpicx[i][j] * outpicx[i][j]) +
            							(outpicy[i][j] * outpicy[i][j])));

            if (ival[i][j] > maxival)
            	maxival = ival[i][j];
    	}        
    }

    // Gives you all three, magnitude, lo, and hi output images.
    for (i = 0; i < 256; i++)
    	for (j = 0; j < 256; j++)
    	{
    		ival[i][j] = (ival[i][j] / maxival) * 255;            
    		fprintf(fo1,"%c",(char)((int)(ival[i][j])));

    		if (ival[i][j] > loThreshold)
    		{
    			fprintf(fo2,"%c",(char)(white));
    		}
    		else
    			fprintf(fo2,"%c",(char)(black));

    		if (ival[i][j] > hiThreshold)
    		{
    			fprintf(fo3,"%c",(char)(white));
    		}
    		else
    			fprintf(fo3,"%c",(char)(black));
    	}

    // You're done writing to the output files
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);

    return 0;
}