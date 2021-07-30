using ChoixResto.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ChoixResto.Controllers
{
    public class ResultatController : Controller
    {
        private Dal dal;
        public ResultatController():this(new Dal())
        {

        }
        public ResultatController(Dal dal)
        {
            this.dal = dal;
        }
        // GET: Resultat
        /*public ActionResult Index()
        {
            return View();
        }*/
        public ActionResult Retour()
        {
            var welcomeForm = new WelcomeForm();
            var welcome = new Welcome();
            List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
            welcome.Bdd = listeDesRestaurants;
            welcome.Sondages = dal.ObtenirSondages();
            welcomeForm.welcome = welcome;
            welcomeForm.sel = new SelectList(welcome.Sondages, "Id", "Id");
            return View("~/Views/Restaurant/Index.cshtml", welcomeForm);
        }
    }
}