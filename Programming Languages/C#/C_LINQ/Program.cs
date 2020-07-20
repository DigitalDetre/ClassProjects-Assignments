// Phong Nguyenho - ph094398
using System;
using System.Collections.Generic;
using System.Linq;

namespace C_LINQ
{
    class Problem1
    {
        public static IEnumerable<int> myFilter(IEnumerable<int> input)
        {
            input = input.Where(num => !((num > 50) && (num % 5 == 0)));
            input = input.AsQueryable().Select(num => num * num * num).Where(num => !(num % 2 == 0));
            return input;
        }

        static void Main(string[] args)
        {
            Random rnd = new Random(5);
            var listForProblem = Enumerable.Range(1, 100).Select(i => rnd.Next() % 101);
            var answer = Problem1.myFilter(listForProblem);

            foreach (int i in answer)
            {
                Console.WriteLine(i);
            }

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}
