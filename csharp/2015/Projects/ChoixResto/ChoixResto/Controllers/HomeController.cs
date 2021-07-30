using ChoixResto.Models;
using ChoixResto.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ChoixResto.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }
        public ActionResult Manger()
        {
            Resto r = new Resto { Nom = "La bonne fourchette", Telephone = "1234" };
            return View(r);
        }
        public ActionResult Bonjour()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le contrôleur",
                Date = DateTime.Now,
            //    Resto = new Resto { Nom = "La bonne fourchette", Telephone = "1234" }
            };
            return View(vm);
        }
        public ActionResult Bonjour2()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le contrôleur",
                Date = DateTime.Now,
            //    Resto = new Resto { Nom = "La bonne fourchette", Telephone = "1234" }
            };
            return View(vm);
        }
        public ActionResult List()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le <span style=\"color:red\">contrôleur</span>",
                Date = DateTime.Now,
                ListeDesRestos = new List<Resto>
        {
            new Resto { Nom = "Resto pinambour", Telephone = "1234" },
            new Resto { Nom = "Resto tologie", Telephone = "1234" },
            new Resto { Nom = "Resto ride", Telephone = "5678" },
            new Resto { Nom = "Resto toro", Telephone = "555" },
        }
            };
            return View(vm);
        }
        public ActionResult Forme()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le contrôleur",
                Resto = new Resto { Nom = "La bonne fourchette", Telephone = "1234" },
                /*Resto = new Resto
                { },*/
                Date = DateTime.Now,
                ListeDesRestos = new List<Resto>
        {
            /*new Resto { Nom = "Resto pinambour", Telephone = "1234" },
            new Resto { Nom = "Resto tologie", Telephone = "1234" },
            new Resto { Nom = "Resto ride", Telephone = "5678" },
            new Resto { Nom = "Resto toro", Telephone = "555" },*/
            new Resto { Id = 1, Nom = "Resto pinambour", Telephone = "1234" },
    new Resto { Id = 2, Nom = "Resto tologie", Telephone = "1234" },
    new Resto { Id = 5, Nom = "Resto ride", Telephone = "5678" },
    new Resto { Id = 9, Nom = "Resto toro", Telephone = "555" },
        },Login = "Francois"
            };
            ViewBag.ListeDesRestos = new SelectList( vm.ListeDesRestos, "Id", "Nom");
            return View(vm);
        }
        public ActionResult Forme2()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le contrôleur",
                Resto = new Resto { Nom = "La bonne fourchette", Telephone = "1234" },
                /*Resto = new Resto
                { },*/
                Date = DateTime.Now,
                ListeDesRestos = new List<Resto>
        {
            /*new Resto { Nom = "Resto pinambour", Telephone = "1234" },
            new Resto { Nom = "Resto tologie", Telephone = "1234" },
            new Resto { Nom = "Resto ride", Telephone = "5678" },
            new Resto { Nom = "Resto toro", Telephone = "555" },*/
            new Resto { Id = 1, Nom = "Resto pinambour", Telephone = "1234" },
    new Resto { Id = 2, Nom = "Resto tologie", Telephone = "1234" },
    new Resto { Id = 5, Nom = "Resto ride", Telephone = "5678" },
    new Resto { Id = 9, Nom = "Resto toro", Telephone = "555" },
        }
            };
            AccueilViewForm res = new AccueilViewForm();
            res.Vm = vm;
            res.Sel = new SelectList(vm.ListeDesRestos, "Id", "Nom");
            return View(res);
        }
        [ChildActionOnly]
        public ActionResult AfficheListeRestaurant()
        {
            List<Models.Resto> listeDesRestos = new List<Resto>
    {
        new Resto { Id = 1, Nom = "Resto pinambour", Telephone = "1234" },
        new Resto { Id = 2, Nom = "Resto tologie", Telephone = "1234" },
        new Resto { Id = 5, Nom = "Resto ride", Telephone = "5678" },
        new Resto { Id = 9, Nom = "Resto toro", Telephone = "555" },
    };
            return PartialView(listeDesRestos);
        }
        public ActionResult Rendu()
        {
            AccueilViewModel vm = new AccueilViewModel
            {
                Message = "Bonjour depuis le <span style=\"color:red\">contrôleur</span>"
            };
            return View(vm);
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
    public class AccueilViewForm
    {
        public AccueilViewModel Vm;
        public SelectList Sel;
    }
}