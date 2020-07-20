// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;

public class RunLikeHell
{
	public static int maxGain(int [] blocks)
	{
		// If there are no blocks then that means the obscure
		// knowledge was inside of the algorithmist all along
		// and there is nothing to be gained.
		if (blocks == null || blocks.length <= 0) 
		{
			return 0;
		}

		// If there is just one block then grab it.
		if (blocks.length == 1) 
		{
			return blocks[0];
		}

		// If there are just two blocks, grab the larger one.
		if (blocks.length == 2)
		{
			return Math.max(blocks[0], blocks[1]);
		}

		int length = blocks.length - 1;

		// Makes an array to store the knowledge gained and
		// initializes the first three indices.
		int [] knowledge = new int[length + 1];
		knowledge[0] = blocks[0];
		knowledge[1] = blocks[1];
		knowledge[2] = blocks[2] + blocks[0];

		// The largest knowledge value gets built up from the
		// initialized indexes.
		for(int i = 3; i < length + 1; i++)
		{
			knowledge[i] += blocks[i] + Math.max(knowledge[i - 2],
												knowledge[i - 3]);
		}

		// The largest value is stored in the last two indexes.
		return Math.max(knowledge[length],
						knowledge[length - 1]);
	}

	public static double difficultyRating()
	{
		return 2.3;
	}

	public static double hoursSpent()
	{
		return 10.5;
	}
}