using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplication1.Models
{
    public class Dal : IDal
    {
        public Meteo ObtenirLaMeteoDuJour()
        {
            // ici , c'est le code pour accéder au service web
            // mais finalement , peu importe ce qu'on y met vu qu'on va bouchonner la méthode
            throw new NotImplementedException();
        }
    }
    public interface IDal
    {
        Meteo ObtenirLaMeteoDuJour();
    }
    public class Meteo
    {
        public double Temperature { get; set; }
        public Temps Temps { get; set; }
    }
    public enum Temps
    {
        Soleil,
        Pluie
    }
    public interface IGenerateur
    {
        int Valeur { get; }
    }

    public class Generateur : IGenerateur
    {
        private Random r;
        public Generateur()
        {
            r = new Random();
        }

        public int Valeur
        {
            get
            {
                return r.Next(0, 100);
            }
        }
    }
}