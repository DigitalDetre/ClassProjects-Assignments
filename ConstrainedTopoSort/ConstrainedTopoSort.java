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
		// First check for a cycle.
       	if (cycleCheck()) 
        {
        	return false;
        }		

        int i, node;
        int cnt = 0, precX = 0, precY = 0;        
        int [] visited = new int [bounds];

        // For some reason adding an edge to the original matrix
        // does not work.
        boolean [][] matrixCopy = new boolean [bounds][bounds];
 
        for(i = 0; i < bounds; i++)
            for(int j = 0; j < bounds; j++)
                matrixCopy[i][j] = matrix[i][j];

        // Force an edge from x to y, this causes y's precedence to be
        // one more than x so that y is always greater than or equal to x.
		// Therefore it's pushed back a bit when enqueued.
        matrixCopy[x - 1][y - 1] = true;

		// Credit to Dr. S for the original code from toposort.java
		// Modified to mark visited nodes(vertices) and get precedence values
		// for x and y.
        // Array to hold how many incoming edges to each node(vertex)
        int [] incoming = new int[bounds];

		// Count the number of incoming edges incident to each vertex.
        for(i = 0; i < bounds; i++)
            for(int j = 0; j < bounds; j++)
                incoming[j] += (matrixCopy[i][j] ? 1 : 0);

        Queue<Integer> q = new ArrayDeque<Integer>();

        // Any vertex with 0 incoming edges is ready to be visited, so add it
        // to the queue.
        for(i = 0; i < bounds; i++)
            if(incoming[i] == 0)
            {
                q.add(i);
            }

        while(!q.isEmpty())
        {
        	// Marks the node(vertex) as visited.
            visited[cnt] = node = q.remove();

            // Gets precedence number for x
            if(visited[cnt] == x - 1)
            {
                precX = cnt;
            }

            // Gets precedence number for y
            if(visited[cnt] == y - 1)
            {
                precY = cnt;
            }

			// Count the number of unique vertices we see.
            ++cnt;

            // Decrement the number of incoming edges of each vertex that
            // can be visited from the vertex that just got dequeued.
            // If any of these reaches 0, add it to the queue so it can be
            // visited.
            for(i = 0; i < bounds; i++)
                if(matrixCopy[node][i] && --incoming[i] == 0)
                {
                    q.add(i);
                }
        }

        // Compare the precedence numbers, if x has a lower
        // number than y, that means x has precedence over y.
        return (precX < precY);
	}

	// Credit to Dr. S for the original code from toposort.java
	// Modified to check for a cycle in the graph and keep a count of
	// incoming edges to vertices.
	private boolean cycleCheck()
	{
		int [] incoming = new int[bounds];
		int cnt = 0;

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
		return cnt != bounds;
	}

	public static double difficultyRating()
	{
		return 3.4;
	}

	public static double hoursSpent()
	{
		return 31.3;
	}
}