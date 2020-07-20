// Written by Tiger Sachse.
// Small tweaks included by Jtucker1.

import java.io.*;
import java.util.*;

// A test case for ConstrainedTopoSort.
public class Tests {

    // Main entry point of test case.
	public static void main(String [] args) throws IOException {
        testCase1();
        testCase2();
        testCase3();       
    }

    // Run tests on a big, complicated graph.
    private static void testCase1() throws IOException {
		ConstrainedTopoSort topo = new ConstrainedTopoSort("TestGraphs/Graph1.txt");
        Tally tally = new Tally(); 

        // Check that all combinations are possible with the first node as the
        // starting node.
        for (int i = 2; i <= 19; i++) {
            if (!topo.hasConstrainedTopoSort(1, i)) {
                System.out.printf("Failed test 1, pair: (%d, %d)\n", 1, i);
                tally.fails++;
            }
            else {

                tally.passes++;
            }
        }

        // Check terminal nodes.
        tally.add(checkTerminalCase(topo, 5, 1));
        tally.add(checkTerminalCase(topo, 13, 1));
        tally.add(checkTerminalCase(topo, 19, 1));

        // Check non-terminal nodes where all nodes smaller are prior to that node.
        tally.add(checkSimulatedTerminalCase(topo, 9, 1));
        tally.add(checkSimulatedTerminalCase(topo, 10, 1));
        tally.add(checkSimulatedTerminalCase(topo, 6, 1));

        // Invalid x, y pairs in the huge graph.
        Pair invalidPairs[] = {
            new Pair(16, 14),
            new Pair(12, 15),
            new Pair(14, 12),
            new Pair(12, 9),
            new Pair(9, 6),
            new Pair(4, 4),
            new Pair(8, 8),
            new Pair(13, 13),
            new Pair(18, 18),
        };
        tally.add(checkValidity(topo, invalidPairs, 1, false));
	
        // Valid x, y pairs in the huge graph.
        Pair validPairs[] = {
            new Pair(17, 7),
            new Pair(13, 14),
            new Pair(19, 5),
            new Pair(3, 13),
        };
        tally.add(checkValidity(topo, validPairs, 1, true));

        // Print the results from the tally.
        System.out.printf("Passed %d pair%s in test 1.\n",
                          tally.passes,
                          (tally.passes == 1) ? "" : "s");
        System.out.printf("Failed %d pair%s in test 1.\n",
                          tally.fails,
                          (tally.fails == 1) ? "" : "s");
	}

    // Run tests on a disconnected graph.
    private static void testCase2() throws IOException {
		ConstrainedTopoSort topo = new ConstrainedTopoSort("TestGraphs/Graph2.txt");
        Tally tally = new Tally();
       
        // Invalid x, y pairs in the disconnected graph.
        Pair invalidPairs[] = {
            new Pair(2, 1),
            new Pair(3, 2),
            new Pair(5, 4),
        };
        tally.add(checkValidity(topo, invalidPairs, 2, false)); 
       
        // Valid x, y pairs in the disconnected graph.
        Pair validPairs[] = {
            new Pair(1, 2),
            new Pair(4, 5),
            new Pair(2, 3),
            new Pair(5, 1),
            new Pair(1, 5),
            new Pair(4, 2),
            new Pair(2, 4),
            new Pair(6, 2),
            new Pair(6, 1),
            new Pair(6, 4),
            new Pair(4, 6),
        };
        tally.add(checkValidity(topo, validPairs, 2, true));

        // Print the results from the tally.
        System.out.printf("Passed %d pair%s in test 2.\n",
                          tally.passes,
                          (tally.passes == 1) ? "" : "s");
        System.out.printf("Failed %d pair%s in test 2.\n",
                          tally.fails,
                          (tally.fails == 1) ? "" : "s");
    }
    
    // Run tests on a graph with a cycle.
    private static void testCase3() throws IOException {
        ConstrainedTopoSort topo = new ConstrainedTopoSort("TestGraphs/Graph3.txt");

        Tally tally = new Tally();

        // All pairs are invalid for graphs with cycles.
        Pair invalidPairs[] = {
            new Pair(3, 3),
            new Pair(5, 6),
            new Pair(4, 6),
            new Pair(1, 2),
            new Pair(1, 5),
            new Pair(1, 3),
            new Pair(1, 7),
            new Pair(2, 1),
            new Pair(3, 4),
            new Pair(6, 4),
            new Pair(4, 2),
            new Pair(5, 7),
            new Pair(5, 5),
            new Pair(7, 7),
            new Pair(8, 8),
            new Pair(20, 20),
        };
        tally.add(checkValidity(topo, invalidPairs, 3, false));
        
        // Print the results from the tally.
        System.out.printf("Passed %d pair%s in test 3.\n",
                          tally.passes,
                          (tally.passes == 1) ? "" : "s");
        System.out.printf("Failed %d pair%s in test 3.\n",
                          tally.fails,
                          (tally.fails == 1) ? "" : "s");
    }

    // Check the validity of each pair in the graph against the expected boolean.
    private static Tally checkValidity(ConstrainedTopoSort topo,
                                       Pair pairs[],
                                       int testNumber,
                                       boolean expected) {
        Tally tally = new Tally();

        // Check every pair.
        for (int i = 0; i < pairs.length; i++) {
            if (topo.hasConstrainedTopoSort(pairs[i].x, pairs[i].y) != expected) {
                System.out.printf("Failed test %d, pair: (%d, %d)\n",
                                  testNumber,
                                  pairs[i].x,
                                  pairs[i].y);
                tally.fails++;
            }
            else {
                tally.passes++;
            }
        }

        // Return the tally of passes and fails.
        return tally;
    }

    // Check nodes with all smaller nodes prior in the graph.
    private static Tally checkSimulatedTerminalCase(ConstrainedTopoSort topo,
                                                    int terminus,
                                                    int testNumber) {
        Tally tally = new Tally();
        
        for (int i = 1; i < terminus; i++) {
            if (topo.hasConstrainedTopoSort(i, terminus) != true) {
                System.out.printf("Failed test %d, pair: (%d, %d)\n", testNumber, i, terminus);
                tally.fails++;
            }
            else {
                tally.passes++;
            }
        }

        // Return the tally of passes and fails.
        return tally;
    }

    // Check nodes that have no out edges in the graph.
    private static Tally checkTerminalCase(ConstrainedTopoSort topo,
                                           int terminus,
                                           int testNumber) {
        Tally tally = new Tally();

        for (int i = 1; i <= 19; i++) {
            if (i == terminus) {
                continue;
            }

            if (topo.hasConstrainedTopoSort(i, terminus) != true) {
                System.out.printf("Failed test %d, pair: (%d, %d)\n", testNumber, i, terminus);
                tally.fails++;
            }
            else {
                tally.passes++;
            }
        }

        // Return the tally of passes and fails.
        return tally;
    }
}

// Class to contain a count of passes and fails in a particular test case.
class Tally {
    int passes;
    int fails;

    // Constructor that sets both members to zero.
    public Tally() {
        passes = 0;
        fails = 0;
    }

    // Add the values of a foreign tally to this tally.
    public void add(Tally tally) {
        passes += tally.passes;
        fails += tally.fails;
    }
}

// Class to hold an x, y pair.
class Pair {
    int x;
    int y;

    // Constructor for a pair with given values for x and y.
    public Pair(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
