// Phong Nguyyenho - ph094398

import java.io.*;
import java.util.*;

public class ConstrainedTopoSort
{
	private boolean [][] matrix;
	private int bounds;

	public ConstrainedTopoSort(String filename) throws IOException
	{
		Scanner in = new Scanner(new File(filename));

		bounds = in.nextInt();
		int link = in.nextInt();

		matrix = new boolean [bounds][bounds];

		// Converts the adjacency list into a matrix
		for (int i = 0; i < bounds; i++)
		{
			for (int j = 0; j < link; j++)
			{
				int node = in.nextInt() - 1;
				matrix[i][node] = true;
			}

			// Only read in the next int if we have a next int to go to
			if (in.hasNext())
			{
				link = in.nextInt();
			}
		}
	}

	public boolean hasConstrainedTopoSort(int x, int y)
	{
		// If x and y are the same vertex then x can't
		// have precedence.
		// Checks for a cycle.
		if ((x == y) || !cycleCheck())
			return false;

		// Credit to Dr. S for the original code from toposort.java
		// Modified to do a BFS on x
		Queue<Integer> q = new ArrayDeque<Integer>();

		// Use x as a starting point
		q.add(x - 1);

		// Does a BFS on x to check if
		// y has a precedence over x.
		while (!q.isEmpty())
		{
			// Gets the node(vertice) to do BFS on.
			int node = q.remove();

			// If y has a precedence over the node(vertice) 
			// leading to x then return false.
			if (matrix[y - 1][node])
			{
				return false;
			}

			// Inserts every vertice that have edges to x into the queue.
			for (int i = 0; i < bounds; i++)
				if (matrix[i][node])
				{
					q.add(i);
				}
		}

		// If we have exited the loop, either x is a precedence of y 
		// or they both have the same precedence.
		return true;
	}

	// Credit to Dr. S for the original code from toposort.java
	// Modified to check for a cycle in the graph
	private boolean cycleCheck()
	{
		int cnt = 0;
		int [] incoming = new int [bounds];

		// Count the number of incoming edges incident to each vertex. For sparse
		// graphs, this could be made more efficient by using an adjacency list.
		for (int i = 0; i < bounds; i++)
			for (int j = 0; j < bounds; j++)
			{
				incoming[j] += (matrix[i][j] ? 1 : 0);
			}

		Queue<Integer> q = new ArrayDeque<Integer>();

		// Any vertex with zero incoming edges is ready to be visited, so add it to
		// the queue.
		for (int i = 0; i < bounds; i++)
			if (incoming[i] == 0)
			{
				q.add(i);
			}

		while (!q.isEmpty())
		{
			// Pull a vertex out of the queue and add it to the topological sort.
			int node = q.remove();

			// Count the number of unique vertices we see.
			++cnt;

			// All vertices we can reach via an edge from the current vertex should
			// have their incoming edge counts decremented. If one of these hits
			// zero, add it to the queue, as it's ready to be included in our
			// topological sort.
			for (int i = 0; i < bounds; i++)
				if (matrix[node][i] && --incoming[i] == 0)
				{
					q.add(i);
				}
		}

		// If we pass out of the loop without including each vertex in our
		// topological sort, we must have a cycle in the graph.
		if (cnt != bounds)
		{
			return false;
		}

		return true;
	}

	public static double difficultyRating()
	{
		return 3.4;
	}

	public static double hoursSpent()
	{
		return 26.3;
	}
}