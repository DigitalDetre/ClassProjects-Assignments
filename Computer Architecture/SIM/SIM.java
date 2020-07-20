// Phong Nguyenho - ph094398
import java.io.*;
import java.util.*;

class Cache
{
	long [][] tag_array;
	boolean [][] dirty;
	long [][] lru;
	long [][] fifo;
}

public class SIM
{
	private static Cache cache;
	private static int blockSize = 64;
	private static int associativity;
	private static int replacement;
	private static int writeBack;
	private static int num_sets;
	private static long clock = 0;
	private static double hit = 0;
	private static double miss = 0;
	private static int numRead = 0;
	private static int numWrite = 0;

	public static void main(String [] args) throws Exception
	{
		// Gets the cache description from user arguments
		int cacheSize = Integer.parseInt(args[0]);
		associativity = Integer.parseInt(args[1]);
		replacement = Integer.parseInt(args[2]);
		writeBack = Integer.parseInt(args[3]);

		// Gets the total number of sets
		num_sets = cacheSize / blockSize / associativity;

		// Creates the cache struct to store information
		cache = new Cache();

		// Creates the appropiate size arrays
		cache.tag_array = new long[num_sets][associativity];
		cache.dirty = new boolean[num_sets][associativity];
		cache.lru = new long[num_sets][associativity];
		cache.fifo = new long[num_sets][associativity];

		// Initialize the tag array to -1
		for (int i = 0; i < num_sets; i++) 
			Arrays.fill(cache.tag_array[i], -1);	

		// Opens the file to scan lines
		Scanner in = new Scanner(new File(args[4]));

		// Read each line from the input file
		while (in.hasNext())
		{
			// Increments clock cycle
			clock++;

			// Gets a read or write line from the file
			String [] line = in.nextLine().split(" ");

			// Gets the op from the line
			String op = line[0];

			// Gets the address from the line
			long add = stringToLong(line[1]);

			// Simulates a cache based on the arguments the user has inputted
			Simulate_access(op, add);
		}

		// Closes the file
		in.close();

		// Calculates the hit ratio
		double hitRatio = hit / (miss + hit);

		// Calculates the miss ratio
		double missRatio = miss / (miss + hit);

		// Prints out the cache descriptions
		System.out.println("Cache Descriptions");
		System.out.println("---------------------------------------");
		System.out.println("Cache Size: " + cacheSize);
		if (writeBack == 0)
			System.out.println("Write Policy: Write-Through");
		else
			System.out.println("Write Policy: Write-Back");
		System.out.println("Cache Associativity: " + associativity);
		if (replacement == 0) 
			System.out.println("Replacement Policy: Least Recently Used");
		else
			System.out.println("Replacement Policy: First In First Out");

		// Prints a new line
		System.out.println();

		// Prints out the cache statistics
		System.out.println("Cache Statistics");
		System.out.println("---------------------------------------");
		System.out.println("Hit Ratio: " + hitRatio);
		System.out.println("Miss Ratio: " + missRatio);
		System.out.println("Number of Writes to Memory: " + numWrite);
		System.out.println("Number of Reads from Memory: " + numRead);
	}

	public static void Simulate_access(String op, long add)
	{		
		// Gets the tag from the address
		long tag = Long.divideUnsigned(add, blockSize);

		// Gets the set from the address
		long temp = tag % num_sets;
		int set = (int)temp;

		// Checks to see if there is a hit/miss and sets index accordingly
		int index = getHit(tag, set);

		// Checks to see if the set row is full
		boolean flagFull = isFull(set);

		// If there is a miss then get index with replacement policy or fill set row
		if (index == -1) 
		{
			// If the set row is empty get the index
			if (!flagFull)
				index = freeSpace(set);

			// If it is full get the index based on replacement policy
			else
				if (replacement == 0)
					index = LRU(set);
				else
					index = FIFO(set);

			// Updates the FIFO only on a miss
			cache.fifo[set][index] = clock;

			// Checks the dirty bit for a write back
			if (cache.dirty[set][index] && (writeBack == 1))
				numWrite++;

			// Sets the dirty bit if there is a write miss
			if (op.equals("W"))
				cache.dirty[set][index] = true;
			else
				cache.dirty[set][index] = false;
		}

		// Sets the dirty bit if there is a write hit
		if (op.equals("W"))
		{
			// Increments number of writes on write hit for write through
			if (writeBack == 0)
				numWrite++;
			cache.dirty[set][index] = true;
		}
		
		// Puts the tag into the array at the set and index
		cache.tag_array[set][index] = tag;

		// Updates the LRU on a hit and miss
		cache.lru[set][index] = clock;
	}

	// Gets the index using LRU logic
	public static int LRU(int set)
	{
		int temp = 0;
		long recentlyUsed = cache.lru[set][0];

		for (int i = 0; i < associativity; i++) 
			if (cache.lru[set][i] < recentlyUsed)
			{
				recentlyUsed = cache.lru[set][i];
				temp = i;
			}
		return temp;
	}

	// Gets the index using FIFO logic
	public static int FIFO(int set)
	{
		int temp = 0;
		long recentlyUsed = cache.fifo[set][0];

		for (int i = 0; i < associativity; i++) 
			if (cache.fifo[set][i] < recentlyUsed)
			{
				recentlyUsed = cache.fifo[set][i];
				temp = i;
			}
		return temp;
	}

	// Check for free space in the set row
	public static int freeSpace(int set)
	{
		for (int i = 0; i < associativity; i++) 
			if (cache.tag_array[set][i] == -1)
				return i;
		return -1;
	}

	// Checks if the set row is full
	public static boolean isFull(int set)
	{
		for (int i = 0; i < associativity; i++) 
			if (cache.tag_array[set][i] == -1) 
				return false;
		return true;
	}

	// Gets the index in the set in which there is a hit
	public static int getHit(long tag, int set)
	{
		for (int i = 0; i < associativity; i++)
			if (cache.tag_array[set][i] == tag)
			{
				hit++;
				return i;
			}

		// Increments the miss counter
		miss++;

		// Increments read on misses
		numRead++;

		return -1;
	}

	// Converts hexadecimal string to a value of type long
	public static long stringToLong(String hexString)
	{
		hexString = hexString.substring(2);
        return Long.parseUnsignedLong(hexString, 16);
    }
}
