/*
Joel Tucker

My own Test Case for Strings
 */

public class TestCase02
{
    public static void main(String [] args)
    {
        double difficulty = GenericBST.difficultyRating();
        System.out.println((difficulty < 1.0 || difficulty > 5.0) ? "fail whale :(" : "Hooray!");

        double hours = GenericBST.hoursSpent();
        System.out.println((hours <= 0.0) ? "fail whale :(" : "Hooray!");

        // Create a GenericBST.
        GenericBST<String> myTree = new GenericBST<>();

        String [] array = {"man", "walk", "appl", "boat", "heel", "zzz", "do", "zebr", "aard", "douc"};

        for (String string : array)
            myTree.insert(string);

        System.out.println(myTree.contains("appl"));
        System.out.println(myTree.contains("man"));
        System.out.println(myTree.contains("aard"));

        myTree.inorder();
        myTree.preorder();
        myTree.postorder();

        myTree.delete("man");
        myTree.delete("boat");
        myTree.delete("appl");
        myTree.delete("aard");
        myTree.inorder();

        System.out.println(myTree.contains("man"));
        System.out.println(myTree.contains("appl"));
        System.out.println(myTree.contains("aard"));

    }
}
