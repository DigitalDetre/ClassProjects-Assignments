// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;

public class TopoPath
{
	public static boolean hasTopoPath(String filename) throws IOException
	{		
		int i, node;
		int cnt = 0, checkPreNode = 0;

		Scanner in = new Scanner(new File(filename));

		int bounds = in.nextInt();
		int link = in.nextInt();
		boolean [][] matrix = new boolean [bounds][bounds];

		// Makes an array to store the number of incoming edges to a vertice
		int [] incoming = new int[bounds];

		// Converts the adjacency list into a matrix and
		// count the number of incoming edges incident to each vertex.
		for (i = 0; i < bounds; i++)
		{
			for (int j = 0; j < link; j++)
			{
				node = in.nextInt() - 1;
				matrix[i][node] = true;
				incoming[node]++;
			}

			// Only read in the next int if we have a next int to go to
			if (in.hasNext())
			{
				link = in.nextInt();
			}
		}

		// Credit to Dr. S for the original code from toposort.java
		// Modified to go through and count unique vertices while checking
		// if the previous node we used is connected to our next one.
		Queue<Integer> q = new ArrayDeque<Integer>();

		// Any vertex with zero incoming edges is ready to be visited, so add it to
		// the queue.
		for (i = 0; i < bounds; i++)
			if (incoming[i] == 0)
			{
				q.add(i);
			}

		while (!q.isEmpty())
		{
			// Gets the node(vertice) so that we can check for 
			// edge that we can use
			node = q.remove();

			// Count the number of unique vertices we see.
			// Checks if the node(vertice) we used last is connected
			// to the current node(vertice).
			if (cnt++ > 0 && !matrix[checkPreNode][node]) 
			{
				return false;
			}

			// Saves the node(vertice) to check if it connects to
			// the next node we are going to use.
			checkPreNode = node;

			// All vertices we can reach via an edge from the current vertex should
			// have their incoming edge counts decremented. If one of these hits
			// zero, add it to the queue, as it's ready to be included in our
			// topological sort.
			for (i = 0; i < bounds; i++)
				if (matrix[node][i] && --incoming[i] == 0)
				{
					q.add(i);
				}
		}

		// If the number of vertices visited is equal to the bounds of the matrix
		// that means we have visited all the unique vertices we see
		// which means it's a path.
		if (cnt == bounds)
		{
			return true;
		}

		// If we come here that means we have a cycle
		return false;
	}

	public static double difficultyRating()
	{
		return 1.3;
	}

	public static double hoursSpent()
	{
		return 11.1;
	}
}