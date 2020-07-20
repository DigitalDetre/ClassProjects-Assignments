// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;
import java.awt.*;

public class SneakyKnights
{
	public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		// The knight's movements
		int [][] knightMoves = {{-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {1, 2}, {1, -2}};

		// Hash set to hold the knight's position after being checked
		HashSet<Point> hashCoord = new HashSet<Point>();

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

			// Creates the knight with integer coordinates
			Point knight = new Point(colInt, rowInt);

			// Modifies the coordinates into the knight's moves and checks them in a hash set
			for (int [] move : knightMoves)
			{
				// Takes the knight's coordinates and turns it into an attack space
				Point attackSpace = new Point(colInt + move[0], rowInt + move[1]);

				// If the attack space hits a knight's position then return false
				if (hashCoord.contains(attackSpace))
					return false;
			}

			hashCoord.add(knight);
		}

		return true;
	}

	public static double difficultyRating()
	{
		return 2.3;
	}

	public static double hoursSpent()
	{
		return 6.0;
	}
}