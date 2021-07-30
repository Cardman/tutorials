using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplication1.Models
{
    public class Client
    {
        public string Nom { get; set; }
        public int Age { get; set; }
    }
    public class Clients
    {
        public List<Client> ObtenirListeClients()
        {
            return new List<Client>
        {
            new Client { Age = 33, Nom = "Nicolas"},
            new Client { Age = 30, Nom = "Delphine"},
            new Client { Age = 33, Nom = "Jérémie"},
            new Client { Age = 1, Nom = "Timéo"}
        };
        }
    }
}