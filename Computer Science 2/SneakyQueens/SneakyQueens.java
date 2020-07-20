// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;

public class SneakyQueens
{
	public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		long startTime = System.nanoTime();

		// Make a hash set for each direction
		HashSet<String> hashCol = new HashSet<String>();
		HashSet<Integer> hashRow = new HashSet<Integer>();
		HashSet<Integer> hashDiag = new HashSet<Integer>();
		HashSet<Integer> negHashDiag = new HashSet<Integer>();

		for (String s : coordinateStrings) 
		{
			// Splits the coordinate string into column strings and row strings
			String [] position = s.split("(?<=\\D)(?=\\d)");
			
			// Converts the row string into its respective value
			int colInt = 0, rowInt = Integer.parseInt(position[1]);

			// Gets the value of the string using j * 26 ^ (k - 1), for k >= 1 
			// j is the alphabet numerical value and k being how many letters are in the column string
			for (int j = 0; j < position[0].length(); j++)
				colInt += (position[0].charAt(j) - 'a' + 1) * Math.pow(26, position[0].length() - j - 1);

			// Checks for collision when inserting column strings into the hash set
			if (hashCol.contains(position[0]))
			{

				long endTime   = System.nanoTime();
				long totalTime = endTime - startTime;
				System.out.println(totalTime);

				return false;
			}
			else
				hashCol.add(position[0]);

			// Checks for collision when inserting row numbers into the hash set
			if (hashRow.contains(rowInt))
			{

				long endTime   = System.nanoTime();
				long totalTime = endTime - startTime;
				System.out.println(totalTime);

				return false;
			}
			else
				hashRow.add(rowInt);

			// Value will always be positive when inserting into a hash set and checking for collisions
			// (y - x + boardsize) positive slope form
			if (hashDiag.contains(rowInt - colInt + boardSize)) 
			{

				long endTime   = System.nanoTime();
				long totalTime = endTime - startTime;
				System.out.println(totalTime);

				return false;
			}
			else
				hashDiag.add(rowInt - colInt + boardSize);

			// Value will always be negative when inserting into a hash set and checking for collisions
			// (y + x - boardsize) negative slope form
			if (negHashDiag.contains(rowInt + colInt - boardSize))
			{

				long endTime   = System.nanoTime();
				long totalTime = endTime - startTime;
				System.out.println(totalTime);

				return false;
			}
			else
				negHashDiag.add(rowInt + colInt - boardSize);
		}

		long endTime   = System.nanoTime();
		long totalTime = endTime - startTime;
		System.out.println(totalTime);

		return true;
	}

	public static double difficultyRating()
	{
		return 2.5;
	}

	public static double hoursSpent()
	{
		return 20.0;
	}
}