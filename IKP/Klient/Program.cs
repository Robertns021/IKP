using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Klient
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Welcome");

            int x = -1;
            while(x != 0)
            {
                Console.WriteLine();
                /*
                Opcije klijenta
                */
                x = int.Parse(Console.ReadLine());
                /*
                Logika klijenta primanje poruka citanje poruka                 
                */
            }
            Console.WriteLine("Goodbye");
            Console.ReadKey();
        }
        //SendMessage(char* queueName, void* message, int messageSize)
    }
}
