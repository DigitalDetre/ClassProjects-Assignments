// Phong Nguyenho - ph094398
/* Modified Marr-Hildreth.c (or marrh.c) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PICSIZE 256
#define MAXMASK 100
#define ON 		255
#define OFF 	0

int pic[PICSIZE][PICSIZE];
double xconv[PICSIZE][PICSIZE];
double yconv[PICSIZE][PICSIZE];
double final[PICSIZE][PICSIZE];
double peaks[PICSIZE][PICSIZE];
double mag[PICSIZE][PICSIZE];
double maskx[MAXMASK][MAXMASK];
double masky[MAXMASK][MAXMASK];
double histogram[PICSIZE];

int main(int argc, char **argv)
{
    int i, j, p, q; 
    int centx = (MAXMASK / 2);
    int centy = (MAXMASK / 2);
    double areaOfTops, hi, lo, maskxval, maskyval, slope, sum1, sum2;
    double maxival = 0, minival = 255;

    // Temp to store the first three lines so that the output doesn't shift
    char fixShift[100];

    FILE *fp1, *fo1, *fo2, *fo3;

    // Input image
    fp1 = fopen(argv[1],"rb");
    if (fp1 == NULL)
    {
    	printf("Unable to open up file to read in.\n");
    	return 1;
    }

    // Loop that gets the first three lines of the input file
    for (i = 0; i < 3; i++)
    	fgets(fixShift, sizeof(fixShift), fp1);

    fo1 = fopen(argv[2],"wb");
    if (fo1 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo1\n");
    	return 1;
    }

    fo2 = fopen(argv[3],"wb");
    if (fo2 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo2\n");
    	return 1;
    }

    fo3 = fopen(argv[4],"wb");
    if (fo3 == NULL)
    {
    	printf("Unable to open up file to write to. Variable: fo3\n");
    	return 1;
    }

    // Gets the sigma to figure out the size of the table
    // Set to 1 to get an exact picture to canny mag and peaks
    double sig = atof(argv[5]);

    // Gets the thresholds
    // lo = 35, hi = 100 to look like canny final
	//double loThreshold = atof(argv[6]);
	//double hiThreshold = atof(argv[7]);

    // Gets a percent to compute threshold
    // 0.05 to get something similar to the final
    double cutOff = atof(argv[6]) * PICSIZE * PICSIZE;

    // Calculates the mask radius from sigma
    int mr = (int)(sig * 3);

    for (i = 0; i < 256; i++)
    	for (j = 0; j < 256; j++)
        	pic[i][j] = getc(fp1);

    // You're done with the input file
    fclose(fp1);

    // Adds the headers to the output files
	fprintf(fo1, "P5\n%d %d\n255\n", PICSIZE, PICSIZE);
	fprintf(fo2, "P5\n%d %d\n255\n", PICSIZE, PICSIZE);
	fprintf(fo3, "P5\n%d %d\n255\n", PICSIZE, PICSIZE);

	// Utilizes the first partial derivatives to make the masks
    for (p = -mr; p <= mr; p++)
    	for (q = -mr; q <= mr; q++)
    	{
    		maskxval = (p * (exp(-(((p * p) + (q * q)) / (2 * (sig * sig))))));
        	maskyval = (q * (exp(-(((p * p) + (q * q)) / (2 * (sig * sig))))));
    		
    		maskx[p + centy][q + centx] = maskxval;
    		masky[p + centy][q + centx] = maskyval;
    	}

    // Scanning code using the masks
    for (i = mr; i <= (256 - mr); i++)
    	for (j = mr; j <= (256 - mr); j++)
    	{
        	sum1 = 0;
        	sum2 = 0;

        	for (p = -mr; p <= mr; p++)
            	for (q = -mr; q <= mr; q++)
            	{
            		sum1 += pic[i + p][j + q] * maskx[p + centy][q + centx];
            		sum2 += pic[i + p][j + q] * masky[p + centy][q + centx];
            	}

        	xconv[i][j] = sum1;
        	yconv[i][j] = sum2;
    	}

    // Computes the magnitude
    for (i = mr; i < (256 - mr); i++)
    	for (j = mr; j < (256 - mr); j++)
    	{
            mag[i][j] = sqrt((xconv[i][j] * xconv[i][j]) + (yconv[i][j] * yconv[i][j]));

            if (mag[i][j] > maxival)
            	maxival = mag[i][j];
    	}

    // Scales the output again
    for (i = 0; i < PICSIZE; i++)
    	for (j = 0; j < PICSIZE; j++)
	    {
        	mag[i][j] = (mag[i][j] / maxival) * 255;
        	fprintf(fo1, "%c", (char)((int)(mag[i][j])));
    	}
	
	for (i = mr; i < (256 - mr); i++)
		for (j = mr; j < (256 - mr); j++)
		{
			if ((xconv[i][j]) == 0.0) 
				xconv[i][j] = .00001;

			slope = yconv[i][j] / xconv[i][j];

			if ((slope <= .4142) && (slope > -.4142))
			{
				if ((mag[i][j] > mag[i - 1][j]) && (mag[i][j] > mag[i + 1][j]))
					peaks[i][j] = 255;
			}
			else if ((slope <= 2.4142) && (slope > .4142))
			{
				if ((mag[i][j] > mag[i - 1][j - 1]) && (mag[i][j] > mag[i + 1][j + 1]))
					peaks[i][j] = 255;
			}
			else if ((slope <= -.4142) && (slope > -2.4142))
			{
				if ((mag[i][j] > mag[i + 1][j - 1]) && (mag[i][j] > mag[i - 1][j + 1]))
					peaks[i][j] = 255;
			}
			else
			{
				if ((mag[i][j] > mag[i][j - 1]) && (mag[i][j] > mag[i][j + 1]))
					peaks[i][j] = 255;
			}
		}

    for (i = 0; i < PICSIZE; i++)
    	for (j = 0; j < PICSIZE; j++)
        	fprintf(fo2, "%c", (char)((int)(peaks[i][j])));

	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
			histogram[(int)mag[i][j]]++;

	for (i = PICSIZE; i > 1; i--)
	{
		areaOfTops += histogram[i];
		if (areaOfTops > cutOff)
			break;
	}

	hi = i;
	lo = .35 * hi;

    for (i = 0; i < 256; i++)
    	for (j = 0; j < 256; j++)
	    	if (peaks[i][j] == 255)
	    	{
	    		if (mag[i][j] > hi)
	    		{
	    			peaks[i][j] = 0;
	    			final[i][j] = 255;
	    		}
	    		else if (mag[i][j] < lo)
	    			peaks[i][j] = final[i][j] = 0;
	    	}

	int moretodo = 1;

	while (moretodo)
	{
		moretodo = 0;

    	for (i = 0; i < 256; i++)
    		for (j = 0; j < 256; j++)	    	
	    		if (peaks[i][j] == 255)
		    		for (p = -1; p <= 1; p++)
            			for (q = -1; q <= 1; q++)
            				if (final[i + p][j + q] == 255)
            				{
            					peaks[i][j] = 0;
            					final[i][j] = 255;
            					moretodo = 1;
            				}
	}

	for (i = 0; i < PICSIZE; i++)
    	for (j = 0; j < PICSIZE; j++)
        	fprintf(fo3, "%c", (char)((int)(final[i][j])));

    // You're done writing to the output files
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);

    return 0;
}

