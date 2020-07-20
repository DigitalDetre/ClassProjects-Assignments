// Sean Szumlanski
// COP 3503, Summer 2018

// ====================================
// ConstrainedTopoSort: TestCase06.java
// ====================================
// A small test case for ConstrainedTopoSort.


import java.io.*;
import java.util.*;

public class TestCase07
{
	private static void failwhale(String params)
	{
		System.out.println("Test Case #6: hasConstrainedTopoSort(" + params + "): fail whale :(");
		System.exit(0);
	}

	public static void main(String [] args) throws IOException
	{
		ConstrainedTopoSort t = new ConstrainedTopoSort("input_files/g3.txt");

		if (t.hasConstrainedTopoSort(1, 2) != true) failwhale("1, 2");
		if (t.hasConstrainedTopoSort(1, 3) != true) failwhale("1, 3");
		if (t.hasConstrainedTopoSort(2, 3) != true) failwhale("2, 3");

		System.out.println("Test Case #7: PASS (Hooray!)");
	}
}
