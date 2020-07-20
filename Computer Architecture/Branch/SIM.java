// Phong Nguyenho - ph094398
import java.io.*;
import java.util.*;

public class SIM
{	
	public static void main(String [] args) throws Exception
	{	
		// Holds the statistics
		double correctPred = 0;
		double missPred = 0;
		long ghb = 0;

		// Gets the GPB and RB from user
		int m = Integer.parseInt(args[0]);
		int n = Integer.parseInt(args[1]);	
		int numEntries = (int)Math.pow(2, m);


		// Creates a table of entries
		long [] table = new long[numEntries];

		// Initialize table to weakly taken
		Arrays.fill(table, 2);

		// Opens the file to scan lines
		Scanner in = new Scanner(new File(args[2]));

		// Read each line from the input file
		while (in.hasNext())
		{
			// Gets a read or write line from the file
			String [] line = in.nextLine().split(" ");

			// Gets the address from the line
			long pc = Long.parseUnsignedLong(line[0], 16);
			pc = pc / 4;

			// Gets the op from the line
			String outcome = line[1];

			long branchHist = pc % numEntries;

			// Calculates the index
			int index = (int)((ghb << (m - n)) ^ branchHist);

			// Gets the prediction from the table
			long prediction = table[index];

			if (prediction == 2 || prediction == 3) 
			{
				if (outcome.equals("t")) 
					correctPred++;
				else
					missPred++;
			}

			if (prediction == 0 || prediction == 1) 
			{
				if (outcome.equals("t")) 
					missPred++;
				else
					correctPred++;
			}

			// If the branch was taken
			if (outcome.equals("t")) 
			{
				table[index]++;

				if (table[index] > 3)
					table[index] = 3;

				if (n != 0)
					ghb = (ghb >> 1) | (long)Math.pow(2, n - 1);
			}

			// If the branch was not taken
			if (outcome.equals("n"))
			{
				table[index]--;

				if (table[index] < 0) 
					table[index] = 0;

				if (n != 0) 
					ghb = ghb >> 1;
			}
		}

		// Calculate the miss ratio
		double missRatio = (missPred / (missPred + correctPred)) * 100;

		// Closes the file
		in.close();

		// Prints out the descriptions
		System.out.println("M: " + m + " N: " + n + " Miss Ratio: " + missRatio);
	}
}
