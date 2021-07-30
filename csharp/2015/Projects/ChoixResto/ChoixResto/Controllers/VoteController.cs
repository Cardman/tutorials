using ChoixResto.Models;
using ChoixResto.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Mvc;

namespace ChoixResto.Controllers
{
    public class VoteController : Controller
    {
        private IDal dal;
        public VoteController():this(new Dal())
        {

        }
        public VoteController(IDal dal)
        {
            this.dal = dal;
        }
        // GET: Vote
        public ActionResult Index2(List<RestaurantCheckBoxViewModel> restos, Utilisateur utilisateur, int? idSondage)
        {
            //var Query = Request.Form[""];
            {
                //StringBuilder Str2 = new StringBuilder();
                //foreach (var r in restos)
                {
                    /*var Sel = Request.Form["Restos[" + Index + "].EstSelectionne"];
                    var Ind = Request.Form["Restos[" + Index + "].Id"];*/
                    //
                    //Str2.Append(r.EstSelectionne).Append(",");
                    //Str2.Append(r.NomEtTelephone).Append(",");
                    //Str2.Append(r.Id).Append("\n");
                    /*var RestoResult = RestList.FirstOrDefault(Rest => Rest.Id.ToString() == Ind);
                    if (RestoResult == null)
                    {
                        Index++;
                        continue;
                    }
                    Str.Append(RestoResult.Nom).Append(",");

                    if (Ut != null)
                    {
                        Str.Append(Ut.Prenom).Append("\n");
                        dal.AjouterVote(IdSon, RestoResult.Id, Ut.Id);
                    }
                    else
                    {
                        Str.Append(Ut).Append("\n");
                    }
                    Index++; */

                }
                //File(Encoding.ASCII.GetBytes(Str2.ToString()), "application/octet-stream", "MonFichier.txt");
            }
            //Votes votes = new Votes();
            var Ut = dal.ObtenirUtilisateur(utilisateur.Id);
            if (Ut == null)
            {
                return View("Error");
            }
            //votes.Utilisateur = Ut;
            //votes.Restos = restos;
            //var Co = votes.CreerVotes().Count;
            //var Restos = dal.ObtientTousLesRestaurants();
            var Mod = new Votes();
            //var SonId = Request.Form["IdSondage"];
            if (!idSondage.HasValue)
            {
                return View("Error");
            }
            int IdSon = idSondage.Value;
            /*if (!int.TryParse(SonId, out IdSon))
            {
                return View("Error");
            }*/
            if (!dal.ADejaVoteBis(IdSon, Ut.Id.ToString()))
            {
                bool Voted = false;
                var Index = 0;
                var RestList = dal.ObtientTousLesRestaurants();
                /*foreach (var r in votes.CreerVotes())
                {
                    var Sel = Request.Form["Restos[" + Index + "].EstSelectionne"];
                    var Ind = Request.Form["Restos[" + Index + "].Id"];
                    var RestoResult = RestList.FirstOrDefault(Rest => Rest.Id.ToString() == Ind);
                    if (RestoResult == null)
                    {
                        Index++;
                        continue;
                    }
                    if (Sel == "false")
                    {
                        Index++;
                        continue;
                    }
                    Voted = true;
                    dal.AjouterVote(IdSon, RestoResult.Id, Ut.Id);
                    Index++;
                }*/
                foreach (var r in restos)
                {
                    var Sel = r.EstSelectionne;
                    //r.NomEtTelephone == null
                    var Ind = r.Id;
                    var RestoResult = RestList.FirstOrDefault(Rest => Rest.Id == Ind);
                    if (RestoResult == null)
                    {
                        Index++;
                        continue;
                    }
                    if (!Sel)
                    {
                        Index++;
                        continue;
                    }
                    Voted = true;
                    dal.AjouterVote(IdSon, RestoResult.Id, Ut.Id);
                    Index++;
                }
                if (!Voted)
                {
                    Votes vo = new Votes();
                    vo.IdSondage = IdSon;
                    vo.Utilisateur = Ut;
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
                    vo.Error = true;
                    return View("~/Views/Vote/Index.cshtml", vo);
                }
            }
            /*StringBuilder Str = new StringBuilder();
            Str.Append(IdSon).Append(",");*/
            //var Index = 0;
            //var RestList = dal.ObtientTousLesRestaurants();
            /*foreach (var r in votes.CreerVotes())
            {
                var Sel = Request.Form["Restos[" + Index + "].EstSelectionne"];
                var Ind = Request.Form["Restos[" + Index + "].Id"];
                //
                Str.Append(Sel).Append(",");
                Str.Append(Ind).Append(",");
                var RestoResult = RestList.FirstOrDefault(Rest => Rest.Id.ToString() == Ind);
                if (RestoResult == null)
                {
                    Index++;
                    continue;
                }
                Str.Append(RestoResult.Nom).Append(",");
                
                if (Ut != null) {
                    Str.Append(Ut.Prenom).Append("\n");
                    dal.AjouterVote(IdSon, RestoResult.Id, Ut.Id);
                } else
                {
                    Str.Append(Ut).Append("\n");
                }
                Index++;

            }*/
            var welcome = new WelcomeForm();
            var welcome2 = new Welcome();
            List<Resto> listeDesRestaurants = dal.ObtientTousLesRestaurants();
            welcome2.Bdd = listeDesRestaurants;
            welcome2.Sondages = dal.ObtenirSondages();
            welcome.welcome = welcome2;
            welcome.sel = new SelectList(welcome2.Sondages, "Id", "Id");
            //return File(Encoding.ASCII.GetBytes(Str.ToString()), "application/octet-stream", "MonFichier.txt");
            return View("~/Views/Restaurant/Index.cshtml", welcome);
            //return View(Mod);
        }
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

        public ActionResult Index(int id)
        {
            RestaurantVoteViewModel viewModel = new RestaurantVoteViewModel
            {
                ListeDesResto = dal.ObtientTousLesRestaurants().Select(r => new RestaurantCheckBoxViewModel { Id = r.Id, NomEtTelephone = string.Format("{0} ({1})", r.Nom, r.Telephone) }).ToList()
            };
            if (dal.ADejaVote(id, Request.Browser.Browser))
            {
                return RedirectToAction("AfficheResultat", new { id = id });
            }
            return View(viewModel);
        }

        [HttpPost]
        public ActionResult Index(RestaurantVoteViewModel viewModel, int id)
        {
            if (!ModelState.IsValid)
                return View(viewModel);
            Utilisateur utilisateur = dal.ObtenirUtilisateur(Request.Browser.Browser);
            if (utilisateur == null)
                return new HttpUnauthorizedResult();
            foreach (RestaurantCheckBoxViewModel restaurantCheckBoxViewModel in viewModel.ListeDesResto.Where(r => r.EstSelectionne))
            {
                dal.AjouterVote(id, restaurantCheckBoxViewModel.Id, utilisateur.Id);
            }
            return RedirectToAction("AfficheResultat", new { id = id });
        }

        public ActionResult AfficheResultat(int id)
        {
            if (!dal.ADejaVote(id, Request.Browser.Browser))
            {
                return RedirectToAction("Index", new { id = id });
            }
            List<Resultats> resultats = dal.ObtenirLesResultats(id);
            return View(resultats.OrderByDescending(r => r.NombreDeVotes).ToList());
        }
        /*public Utilisateur ObtenirUtilisateur(string idStr)
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
}*/
    }
}