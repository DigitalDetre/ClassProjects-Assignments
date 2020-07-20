// Phong Nguyenho - ph094398

import java.io.*;
import java.util.*;

class Node<T>
{
	T data;
	Node<T> left, right;

	Node(T data)
	{
		this.data = data;
	}
}

public class GenericBST<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> root;

	// Inserts the data into the left or right subroot trees, doesn't allow
	// duplicate data.
	public void insert(AnyType data)
	{
		root = insert(root, data);
	}

	private Node<AnyType> insert(Node<AnyType> root, AnyType data)
	{
		// If the root has no data then insert data into it
		if (root == null)
			return new Node<>(data);

		// If the data being compared is less than root data then the data
		// returns a negative value and is inserted into the left subtree
		else if (data.compareTo(root.data) < 0)
			root.left = insert(root.left, data);

		// If the data being compared is greater than root data then the data
		// returns a positive value and is inserted into the right subtree
		else if (data.compareTo(root.data) > 0)
			root.right = insert(root.right, data);
		else
		{
			// Stylistically, I have this here to explicitly state that we are
			// disallowing insertion of duplicate values. This is unconventional
			// and a bit cheeky.
			;
		}

		return root;
	}

	// Deletes the node from the BST
	public void delete(AnyType data)
	{
		root = delete(root, data);
	}

	private Node<AnyType> delete(Node<AnyType> root, AnyType data)
	{
		// Returns null if there is no data in the tree or if there is no more
		// traversals
		if (root == null)
			return null;

		// If the data being compared is less than root data then traverse
		// the left subtree
		else if (data.compareTo(root.data) < 0)
			root.left = delete(root.left, data);

		// If the data being compared is greater than root data then traverse
		// the right subtree
		else if (data.compareTo(root.data) > 0)
			root.right = delete(root.right, data);

		// If the data has been found then ...
		else
		{
			// return null if the node has no children
			if (root.left == null && root.right == null)
				return null;

			// return the left node if there is no right node
			else if (root.right == null)
				return root.left;

			// return the right node if there is no left node
			else if (root.left == null)
				return root.right;

			// set the largest value from the left subtree to the current node
			// then call delete on the left child node
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is non-empty.
	private AnyType findMax(Node<AnyType> root)
	{
		// Traverses to the end of the right subtree of the left subtree
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	// Returns true if the value is contained in the BST, false otherwise.
	public boolean contains(AnyType data)
	{
		return contains(root, data);
	}

	private boolean contains(Node<AnyType> root, AnyType data)
	{
		// Returns false if the tree does not contain the data or there is no
		// more traversals
		if (root == null)
			return false;

		// If the data being compared is less than root data then traverse
		// the left subtree
		else if (data.compareTo(root.data) < 0)
			return contains(root.left, data);

		// If the data being compared is greater than root data then traverse
		// the right subtree
		else if (data.compareTo(root.data) > 0)
			return contains(root.right, data);
		else
			return true;
	}

	// Prints out what traversal it is and then prints out in that order
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	private void inorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// Prints out what traversal it is and then prints out in that order
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	private void preorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// Prints out what traversal it is and then prints out in that order
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	private void postorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

	public static double difficultyRating()
	{
		return 1.3;
	}

	public static double hoursSpent()
	{
		return 4.0;
	}
}
