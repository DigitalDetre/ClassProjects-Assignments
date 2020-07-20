// Sean Szumlanski
// COP 3503, Summer 2018

// =========================
// TopoPath: TestCase04.java
// =========================
// This corresponds to graph G2 from the assignment PDF.


import java.io.*;

public class TestCase04
{
	public static void main(String [] args) throws IOException
	{
		System.out.print("Test Case #4: ");

		boolean success = (TopoPath.hasTopoPath("input_files/g2.txt") == false);
		System.out.println(success ? "PASS" : "fail whale :(");
	}
}
