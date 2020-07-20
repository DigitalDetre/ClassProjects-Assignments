// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;

class Node<Anytype extends Comparable<Anytype>> 
{
	Anytype value;
	int height;
	ArrayList<Node<Anytype>> nextNode;

	Node(int height)
	{
		this.height = height;
		nextNode = new ArrayList<Node<Anytype>>();
		for (int i = 0; i < height; i++)
			nextNode.add(null);
	}

	Node(Anytype data, int height)
	{
		this.value = data;
		this.height = height;
		nextNode = new ArrayList<Node<Anytype>>();
		for (int i = 0; i < height; i++)
			nextNode.add(null);
	}

	public Anytype value()
	{
		return this.value;
	}

	public int height()
	{
		return this.height;
	}

	// Gets the next node reference at this level
	public Node<Anytype> next(int level)
	{
		if (level < 0 || level > this.height - 1)
			return null;

		return this.nextNode.get(level);
	}

	// Replaces the node at that level to the node given
	public void setNext(int level, Node<Anytype> node)
	{
		this.nextNode.set(level, node);
	}

	// Adds a null reference to the top
	public void grow()
	{
		nextNode.add(null);
		this.height++;
	}

	// Maybe adds a null reference to the top
	public void maybeGrow()
	{
		Random probability = new Random();

		if (probability.nextBoolean())
		{
			nextNode.add(null);
			this.height++;
		}
	}

	// Removes references from the top until it reaches the required height
	public void trim(int height)
	{
		while (this.height >= height)
		{
			nextNode.remove(this.height - 1);
			this.height--;
		}
	}
}

public class SkipList<Anytype extends Comparable<Anytype>> 
{
	private Node<Anytype> head;
	private int height;
	private int size;

	SkipList()
	{
		height = 1;
		size = 0;
		head = new Node<Anytype>(height);
	}

	SkipList(int height)
	{
		this.height = height;
		size = 0;
		head = new Node<Anytype>(this.height);
	}

	public int size()
	{
		return size;
	}

	public int height()
	{
		return height;
	}

	public Node<Anytype> head()
	{
		return head;
	}

	public void insert(Anytype data)
	{
		int i = 0, nodeHeight = generateRandomHeight(getMaxHeight(++this.size) - 1);
		Node<Anytype> current = head;
		Node<Anytype> temp = head;
		Node<Anytype> newNode = new Node<Anytype>(data, nodeHeight + 1);

		// If inserting causes the skip list to grow then increase height and adjust each valid node
		if (this.height < getMaxHeight(size)) 
		{
			growSkipList();
			this.height++;
		}

		// Starts from the top of the head node and drops a level accordingly,
		// using the algorithm described in class
		while (i++ < size)
		{
			// If the next node is a null reference i.e at the beginning or end of the skip list
			// Insert the node there
			if (current.next(nodeHeight) == null) 
			{
				while (0 <= nodeHeight)
				{
					// If the node reference at the level is not null then connect it to the next node
					if (current.next(nodeHeight) != null) 
					{
						temp = current.next(nodeHeight);
						current.setNext(nodeHeight, newNode);
						current.next(nodeHeight).setNext(nodeHeight--, temp);
					}
					else
						current.setNext(nodeHeight--, newNode);
				}

				break;
			}
			// If the next node value is greater than or equal to the data then insert there
			else if (current.next(nodeHeight).value().compareTo(data) >= 0) 
			{
				while (0 <= nodeHeight)
				{
					if (current.next(nodeHeight) != null) 
					{
						temp = current.next(nodeHeight);
						current.setNext(nodeHeight, newNode);
						current.next(nodeHeight).setNext(nodeHeight--, temp);
					}
					else
						current.setNext(nodeHeight--, newNode);
				}

				break;
			}
			else
			{
				current = current.next(nodeHeight);
			}
		}
	}

	public void insert(Anytype data, int height)
	{
		int i = 0, nodeHeight = height - 1;
		Node<Anytype> current = head;
		Node<Anytype> temp = head;
		Node<Anytype> newNode = new Node<Anytype>(data, height);

		// If inserting causes the skip list to grow then increase height and adjust each valid node
		if (this.height < getMaxHeight(++size)) 
		{
			growSkipList();
			this.height++;
		}

		// Starts from the top of the head node and drops a level accordingly,
		// using the algorithm described in class
		while (i++ < size)
		{
			// If the next node is a null reference i.e at the beginning or end of the skip list
			// Insert the node there
			if (current.next(nodeHeight) == null) 
			{
				while (0 <= nodeHeight)
				{
					// If the node reference at the level is not null then connect it to the next node
					if (current.next(nodeHeight) != null) 
					{
						temp = current.next(nodeHeight);
						current.setNext(nodeHeight, newNode);
						current.next(nodeHeight).setNext(nodeHeight--, temp);
					}
					else
						current.setNext(nodeHeight--, newNode);
				}

				break;
			}
			// If the next node value is greater than or equal to the data then insert there
			else if (current.next(nodeHeight).value().compareTo(data) >= 0) 
			{
				while (0 <= nodeHeight)
				{
					if (current.next(nodeHeight) != null) 
					{
						temp = current.next(nodeHeight);
						current.setNext(nodeHeight, newNode);
						current.next(nodeHeight).setNext(nodeHeight--, temp);
					}
					else
						current.setNext(nodeHeight--, newNode);
				}

				break;
			}
			else
			{
				current = current.next(nodeHeight);
			}
		}
	}

	// Deletes the node containing the data, if it's not in the skiplist then return
	// Not complete
	public void delete(Anytype data)
	{
		Node<Anytype> current = head;
		int i = 0, nodeHeight = this.height - 1;

		if (this.height < getMaxHeight(--size)) 
		{
			trimSkipList();
			this.height--;
		}

		return;
	}

	// Checks the skip list to see if it contains the data
	public boolean contains(Anytype data)
	{
		Node<Anytype> current = head;
		int i = 0, nodeHeight = this.height - 1;

		// Starts from the top of the head node and drops a level accordingly,
		// using the search algorithm described in class
		while (i++ < size)
		{
			// Returns false if not found
			if (0 > nodeHeight) 
			{
				return false;	
			}
			if (current.next(nodeHeight) == null) 
			{
				nodeHeight--;
			}
			else if (current.next(nodeHeight).value().compareTo(data) > 0) 
			{		
				current = current.next(--nodeHeight);
			}
			else if (current.next(nodeHeight).value().compareTo(data) < 0)
			{	
				current = current.next(nodeHeight);
			}
			else
				return true;
		}

		return false;
	}

	// Gets the node that references the node with the data
	public Node<Anytype> get(Anytype data)
	{
		Node<Anytype> current = head;
		int i = 0, nodeHeight = this.height - 1;

		// Starts from the top of the head node and drops a level accordingly,
		// using the search algorithm described in class
		while (i++ < size)
		{
			// Returns null if not found
			if (0 > nodeHeight) 
			{
				return null;	
			}
			if (current.next(nodeHeight) == null) 
			{
				nodeHeight--;
			}
			else if (current.next(nodeHeight).value().compareTo(data) > 0) 
			{		
				current = current.next(--nodeHeight);
			}
			else if (current.next(nodeHeight).value().compareTo(data) < 0)
			{	
				current = current.next(nodeHeight);
			}
			else
				return current;
		}

		return null;
	}

	public static double difficultyRating()
	{
		return 4.9;
	}

	public static double hoursSpent()
	{
		return 39.4;
	}

	// Returns the ceiling of log base 2 of n nodes using base conversion
	private static int getMaxHeight(int n)
	{
		if (n == 1)
			return 1;

		return (((int)Math.ceil(Math.log(n) / Math.log(2))));
	}

	// Generates a height with a probability of 1 / 2^n
	private static int generateRandomHeight(int maxHeight)
	{
		Random probability = new Random();
		int height = 0;

		while (probability.nextBoolean() && (height < maxHeight))
			height++;

		return height;
	}

	// Grows the skip list if the log base 2 ceiling of number of nodes > skip list height
	private void growSkipList()
	{
		Node<Anytype> current = head;
		Node<Anytype> temp = head;

		// Grows the head node first
		current.grow();

		// Goes through every valid node at previous max height and probably makes it grow
		while (current.next(this.height - 1) != null)
		{
			current = current.next(this.height - 1);
			current.maybeGrow();

			// If the node grows then set the reference at the new level to the next node at that level
			/*if (current.height() == this.height) 
			{
				temp.setNext(this.height, current);
				temp = current.next(this.height);
			}*/
		}
	}

	private void trimSkipList()
	{
		Node<Anytype> current = head;
		Node<Anytype> temp = head;
		int nodeHeight = getMaxHeight(size) - 1;

		// Trims the head node first
		current.trim(nodeHeight);

		// Goes through every valid node at current max height and trims it
		while (temp.next(this.height - 1) != null)
		{
			temp = current.next(this.height - 1);
			current.trim(nodeHeight);
			current = temp;
		}
	}
}
