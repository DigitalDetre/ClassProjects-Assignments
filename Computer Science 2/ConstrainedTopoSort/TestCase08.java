// Sean Szumlanski
// COP 3503, Summer 2018

// ====================================
// ConstrainedTopoSort: TestCase08.java
// ====================================
// A small test case for ConstrainedTopoSort.


import java.io.*;
import java.util.*;

public class TestCase08
{
	private static void failwhale(String params)
	{
		System.out.println("Test Case #8: hasConstrainedTopoSort(" + params + "): fail whale :(");
		System.exit(0);
	}

	public static void main(String [] args) throws IOException
	{
		ConstrainedTopoSort t = new ConstrainedTopoSort("input_files/g4.txt");

		if (t.hasConstrainedTopoSort(8, 2) != true) failwhale("8, 2");
		if (t.hasConstrainedTopoSort(2, 8) != false) failwhale("8, 2");
		if (t.hasConstrainedTopoSort(2, 4) != true) failwhale("2, 4");
		if (t.hasConstrainedTopoSort(4, 2) != true) failwhale("4, 2");
		if (t.hasConstrainedTopoSort(6, 4) != true) failwhale("6, 4");
		if (t.hasConstrainedTopoSort(4, 6) != true) failwhale("4, 6");
		if (t.hasConstrainedTopoSort(3, 7) != true) failwhale("3, 7");
		if (t.hasConstrainedTopoSort(7, 3) != true) failwhale("7, 3");
		if (t.hasConstrainedTopoSort(2, 1) != true) failwhale("2, 1");
		if (t.hasConstrainedTopoSort(1, 2) != true) failwhale("1, 2");
		if (t.hasConstrainedTopoSort(3, 6) != false) failwhale("3, 6");
		if (t.hasConstrainedTopoSort(6, 3) != true) failwhale("6, 3");
		if (t.hasConstrainedTopoSort(1, 5) != true) failwhale("1, 5");
		if (t.hasConstrainedTopoSort(5, 1) != true) failwhale("5, 1");



		System.out.println("Test Case #8: PASS (Hooray!)");
	}
}
