using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    enum Jours
    {
        Lundi,
        Mardi,
        Mercredi,
        Jeudi,
        Vendredi,
        Samedi,
        Dimanche
    }

    class Program
    {
        static void Main(string[] args)
        {
            int age;
            age = 27;
            Console.WriteLine(age);//Display 27
            int ageduvisiteur = 30;
            int ageDuVisiteur = 20;
            Console.WriteLine(ageduvisiteur); // Display 30
            Console.WriteLine(ageDuVisiteur); // Display 20
            string prenom = "nicolas";
            decimal soldeCompteBancaire = 100;
            bool estVrai = true;
            Console.WriteLine(prenom);
            Console.WriteLine(soldeCompteBancaire);
            Console.WriteLine(estVrai);
            string codePostal = "33000";
            string ville = "\"Bordeaux\"";
            string adresse = codePostal + " " + ville;
            Console.WriteLine(adresse); // Display : 33000 Bordeaux
            string fichier = @"c:\repertoire\fichier.cs"; // contains : c:\repertoire\fichier.cs
            Console.WriteLine(fichier);
            decimal compteEnBanque = 300;
            if (compteEnBanque >= 0) {
                Console.WriteLine("Votre compte est créditeur");
            }
            compteEnBanque = 300;
            bool estCrediteur = (compteEnBanque >= 0);
            if (estCrediteur)
                Console.WriteLine("Votre compte est créditeur");
            else
                Console.WriteLine("Votre compte est débiteur");
            string login = "Nicolas";
            string motDePasse = "test";
            if (login == "Nicolas" && motDePasse == "test")
                Console.WriteLine("Bienvenue Nicolas");
            else
                Console.WriteLine("Login incorrect");
            string civilite = "M";
            if (civilite == "Mme" || civilite == "Mlle")
                Console.WriteLine("Vous êtes une femme");
            else
                Console.WriteLine("Vous êtes un homme");
            civilite = "Mme";
            if (civilite == "Mme" || civilite == "Mlle")
                Console.WriteLine("Vous êtes une femme");
            else
                Console.WriteLine("Vous êtes un homme");
            civilite = "mme";
            if (civilite == "Mme" || civilite == "Mlle")
                Console.WriteLine("Vous êtes une femme");
            else
                Console.WriteLine("Vous êtes un homme");
            civilite = "mme";
            if (civilite == "Mme")
                Console.WriteLine("Vous êtes une femme");
            else if (civilite == "Mlle")
                Console.WriteLine("Vous êtes une femme non mariée");
            else if (civilite == "M.")
                Console.WriteLine("Vous êtes un homme");
            else
                Console.WriteLine("Je n'ai pas pu déterminer votre civilité");
            civilite = "M.";
            switch (civilite)
            {
                case "M.":
                    Console.WriteLine("Bonjour monsieur");
                    break;
                case "Mme":
                    Console.WriteLine("Bonjour madame");
                    break;
                case "Mlle":
                    Console.WriteLine("Bonjour mademoiselle");
                    break;
                default:
                    Console.WriteLine("Bonjour inconnu");
                    break;
            }
            AffichageBienvenue();
            DireBonjour("Nicolas", 30);
            DireBonjour("Jérémie", 20);
            double valeur = LongueurHypotenuse(1, 3);
            Console.WriteLine(valeur);
            valeur = LongueurHypotenuse(10, 10);
            Console.WriteLine(valeur);
            string[] jours = new string[] { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche" };
            for (int i = 0; i < jours.Length; i++)
            {
                Console.WriteLine(jours[i]);
            }
            Console.WriteLine("\n");
            Console.WriteLine(jours[3]); // affiche Jeudi
            Console.WriteLine(jours[0]); // affiche Lundi
            Console.WriteLine("\n");
            Array.Sort(jours);
            for (int i = 0; i < jours.Length; i++)
            {
                Console.WriteLine(jours[i]);
            }
            //line 13 Console.WriteLine(jours[10]); // provoque une erreur d'exécution car l'indice n'existe pas
            List<int> chiffres = new List<int>(); // création de la liste
            chiffres.Add(8); // chiffres contient 8
            chiffres.Add(9); // chiffres contient 8, 9
            chiffres.Add(4); // chiffres contient 8, 9, 4

            chiffres.RemoveAt(1); // chiffres contient 8, 4

            foreach (int chiffre in chiffres)
            {
                Console.WriteLine(chiffre);
            }
            Jours lundi = Jours.Lundi;
            Console.WriteLine(lundi);
        }

        static void AffichageBienvenue()
        {
            Console.WriteLine("Bonjour Nicolas");
            Console.WriteLine("-------" + Environment.NewLine);
            Console.WriteLine("\tBienvenue dans le monde merveilleux du C#");
        }

        static void DireBonjour(string prenom, int age)
        {
            Console.WriteLine("Bonjour " + prenom);
            Console.WriteLine("Vous avez " + age + " ans");
        }

        static double LongueurHypotenuse(double a, double b)
        {
            double sommeDesCarres = a * a + b * b;
            double resultat = Math.Sqrt(sommeDesCarres);
            return resultat;
        }
    }
}
