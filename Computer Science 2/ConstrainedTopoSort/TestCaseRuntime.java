import java.io.*;

public class TestCaseRuntime
{
	private static int pass = 0;
	private static int fail = 0;

	private static void checkTest(boolean success)
	{
		if (success)
		 	 pass++; 
		else 
			fail++;
	}

	public static void main(String [] args) throws IOException, Exception
	{
		long start = System.nanoTime();
		ConstrainedTopoSort t = new ConstrainedTopoSort("input_files/Graph16.txt");
		for (int i = 0; i < 5; i++)
		{
			checkTest(t.hasConstrainedTopoSort(9999, 10000) == true);
			checkTest(t.hasConstrainedTopoSort(10000, 9999) == false);
		}
		long end = System.nanoTime();
		System.out.println("Passed " + pass + " cases");
		System.out.println("Failed " + fail + " cases");
		System.out.println("Runtime (nanoseconds): " + (end - start));
	}
}
