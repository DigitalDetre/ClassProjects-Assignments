import java.util.ArrayList;

/*
Joel Tucker

My own test cases for Person Object

 */
public class TestCase03
{
    public static void main(String [] args)
    {
        double difficulty = GenericBST.difficultyRating();
        System.out.println((difficulty < 1.0 || difficulty > 5.0) ? "fail whale :(" : "Hooray!");

        double hours = GenericBST.hoursSpent();
        System.out.println((hours <= 0.0) ? "fail whale :(" : "Hooray!");

        // Create a GenericBST.
        GenericBST<Person> myTree = new GenericBST<Person>();

        ArrayList<Person> list = new ArrayList<Person>();

        // add some Person objects to the ArrayList
        list.add(new Person("Cada St-Merrein", "04/22/1961"));
        list.add(new Person("Regulus Arcturus Black", "01/30/1961"));
        list.add(new Person("Perceval Thoreau", "08/08/1450"));
        list.add(new Person("Magdeleine Corriander Grabb", "05/19/1960"));
        list.add(new Person("Toby Mcfluffy Face", "11/01/1984"));

        Person p = new Person("Michael Smerconish", "05/23/1970");
        list.add(p);


        for (Person person : list)
            myTree.insert(person);

        System.out.println(myTree.contains(p));

        myTree.inorder();
        myTree.preorder();
        myTree.postorder();

        myTree.delete(p);
        myTree.delete(list.get(2));

        myTree.inorder();
        System.out.println(myTree.contains(p));

    }
}
