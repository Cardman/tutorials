using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    public class HomeController : Controller
    {
        /*public string Index(int? id)
        {
            return "Bonjour "+id;
        }*/

        /*public string Index(string id)
        {
            return "Bonjour " + id;
        }*/
        /*public string Index(string id)
        {
            return @"
        <html>
            <head>
                <title>Hello World</title>
            </head>
            <body>
                <p>Hello <span style=""color:red"">" + id + @"</span></p>
            </body>
        </html>";
        }*/
        /*public ActionResult Index(string id)
        {
            if (string.IsNullOrWhiteSpace(id))
                return View("Error");
            else
                return View();
        }*/
        public ActionResult Index(string id)
        {
            if (string.IsNullOrWhiteSpace(id))
                return View("Error");
            else
            {
                ViewData["Nom"] = id;
                return View();
            }
        }
        public string Index2(string id)
        {
            return HtmlHelper.GenerateLink(Request.RequestContext, RouteTable.Routes, "Mon lien", null, "Index", "Home", new RouteValueDictionary { { "id", id } }, null);
        }
        public string Afficher(string id)
        {
            return "coq " + id;
        }
        public ActionResult ListeClients()
        {
            Clients clients = new Clients();
            ViewData["Clients"] = clients.ObtenirListeClients();
            return View();
        }

        public ActionResult ChercheClient(string id)
        {
            ViewData["Nom"] = id;
            Clients clients = new Clients();
            Client client = clients.ObtenirListeClients().FirstOrDefault(c => c.Nom == id);
            if (client != null)
            {
                ViewData["Age"] = client.Age;
                return View("Trouve");
            }
            return View("NonTrouve");
        }
        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}