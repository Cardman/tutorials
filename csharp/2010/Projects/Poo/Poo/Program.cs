using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Poo
{
    class Program
    {
        static void Main(string[] args)
        {
            Afficheur.Affiche(new MyClass());
            Afficheur.Affiche(1);
            MaListeGenerique<int> maListe = new MaListeGenerique<int>();
            maListe.Ajouter(25);
            maListe.Ajouter(30);
            maListe.Ajouter(5);

            Console.WriteLine(maListe.ObtenirElement(0));
            Console.WriteLine(maListe.ObtenirElement(1));
            Console.WriteLine(maListe.ObtenirElement(2));

            for (int i = 0; i < 30; i++)
            {
                maListe.Ajouter(i);
            }
            Oiseau oiseau = Afficheur.Creer<Oiseau>();
            Avion a380 = Afficheur.Creer<Avion>();
            TypeValeurNull<int> entier = new TypeValeurNull<int>();
            if (!entier.AUneValeur)
            {
                Console.WriteLine("l'entier n'a pas de valeur");
            }
            entier.Valeur = 5;
            if (entier.AUneValeur)
            {
                Console.WriteLine("Valeur de l'entier : " + entier.Valeur);
            }
            int? entier2 = null;
            if (!entier2.HasValue)
            {
                Console.WriteLine("l'entier n'a pas de valeur");
            }
            entier2 = 5;
            if (entier2.HasValue)
            {
                Console.WriteLine("Valeur de l'entier : " + entier2.Value);
            }
            string chaineNormale = "Bonjour à tous";
            string chaineCryptee = chaineNormale.Crypte();
            Console.WriteLine(chaineCryptee);
            chaineNormale = chaineCryptee.Decrypte();
            Console.WriteLine(chaineNormale);
            new DemoEvenement().Demo();
            try
            {
                string chaine = "dix";
                int valeur = Convert.ToInt32(chaine);
                Console.WriteLine("Ce code ne sera jamais affiché");
            }
            catch (Exception)
            {
                Console.WriteLine("Une erreur s'est produite dans la tentative de conversion");
            }
            try
            {
                string chaine = "10";
                int valeur = Convert.ToInt32(chaine);
                Console.WriteLine("Conversion OK");
            }
            catch (Exception)
            {
                Console.WriteLine("Nous ne passons jamais ici ...");
            }
            try
            {
                string chaine = "dix";
                int valeur = Convert.ToInt32(chaine);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Il y a un eu une erreur, plus d'informations ci-dessous :");
                Console.WriteLine();
                Console.WriteLine("Message d'erreur : " + ex.Message);
                Console.WriteLine();
                Console.WriteLine("Pile d'appel : " + ex.StackTrace);
                Console.WriteLine();
                Console.WriteLine("Type de l'exception : " + ex.GetType());
            }
            try
            {
                Methode1();
            }
            catch (NotImplementedException ex)
            {
                Console.WriteLine("On intercepte l'exception de la méthode 3");
                Console.WriteLine(ex.StackTrace);
            }
            Type type = typeof(string);
            foreach (MethodInfo infos in type.GetMethods())
            {
                Console.Write(infos.Name+"(");
                foreach (ParameterInfo p in infos.GetParameters())
                {
                    Console.Write(p.ParameterType+",");
                }
                Console.WriteLine(")");
                //Console.Write
            }
        }
        public static void Methode1()
        {
            Methode2();
        }

        public static void Methode2()
        {
            Methode3();
        }

        public static void Methode3()
        {
            throw new NotImplementedException();
        }
    }
    public static class Afficheur
    {
        public static void Affiche<T>(T a)
        {
            Console.WriteLine("Afficheur d'objet :");
            Console.WriteLine("\tType : " + a.GetType());
            Console.WriteLine("\tReprésentation : " + a.ToString());
        }
        public static T Creer<T>() where T : IVolant, new()
        {
            T t = new T();
            t.DeplierLesAiles();
            t.Voler();
            return t;
        }
    }
    class MyClass
    {
    }
    public class MaListeGenerique<T>
    {
        private int capacite;
        private int nbElements;
        private T[] tableau;

        public MaListeGenerique()
        {
            capacite = 10;
            nbElements = 0;
            tableau = new T[capacite];
        }
        public void Ajouter(T element)
        {
            if (nbElements >= capacite)
            {
                capacite *= 2;
                T[] copieTableau = new T[capacite];
                for (int i = 0; i < tableau.Length; i++)
                {
                    copieTableau[i] = tableau[i];
                }
                tableau = copieTableau;
            }
            tableau[nbElements] = element;
            nbElements++;
        }
        public T ObtenirElement(int indice)
        {
            if (indice < 0 || indice >= nbElements)
            {
                Console.WriteLine("L'indice n'est pas bon");
                return default(T);
            }
            return tableau[indice];
        }
    }
    public interface IVolant
    {
        void DeplierLesAiles();
        void Voler();
    }
    public class Avion : IVolant
    {
        public void DeplierLesAiles()
        {
            Console.WriteLine("Je déplie mes ailes mécaniques");
        }

        public void Voler()
        {
            Console.WriteLine("J'allume le moteur");
        }
    }

    public class Oiseau : IVolant
    {
        public void DeplierLesAiles()
        {
            Console.WriteLine("Je déplie mes ailes d'oiseau");
        }

        public void Voler()
        {
            Console.WriteLine("Je bats des ailes");
        }
    }
    public class TypeValeurNull<T> where T : struct
    {
        private bool aUneValeur;
        public bool AUneValeur
        {
            get { return aUneValeur; }
        }

        private T valeur;
        public T Valeur
        {
            get
            {
                if (aUneValeur)
                    return valeur;
                throw new InvalidOperationException();
            }
            set
            {
                aUneValeur = true;
                valeur = value;
            }
        }
    }
    public static class Encodage
    {
        public static string Crypte(this string chaine)
        {
            return Convert.ToBase64String(Encoding.Default.GetBytes(chaine));
        }

        public static string Decrypte(this string chaine)
        {
            return Encoding.Default.GetString(Convert.FromBase64String(chaine));
        }
    }
    public class Voiture
    {
        public delegate void DelegateDeChangementDePrix(decimal nouveauPrix);
        public event DelegateDeChangementDePrix ChangementDePrix;
        public decimal Prix { get; set; }

        public void PromoSurLePrix()
        {
            Prix = Prix / 2;
            if (ChangementDePrix != null)
                ChangementDePrix(Prix);
        }
    }
    public class DemoEvenement
    {
        public void Demo()
        {
            Voiture voiture = new Voiture { Prix = 10000 };

            Voiture.DelegateDeChangementDePrix delegateChangementDePrix = voiture_ChangementDePrix;
            voiture.ChangementDePrix += delegateChangementDePrix;

            voiture.PromoSurLePrix();
        }

        private void voiture_ChangementDePrix(decimal nouveauPrix)
        {
            Console.WriteLine("Le nouveau prix est de : " + nouveauPrix);
        }
    }
}
