using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine(System.Environment.UserName);
            System.Xml.ConformanceLevel level;
            System.Numerics.BigInteger bigInt;
            Complex c = Complex.One;
            Console.WriteLine(c);
            Console.WriteLine("Partie réelle : " + c.Real);
            Console.WriteLine("Partie imaginaire : " + c.Imaginary);

            Console.WriteLine(Complex.Conjugate(Complex.FromPolarCoordinates(1.0, 45 * Math.PI / 180)));
            //Console.WriteLine(translation(DateTime.Now.DayOfWeek));
            Console.WriteLine(formatHello(DateTime.Now.DayOfWeek,"francois",DateTime.Now.Hour));
            Console.WriteLine(formatHello(DayOfWeek.Monday, "francois", 4));
            Console.WriteLine(formatHello(DayOfWeek.Monday, "francois", 16));
            Console.WriteLine(formatHello(DayOfWeek.Monday, "francois", 19));
            Console.WriteLine("\n");
            List<int> numbers_ = new List<int>();
            numbers_.Add(2);
            numbers_.Add(5);
            Console.WriteLine(sum(numbers_));
            Console.WriteLine(sum2(numbers_));
            string chaineAge = "20";
            int age = Convert.ToInt32(chaineAge); // age is worth 20
            Console.WriteLine(age);
            chaineAge = "ab20cd";
            int age2;
            if (int.TryParse(chaineAge, out age2))
            {
                Console.WriteLine("La conversion est possible, age vaut " + age2);
            }
            else
            {
                Console.WriteLine("Conversion impossible");
            }
            chaineAge = "20";
            int age3;
            if (int.TryParse(chaineAge, out age3))
            {
                Console.WriteLine("La conversion est possible, age vaut " + age3);
            }
            else
            {
                Console.WriteLine("Conversion impossible");
            }
            Console.WriteLine("\n");
            foreach (string parametre in args)
            {
                Console.WriteLine(parametre);
            }
            Console.WriteLine("\n");
            foreach (string parametre in Environment.GetCommandLineArgs())
            {
                Console.WriteLine(parametre);
            }
            Car car_ = new Car();
            car_.Couleur = "white";
            car_.Vitesse = 30;
            car_.Klaxonner();
            MyClass cl_ = new MyClass();
            cl_.Klaxonner();
            Animal animal = new Animal("") { NombreDePattes = 4 };
            animal.Respirer();
            Console.WriteLine();

            Chien chien = new Chien("milou") { NombreDePattes = 4 };
            chien.Respirer();
            chien.Aboyer();
            List<Animal> animaux = new List<Animal>();
            Animal milou = new Chien("Milou");
            Animal dingo = new Chien("Dingo");
            Animal idefix = new Chien("Idéfix");
            Animal tom = new Chat("Tom");
            Animal felix = new Chat("Félix");

            animaux.Add(milou);
            animaux.Add(dingo);
            animaux.Add(idefix);
            animaux.Add(tom);
            animaux.Add(felix);
            foreach (Animal animal2 in animaux)
            {
                animal2.Respirer();
            }
            Console.WriteLine();
            foreach (Animal animal2 in animaux)
            {
                Console.WriteLine(animal2);
            }
            ChienMuet chienMuet_ = new ChienMuet();
            chienMuet_.Aboyer();
            age = 30;
            Doubler(ref age);
            Console.WriteLine(age);
        }
        public static void Doubler(ref int valeur)
        {
            valeur = valeur * 2;
        }
        static int sum(List<int> _numbers)
        {
            int sum_ = 0;
            foreach (int i in _numbers) {
                sum_ += i;
            }
            return sum_;
        }
        static int sum2(List<int> _numbers)
        {
            int sum_ = 0;
            for (int i = 0; i < _numbers.Count; i++)
            {
                sum_ += _numbers.ElementAt(i);
            }
            return sum_;
        }
        static string formatHello(DayOfWeek d, string _user, int _h)
        {
            string hello_;
            switch (d)
            {
                case DayOfWeek.Monday:
                case DayOfWeek.Tuesday:
                case DayOfWeek.Wednesday:
                case DayOfWeek.Thursday:
                    if (_h > 18)
                    {
                        hello_ = "bonsoir " + _user;
                    }
                    else if (_h >= 9)
                    {
                        hello_ = "bonjour " + _user;
                    }
                    else
                    {
                        if (d == DayOfWeek.Monday)
                        {
                            hello_ = "bon week-end " + _user;
                        }
                        else
                        {
                            hello_ = "bonsoir " + _user;
                        }
                    }
                    return hello_;
                case DayOfWeek.Friday:
                    if (_h >= 9 && _h <= 18)
                    {
                        hello_ = "bonjour " + _user;
                    }
                    else
                    {
                        hello_ = "bon week-end " + _user;
                    }
                    return hello_;
                default:
                    return "bon week-end " + _user;
            }

        }
        static string translation(DayOfWeek d)
        {
            switch (d)
            {
                case DayOfWeek.Monday:
                    return "lundi";
                case DayOfWeek.Tuesday:
                    return "mardi";
                case DayOfWeek.Wednesday:
                    return "mercredi";
                case DayOfWeek.Thursday:
                    return "jeudi";
                case DayOfWeek.Friday:
                    return "vendredi";
                case DayOfWeek.Saturday:
                    return "samedi";
                default:
                    return "dimanche";
            }
        }
    }
    enum Day {
        LUNDI,MARDI,MERCREDI,JEUDI,VENDREDI,SAMEDI,DIMANCHE
    }
    class Car {
        public string Couleur;
        public Car() : this(10)
        {
        }

        public Car(int vitesseVoiture)
        {
            System.Console.WriteLine("this");
            Vitesse = vitesseVoiture;
        }
        public void Klaxonner()
        {
            Console.WriteLine("Pouet ! "+Couleur+" car at "+Vitesse);
        }
        public bool VitesseAutorisee(int vitesse)
        {
            return vitesse <= 90;
        }
        private int vitessePrivee;
        public int Vitesse
        {
            get
            {
                coucou("get");
                return vitessePrivee;
            }
            set
            {
                coucou("set");
                vitessePrivee = value;
            }
        }
        void coucou(string _method)
        {
            Console.WriteLine("coucou " + _method);
        }
        public int VitesseMax { get; set; }
    }
    public class Animal
    {
        public int NombreDePattes { get; set; }
        public int age;
        protected bool estVivant;
        protected string prenom;
        public Animal(string prenomAnimal)
        {
            prenom = prenomAnimal;
        }
        public void Respirer()
        {
            Console.WriteLine("Je suis " + prenom + " et je respire");
        }
    }
    public class Chien : Animal
    {
        public Chien(string prenomDuChien):base(prenomDuChien)
        {
            prenom = prenomDuChien;
        }
        public virtual void Aboyer()
        {
            Console.WriteLine("Wouaf !");
        }
        public void Vieillir()
        {
            age++;
        }

        public void Naissance()
        {
            age = 0;
            estVivant = true; 
        }
        public override string ToString()
        {
            return "Je suis un chien et je m'appelle " + prenom;
        }
    }
    public class ChienMuet : Chien
    {
        public ChienMuet():base("boby") {
        }
        public override void Aboyer()
        {
            Console.WriteLine("...");
        }
    }
    public class Chat : Animal
    {
        public Chat(string prenomDuChat): base(prenomDuChat)
        {
            prenom = prenomDuChat;
        }
        public void Vieillir()
        {
            age++;
        }

        public void Naissance()
        {
            age = 0;
            estVivant = true;
        }
        public void Miauler()
        {
            Console.WriteLine("Miaou");
        }
        public override string ToString()
        {
            return "Je suis un chat et je m'appelle " + prenom;
        }
    }
}
