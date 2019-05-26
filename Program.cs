using System;
using static System.Console;
using static System.Math;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp7
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rand = new Random();
            byte N = (byte)rand.Next(6, 20);
            WriteLine($"Размер массива {N}");
            char[] mas = new char [N];
            for(int i = 0; i < mas.Length; i++)
            {
                mas[i] = ' ';
            }
            unLine(mas);
            caplet(mas);
            digit(mas);
            letter(mas);
            WriteLine();            
            foreach (char item in mas)
            {
                Write(item);
            }
            WriteLine();
            ReadKey();
        }
        static void unLine(char[] mas)
        {
            Random rand = new Random();
            int i = rand.Next(0, mas.Length - 1);
            mas[i] = '_';
        }
        static void caplet(char[] mas)
        {
            int a = 0;
            int j;
            char symbol;
            int counter = 0;
            for(int i = 0; i < mas.Length; i++)
            {
                if(mas[i] == '_')
                {
                    a = i;
                }
            }
            Random rand = new Random();
            while (counter < 2)
            {
                j = rand.Next(0, mas.Length);

                if(j != a)
                {
                    symbol = (char)rand.Next(65, 90);
                    mas[j] = symbol;
                    counter++;
                }
            }
        }
        static void digit(char [] mas)
        {
            int m = 0;
            if(mas.Length <= 5)
            {
                m = 1;
            }
            if (mas.Length <= 8)
            {
                m = 2;
            }
            if (mas.Length <= 12)
            {
                m = 3;
            }
            if (mas.Length <= 16)
            {
                m = 4;
            }
            if (mas.Length <= 20)
            {
                m = 5;
            }
            Random rand = new Random();
            int counter = rand.Next(1, m);
            char digit;
            int i;             
            while(counter > 0)
            {
                i = rand.Next(1, mas.Length-2);
                digit = (char)rand.Next(48, 57);
                if(mas[i] == ' ' && (mas[i-1] < '0' || mas[i - 1] > '9'))
                {
                    mas[i] = digit;
                    counter--;
                }
            }
        }
        static void letter(char [] mas)
        {
            Random rand = new Random();
            //char letter;
            for(int i = 0;  i < mas.Length; i++)
            {                
                if(mas[i] == ' ')
                {
                    mas[i] = (char)rand.Next(97, 122);
                }
            }
        }
    }
}
