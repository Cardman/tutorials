using ChoixResto.Models;
using ChoixResto.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ChoixResto.Controllers
{
    public class RestaurantController : Controller
    {
        private IDal dal;
        //private Welcome welcome;
        public RestaurantController() : this(new Dal())
        {
        }
        public RestaurantController(IDal dalIoc)
        {
            dal = dalIoc;
        }

        /*public ActionResult Index()
        {
            List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
            return View(listeDesRestaurants);
        }*/
        // GET: Restaurant
        [ActionName("Index")]
        public ActionResult LeNomQueJeVeux()
        {
            //using (IDal dal = new Dal())
            {
                var welcome = new WelcomeForm();
                welcome.welcome = new Welcome();
                List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
                welcome.welcome.Bdd = listeDesRestaurants;
                welcome.welcome.Sondages = dal.ObtenirSondages();
                welcome.sel = new SelectList(welcome.welcome.Sondages, "Id", "Id");
                return View(welcome);
            }
        }
        [ActionName("Majeur")]
        public ActionResult LeNomQueJeVeux2()
        {
            List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
            return View(listeDesRestaurants);
        }
        public ActionResult CreerRestaurant()
        {
            return View();
        }
        [HttpPost]
        public ActionResult CreerSondage()
        {
            Votes vo = new Votes();
            vo.IdSondage = dal.CreerUnSondage();
            var welcome = new WelcomeForm();
            Welcome welc = new Welcome();
            List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
            welc.Bdd = listeDesRestaurants;
            welc.Sondages = dal.ObtenirSondages();
            welc.Prenom = Request.Form["welcome.Prenom"];
            welcome.welcome = welc;
            welcome.sel = new SelectList(welc.Sondages, "Id", "Id");
            return View("Index", welcome);
        }
        [HttpPost]
        public ActionResult AccederSondage(int? id)
        {
            if (id.HasValue)
            {
                var sondage = dal.ObtenirSondages().FirstOrDefault(Sond => Sond.Id == id);
                if (sondage == null)
                {
                    return View("Error");
                }
                Votes vo = new Votes();
                vo.IdSondage = sondage.Id;
                var pre = Request.Form["welcome.Prenom"];
                vo.Utilisateur = ObtenirUtilisateurBis(pre);
                if (vo.Utilisateur == null)
                {
                    List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
                    var welcome = new WelcomeForm();
                    Welcome welc = new Welcome();
                    welc.Bdd = listeDesRestaurants;
                    welc.Sondages = dal.ObtenirSondages();
                    welc.Prenom = pre;
                    welcome.welcome = welc;
                    welcome.sel = new SelectList(welc.Sondages, "Id", "Id");
                    return View("Index", welcome);
                }
                var Restos = dal.ObtientTousLesRestaurants();
                vo.Restos = new List<RestaurantCheckBoxViewModel>();
                foreach (var r in Restos)
                {
                    var res = new RestaurantCheckBoxViewModel();
                    res.Rest = r;
                    res.NomEtTelephone = r.Nom + " " + r.Telephone;
                    res.Id = r.Id;
                    vo.Restos.Add(res);
                }
                return View("~/Views/Vote/Index.cshtml", vo);
            }
            return View("Error");
        }
        [HttpPost]
        public ActionResult AccederResultatSondage(int? id)
        {
            if (id.HasValue)
            {
                var sondage = dal.ObtenirSondages().FirstOrDefault(Sond => Sond.Id == id);
                if (sondage == null)
                {
                    return View("Error");
                }
                return View("~/Views/Resultat/Index.cshtml", dal.ObtenirLesResultats(sondage.Id));
            }
            return View("Error");
        }
        public Utilisateur ObtenirUtilisateurBis(string idStr)
        {
            return CreeOuRecupere(idStr, "1234");
        }

        private Utilisateur CreeOuRecupere(string nom, string motDePasse)
        {
            Utilisateur utilisateur = dal.Authentifier(nom, motDePasse);
            if (utilisateur == null)
            {
                int id = dal.AjouterUtilisateur(nom, motDePasse);
                return dal.ObtenirUtilisateur(id);
            }
            return utilisateur;
        }
        [HttpPost]
        public ActionResult CreerRestaurant(Resto resto)
        {
            //using (IDal dal = new Dal())
            {
                if (dal.RestaurantExiste(resto.Nom))
                {
                    ModelState.AddModelError("Nom", "Ce nom de restaurant existe déjà");
                    return View(resto);
                }
                if (!ModelState.IsValid)
                {
                    return View(resto);
                }
                dal.CreerRestaurant(resto.Nom, resto.Telephone);
                return RedirectToAction("Index");
            }
        }
        public ActionResult ModifierRestaurant(int? id)
        {
            if (id.HasValue)
            {
                //using (IDal dal = new Dal())
                {
                    Resto restaurant = dal.ObtientTousLesRestaurants().FirstOrDefault(r => r.Id == id.Value);
                    if (restaurant == null)
                    {
                        return View("Error");
                    }
                    return View(restaurant);
                }
            }
            else
            {
                return View("Error");
            }
        }
        public ActionResult AfficheJson()
        {
            Resto resto = new Resto { Id = 1, Nom = "Resto pinambour" };
            return Json(resto, JsonRequestBehavior.AllowGet);
        }
        public ActionResult ObtientFichier()
        {
            string fichier = Server.MapPath("~/App_Data/MonFichier.txt");
            return File(fichier, "application/octet-stream", "MonFichier.txt");
        }
        public ActionResult AccesAuthentifie()
        {
            if (HttpContext.User.Identity.IsAuthenticated)
                return View();
            return new HttpStatusCodeResult(401);
        }
        /*[HttpPost]
        public ActionResult ModifierRestaurant(int? id, string nom, string telephone)
        {
            if (id.HasValue)
            {
                using (IDal dal = new Dal())
                {
                    dal.ModifierRestaurant(id.Value, nom, telephone);
                    return RedirectToAction("Index");
                }
            }
            else
            {
                return View("Error");
            }
        }*/
        /*[HttpPost]
        public ActionResult ModifierRestaurant(Resto resto)
        {
            using (IDal dal = new Dal())
            {
                dal.ModifierRestaurant(resto.Id, resto.Nom, resto.Telephone);
                return RedirectToAction("Index");
            }
        }*/
        /*[HttpPost]
        public ActionResult ModifierRestaurant(Resto resto)
        {
            if (string.IsNullOrWhiteSpace(resto.Nom))
            {
                ViewBag.MessageErreur = "Le nom du restaurant doit être rempli";
                return View(resto);
            }
            using (IDal dal = new Dal())
            {
                dal.ModifierRestaurant(resto.Id, resto.Nom, resto.Telephone);
                return RedirectToAction("Index");
            }
        }*/
        [HttpPost]
        public ActionResult ModifierRestaurant(Resto resto)
        {
            if (!ModelState.IsValid)
            {
                return View(resto);
            }
            dal.ModifierRestaurant(resto.Id, resto.Nom, resto.Telephone);
            return RedirectToAction("Index");
        }
    }
    public static class ControllerExtensions
    {
        public static void ValideLeModele<T>(this Controller controller, T modele)
        {
            controller.ModelState.Clear();

            ValidationContext context = new ValidationContext(modele, null, null);
            List<ValidationResult> validationResults = new List<ValidationResult>();
            Validator.TryValidateObject(modele, context, validationResults, true);

            foreach (ValidationResult result in validationResults)
            {
                foreach (string memberName in result.MemberNames)
                {
                    controller.ModelState.AddModelError(memberName, result.ErrorMessage);
                }
            }
        }
    }
    public class InitChoixResto : DropCreateDatabaseAlways<BddContext>
    {
        protected override void Seed(BddContext context)
        {
            context.Restos.Add(new Resto { Id = 1, Nom = "Resto pinambour", Telephone = "123" });
            context.Restos.Add(new Resto { Id = 2, Nom = "Resto pinière", Telephone = "456" });
            context.Restos.Add(new Resto { Id = 3, Nom = "Resto toro", Telephone = "789" });

            base.Seed(context);
        }
    }
    public class WelcomeForm
    {
        public Welcome welcome;
        public SelectList sel;
    }
}