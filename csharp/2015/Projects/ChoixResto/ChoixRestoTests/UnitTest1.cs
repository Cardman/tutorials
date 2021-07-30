using System;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ChoixResto.Models;
using System.Collections.Generic;
using System.Data.Entity;
using ChoixResto.Controllers;
using System.Web.Mvc;
using Moq;
using ChoixResto.ViewModels;
using System.Collections;
using System.Text;

namespace ChoixRestoTests
{
    /*[TestClass]
    public class DalTests
    {
        [TestInitialize]
        public void Init_AvantChaqueTest()
        {
            IDatabaseInitializer<BddContext> init = new DropCreateDatabaseAlways<BddContext>();
            Database.SetInitializer(init);
            init.InitializeDatabase(new BddContext());
        }
        [TestMethod]
        public void CreerRestaurant_AvecUnNouveauRestaurant_ObtientTousLesRestaurantsRenvoitBienLeRestaurant()
        {
            using (IDal dal = new Dal())
            {
                dal.CreerRestaurant("La bonne fourchette", "01 02 03 04 05");
                List<Resto> restos = dal.ObtientTousLesRestaurants();

                Assert.IsNotNull(restos);
                Assert.AreEqual(1, restos.Count);
                Assert.AreEqual("La bonne fourchette", restos[0].Nom);
                Assert.AreEqual("01 02 03 04 05", restos[0].Telephone);
            }
        }
        [TestMethod]
        public void ModifierRestaurant_CreationDUnNouveauRestaurantEtChangementNomEtTelephone_LaModificationEstCorrecteApresRechargement()
        {
            using (IDal dal = new Dal())
            {
                dal.CreerRestaurant("La bonne fourchette", "01 02 03 04 05");
                List<Resto> restos = dal.ObtientTousLesRestaurants();
                int id = restos.First(r => r.Nom == "La bonne fourchette").Id;

                dal.ModifierRestaurant(id, "La bonne cuillère", null);

                restos = dal.ObtientTousLesRestaurants();
                Assert.IsNotNull(restos);
                Assert.AreEqual(1, restos.Count);
                Assert.AreEqual("La bonne cuillère", restos[0].Nom);
                Assert.IsNull(restos[0].Telephone);
            }
        }
    }*/
    [TestClass]
    public class DalTests
    {
        private IDal dal;

        [TestInitialize]
        public void Init_AvantChaqueTest()
        {
            IDatabaseInitializer<BddContext> init = new DropCreateDatabaseAlways<BddContext>();
            Database.SetInitializer(init);
            init.InitializeDatabase(new BddContext());

            dal = new Dal();
        }

        [TestCleanup]
        public void ApresChaqueTest()
        {
            dal.Dispose();
        }

        [TestMethod]
        public void CreerRestaurant_AvecUnNouveauRestaurant_ObtientTousLesRestaurantsRenvoitBienLeRestaurant()
        {
            dal.CreerRestaurant("La bonne fourchette", "0102030405");
            List<Resto> restos = dal.ObtientTousLesRestaurants();

            Assert.IsNotNull(restos);
            Assert.AreEqual(1, restos.Count);
            Assert.AreEqual("La bonne fourchette", restos[0].Nom);
            Assert.AreEqual("0102030405", restos[0].Telephone);
        }

        [TestMethod]
        public void ModifierRestaurant_CreationDUnNouveauRestaurantEtChangementNomEtTelephone_LaModificationEstCorrecteApresRechargement()
        {
            dal.CreerRestaurant("La bonne fourchette", "0102030405");
            dal.ModifierRestaurant(1, "La bonne cuillère", null);

            List<Resto> restos = dal.ObtientTousLesRestaurants();
            Assert.IsNotNull(restos);
            Assert.AreEqual(1, restos.Count);
            Assert.AreEqual("La bonne cuillère", restos[0].Nom);
            Assert.IsNull(restos[0].Telephone);
        }

        [TestMethod]
        public void RestaurantExiste_AvecCreationDunRestauraunt_RenvoiQuilExiste()
        {
            dal.CreerRestaurant("La bonne fourchette", "0102030405");

            bool existe = dal.RestaurantExiste("La bonne fourchette");

            Assert.IsTrue(existe);
        }

        [TestMethod]
        public void RestaurantExiste_AvecRestaurauntInexistant_RenvoiQuilExiste()
        {
            bool existe = dal.RestaurantExiste("La bonne fourchette");

            Assert.IsFalse(existe);
        }

        [TestMethod]
        public void ObtenirUtilisateur_UtilisateurInexistant_RetourneNull()
        {
            Utilisateur utilisateur = dal.ObtenirUtilisateur(1);
            Assert.IsNull(utilisateur);
        }

        [TestMethod]
        public void ObtenirUtilisateur_IdNonNumerique_RetourneNull()
        {
            Utilisateur utilisateur = dal.ObtenirUtilisateur("abc");
            Assert.IsNull(utilisateur);
        }

        [TestMethod]
        public void AjouterUtilisateur_NouvelUtilisateurEtRecuperation_LutilisateurEstBienRecupere()
        {
            dal.AjouterUtilisateur("Nouvel utilisateur", "12345");

            Utilisateur utilisateur = dal.ObtenirUtilisateur(1);

            Assert.IsNotNull(utilisateur);
            Assert.AreEqual("Nouvel utilisateur", utilisateur.Prenom);

            utilisateur = dal.ObtenirUtilisateur("1");

            Assert.IsNotNull(utilisateur);
            Assert.AreEqual("Nouvel utilisateur", utilisateur.Prenom);
        }

        [TestMethod]
        public void Authentifier_LoginMdpOk_AuthentificationOK()
        {
            dal.AjouterUtilisateur("Nouvel utilisateur", "12345");

            Utilisateur utilisateur = dal.Authentifier("Nouvel utilisateur", "12345");

            Assert.IsNotNull(utilisateur);
            Assert.AreEqual("Nouvel utilisateur", utilisateur.Prenom);
        }

        [TestMethod]
        public void Authentifier_LoginOkMdpKo_AuthentificationKO()
        {
            dal.AjouterUtilisateur("Nouvel utilisateur", "12345");
            Utilisateur utilisateur = dal.Authentifier("Nouvel utilisateur", "0");

            Assert.IsNull(utilisateur);
        }

        [TestMethod]
        public void Authentifier_LoginKoMdpOk_AuthentificationKO()
        {
            dal.AjouterUtilisateur("Nouvel utilisateur", "12345");
            Utilisateur utilisateur = dal.Authentifier("Nouvel", "12345");

            Assert.IsNull(utilisateur);
        }

        [TestMethod]
        public void Authentifier_LoginMdpKo_AuthentificationKO()
        {
            Utilisateur utilisateur = dal.Authentifier("Nouvel utilisateur", "12345");

            Assert.IsNull(utilisateur);
        }

        [TestMethod]
        public void ADejaVote_AvecIdNonNumerique_RetourneFalse()
        {
            bool pasVote = dal.ADejaVote(1, "abc");

            Assert.IsFalse(pasVote);
        }

        [TestMethod]
        public void ADejaVote_UtilisateurNAPasVote_RetourneFalse()
        {
            int idSondage = dal.CreerUnSondage();
            int idUtilisateur = dal.AjouterUtilisateur("Nouvel utilisateur", "12345");

            bool pasVote = dal.ADejaVote(idSondage, idUtilisateur.ToString());

            Assert.IsFalse(pasVote);
        }

        [TestMethod]
        public void ADejaVote_UtilisateurAVote_RetourneTrue()
        {
            int idSondage = dal.CreerUnSondage();
            int idUtilisateur = dal.AjouterUtilisateur("Nouvel utilisateur", "12345");
            dal.CreerRestaurant("La bonne fourchette", "0102030405");
            dal.AjouterVote(idSondage, 1, idUtilisateur);

            bool aVote = dal.ADejaVote(idSondage, idUtilisateur.ToString());

            Assert.IsTrue(aVote);
        }

        [TestMethod]
        public void ObtenirLesResultats_AvecQuelquesChoix_RetourneBienLesResultats()
        {
            int idSondage = dal.CreerUnSondage();
            int idUtilisateur1 = dal.AjouterUtilisateur("Utilisateur1", "12345");
            int idUtilisateur2 = dal.AjouterUtilisateur("Utilisateur2", "12345");
            int idUtilisateur3 = dal.AjouterUtilisateur("Utilisateur3", "12345");

            dal.CreerRestaurant("Resto pinière", "0102030405");
            dal.CreerRestaurant("Resto pinambour", "0102030405");
            dal.CreerRestaurant("Resto mate", "0102030405");
            dal.CreerRestaurant("Resto ride", "0102030405");

            dal.AjouterVote(idSondage, 1, idUtilisateur1);
            dal.AjouterVote(idSondage, 3, idUtilisateur1);
            dal.AjouterVote(idSondage, 4, idUtilisateur1);
            dal.AjouterVote(idSondage, 1, idUtilisateur2);
            dal.AjouterVote(idSondage, 1, idUtilisateur3);
            dal.AjouterVote(idSondage, 3, idUtilisateur3);

            List<Resultats> resultats = dal.ObtenirLesResultats(idSondage);

            Assert.AreEqual(3, resultats[0].NombreDeVotes);
            Assert.AreEqual("Resto pinière", resultats[0].Nom);
            Assert.AreEqual("0102030405", resultats[0].Telephone);
            Assert.AreEqual(2, resultats[1].NombreDeVotes);
            Assert.AreEqual("Resto mate", resultats[1].Nom);
            Assert.AreEqual("0102030405", resultats[1].Telephone);
            Assert.AreEqual(1, resultats[2].NombreDeVotes);
            Assert.AreEqual("Resto ride", resultats[2].Nom);
            Assert.AreEqual("0102030405", resultats[2].Telephone);
        }

        [TestMethod]
        public void ObtenirLesResultats_AvecDeuxSondages_RetourneBienLesBonsResultats()
        {
            int idSondage1 = dal.CreerUnSondage();
            int idUtilisateur1 = dal.AjouterUtilisateur("Utilisateur1", "12345");
            int idUtilisateur2 = dal.AjouterUtilisateur("Utilisateur2", "12345");
            int idUtilisateur3 = dal.AjouterUtilisateur("Utilisateur3", "12345");
            dal.CreerRestaurant("Resto pinière", "0102030405");
            dal.CreerRestaurant("Resto pinambour", "0102030405");
            dal.CreerRestaurant("Resto mate", "0102030405");
            dal.CreerRestaurant("Resto ride", "0102030405");
            dal.AjouterVote(idSondage1, 1, idUtilisateur1);
            dal.AjouterVote(idSondage1, 3, idUtilisateur1);
            dal.AjouterVote(idSondage1, 4, idUtilisateur1);
            dal.AjouterVote(idSondage1, 1, idUtilisateur2);
            dal.AjouterVote(idSondage1, 1, idUtilisateur3);
            dal.AjouterVote(idSondage1, 3, idUtilisateur3);

            int idSondage2 = dal.CreerUnSondage();
            dal.AjouterVote(idSondage2, 2, idUtilisateur1);
            dal.AjouterVote(idSondage2, 3, idUtilisateur1);
            dal.AjouterVote(idSondage2, 1, idUtilisateur2);
            dal.AjouterVote(idSondage2, 4, idUtilisateur3);
            dal.AjouterVote(idSondage2, 3, idUtilisateur3);

            List<Resultats> resultats1 = dal.ObtenirLesResultats(idSondage1);
            List<Resultats> resultats2 = dal.ObtenirLesResultats(idSondage2);

            Assert.AreEqual(3, resultats1[0].NombreDeVotes);
            Assert.AreEqual("Resto pinière", resultats1[0].Nom);
            Assert.AreEqual("0102030405", resultats1[0].Telephone);
            Assert.AreEqual(2, resultats1[1].NombreDeVotes);
            Assert.AreEqual("Resto mate", resultats1[1].Nom);
            Assert.AreEqual("0102030405", resultats1[1].Telephone);
            Assert.AreEqual(1, resultats1[2].NombreDeVotes);
            Assert.AreEqual("Resto ride", resultats1[2].Nom);
            Assert.AreEqual("0102030405", resultats1[2].Telephone);

            Assert.AreEqual(1, resultats2[0].NombreDeVotes);
            Assert.AreEqual("Resto pinambour", resultats2[0].Nom);
            Assert.AreEqual("0102030405", resultats2[0].Telephone);
            Assert.AreEqual(2, resultats2[1].NombreDeVotes);
            Assert.AreEqual("Resto mate", resultats2[1].Nom);
            Assert.AreEqual("0102030405", resultats2[1].Telephone);
            Assert.AreEqual(1, resultats2[2].NombreDeVotes);
            Assert.AreEqual("Resto pinière", resultats2[2].Nom);
            Assert.AreEqual("0102030405", resultats2[2].Telephone);
        }
        [TestMethod]
        public void AccueilController_Index_RenvoiVueParDefaut()
        {
            AccueilController controller = new AccueilController();

            ViewResult resultat = (ViewResult)controller.Index();

            Assert.AreEqual(string.Empty, resultat.ViewName);
        }
        [TestMethod]
        public void AccueilController_AfficheDate_RenvoiVueIndexEtViewData()
        {
            AccueilController controller = new AccueilController();

            ViewResult resultat = (ViewResult)controller.AfficheDate("Nicolas");

            Assert.AreEqual("Index", resultat.ViewName);
            Assert.AreEqual(new DateTime(2012, 4, 28), resultat.ViewData["date"]);
            Assert.AreEqual("Bonjour Nicolas !", resultat.ViewData["Message"]);
        }
        [TestMethod]
        public void RestaurantController_Index_LeControleurEstOk()
        {
            using (IDal dal = new DalEnDur())
            {
                RestaurantController controller = new RestaurantController(dal);
                ViewResult resultat = (ViewResult)controller.LeNomQueJeVeux2();

                List<Resto> modele = (List<Resto>)resultat.Model;
                Assert.AreEqual("Resto pinambour", modele[0].Nom);
            }
        }
        [TestMethod]
        public void RestaurantController_ModifierRestaurantAvecRestoInvalide_RenvoiVueParDefaut()
        {
            using (IDal dal = new DalEnDur())
            {
                RestaurantController controller = new RestaurantController(dal);
                controller.ModelState.AddModelError("Nom", "Le nom du restaurant doit être saisi");

                ViewResult resultat = (ViewResult)controller.ModifierRestaurant(new Resto { Id = 1, Nom = null, Telephone = "0102030405" });

                Assert.AreEqual(string.Empty, resultat.ViewName);
                Assert.IsFalse(resultat.ViewData.ModelState.IsValid);
            }
        }
        [TestMethod]
        public void RestaurantController_ModifierRestaurantAvecRestoInvalideEtBindingDeModele_RenvoiVueParDefaut()
        {
            RestaurantController controller = new RestaurantController(new DalEnDur());
            Resto resto = new Resto { Id = 1, Nom = null, Telephone = "0102030405" };
            controller.ValideLeModele(resto);

            ViewResult resultat = (ViewResult)controller.ModifierRestaurant(resto);

            Assert.AreEqual(string.Empty, resultat.ViewName);
            Assert.IsFalse(resultat.ViewData.ModelState.IsValid);
        }
        [TestMethod]
        public void RestaurantController_ModifierRestaurantAvecRestoValide_CreerRestaurantEtRenvoiVueIndex()
        {
            using (IDal dal = new DalEnDur())
            {
                RestaurantController controller = new RestaurantController(dal);
                Resto resto = new Resto { Id = 1, Nom = "Resto mate", Telephone = "0102030405" };
                controller.ValideLeModele(resto);

                RedirectToRouteResult resultat = (RedirectToRouteResult)controller.ModifierRestaurant(resto);

                Assert.AreEqual("Index", resultat.RouteValues["action"]);
                Resto restoTrouve = dal.ObtientTousLesRestaurants().First();
                Assert.AreEqual("Resto mate", restoTrouve.Nom);
            }
        }
    }
    [TestClass]
    public class VoteControllerTests
    {
        private IDal dal;
        private int idSondage;
        private VoteController controleur;

        [TestInitialize]
        public void Init()
        {
            dal = new DalEnDur();
            idSondage = dal.CreerUnSondage();

            Mock<ControllerContext> controllerContext = new Mock<ControllerContext>();
            controllerContext.Setup(p => p.HttpContext.Request.Browser.Browser).Returns("1");

            controleur = new VoteController(dal);
            controleur.ControllerContext = controllerContext.Object;
        }
        [TestMethod]
        public void Index_AvecSondageNormalMaisSansUtilisateur_RenvoiLeBonViewModelEtAfficheLaVue()
        {
            ViewResult view = (ViewResult)controleur.Index(idSondage);

            RestaurantVoteViewModel viewModel = (RestaurantVoteViewModel)view.Model;
            Assert.AreEqual(3, viewModel.ListeDesResto.Count);
            Assert.AreEqual(1, viewModel.ListeDesResto[0].Id);
            Assert.IsFalse(viewModel.ListeDesResto[0].EstSelectionne);
            Assert.AreEqual("Resto pinambour (0102030405)", viewModel.ListeDesResto[0].NomEtTelephone);
        }

        [TestMethod]
        public void Index_AvecSondageNormalAvecUtilisateurNayantPasVote_RenvoiLeBonViewModelEtAfficheLaVue()
        {
            dal.AjouterUtilisateur("Nico", "1234");
            dal.AjouterUtilisateur("Jérémie", "1234");

            ViewResult view = (ViewResult)controleur.Index(idSondage);

            RestaurantVoteViewModel viewModel = (RestaurantVoteViewModel)view.Model;
            Assert.AreEqual(3, viewModel.ListeDesResto.Count);
            Assert.AreEqual(1, viewModel.ListeDesResto[0].Id);
            Assert.IsFalse(viewModel.ListeDesResto[0].EstSelectionne);
            Assert.AreEqual("Resto pinambour (0102030405)", viewModel.ListeDesResto[0].NomEtTelephone);
        }
        [TestMethod]
        public void Index_AvecSondageNormalMaisDejaVote_EffectueLeRedirectToAction()
        {
            dal.AjouterUtilisateur("Nico", "1234");
            dal.AjouterUtilisateur("Jérémie", "1234");
            dal.AjouterVote(idSondage, 1, 1);

            RedirectToRouteResult resultat = (RedirectToRouteResult)controleur.Index(idSondage);

            Assert.AreEqual("AfficheResultat", resultat.RouteValues["action"]);
            Assert.AreEqual(idSondage, resultat.RouteValues["id"]);
        }
        [TestMethod]
        public void IndexPost_AvecViewModelInvalide_RenvoiLeBonViewModelEtAfficheLaVue()
        {
            RestaurantVoteViewModel viewModel = new RestaurantVoteViewModel
            {
                ListeDesResto = new List<RestaurantCheckBoxViewModel>
            {
                new RestaurantCheckBoxViewModel { EstSelectionne = false, Id = 2, NomEtTelephone = "Resto pinière (0102030405)"},
                new RestaurantCheckBoxViewModel { EstSelectionne = false, Id = 3, NomEtTelephone = "Resto toro (0102030405)"},
            }
            };
            controleur.ValideLeModele(viewModel);

            ViewResult view = (ViewResult)controleur.Index(viewModel, idSondage);

            viewModel = (RestaurantVoteViewModel)view.Model;
            Assert.AreEqual(2, viewModel.ListeDesResto.Count);
            Assert.AreEqual(2, viewModel.ListeDesResto[0].Id);
            Assert.IsFalse(viewModel.ListeDesResto[0].EstSelectionne);
            Assert.AreEqual("Resto pinière (0102030405)", viewModel.ListeDesResto[0].NomEtTelephone);
        }
        [TestMethod]
        public void IndexPost_AvecViewModelValideMaisPasDutilisateur_RenvoiUneHttpUnauthorizedResult()
        {
            RestaurantVoteViewModel viewModel = new RestaurantVoteViewModel
            {
                ListeDesResto = new List<RestaurantCheckBoxViewModel>
            {
                new RestaurantCheckBoxViewModel { EstSelectionne = true, Id = 2, NomEtTelephone = "Resto pinière (0102030405)"},
                new RestaurantCheckBoxViewModel { EstSelectionne = false, Id = 3, NomEtTelephone = "Resto toro (0102030405)"},
            }
            };
            controleur.ValideLeModele(viewModel);

            HttpUnauthorizedResult view = (HttpUnauthorizedResult)controleur.Index(viewModel, idSondage);

            Assert.AreEqual(401, view.StatusCode);
        }
        [TestMethod]
        public void IndexPost_AvecViewModelValideEtUtilisateur_AppelleBienAjoutVoteEtRenvoiBonneAction()
        {
            Mock<IDal> mock = new Mock<IDal>();
            mock.Setup(m => m.ObtenirUtilisateur("1")).Returns(new Utilisateur { Id = 1, Prenom = "Nico" });

            Mock<ControllerContext> controllerContext = new Mock<ControllerContext>();
            controllerContext.Setup(p => p.HttpContext.Request.Browser.Browser).Returns("1");
            controleur = new VoteController(mock.Object);
            controleur.ControllerContext = controllerContext.Object;

            RestaurantVoteViewModel viewModel = new RestaurantVoteViewModel
            {
                ListeDesResto = new List<RestaurantCheckBoxViewModel>
                {
                    new RestaurantCheckBoxViewModel { EstSelectionne = true, Id = 2, NomEtTelephone = "Resto pinière (0102030405)"},
                    new RestaurantCheckBoxViewModel { EstSelectionne = false, Id = 3, NomEtTelephone = "Resto toro (0102030405)"},
                }
            };
            controleur.ValideLeModele(viewModel);

            RedirectToRouteResult resultat = (RedirectToRouteResult)controleur.Index(viewModel, idSondage);

            mock.Verify(m => m.AjouterVote(idSondage, 2, 1));
            Assert.AreEqual("AfficheResultat", resultat.RouteValues["action"]);
            Assert.AreEqual(idSondage, resultat.RouteValues["id"]);
        }
        [TestMethod]
        public void AfficheResultat_SansAvoirVote_RenvoiVersIndex()
        {
            RedirectToRouteResult resultat = (RedirectToRouteResult)controleur.AfficheResultat(idSondage);

            Assert.AreEqual("Index", resultat.RouteValues["action"]);
            Assert.AreEqual(idSondage, resultat.RouteValues["id"]);
        }

        [TestMethod]
        public void AfficheResultat_AvecVote_RenvoiLesResultats()
        {
            dal.AjouterUtilisateur("Nico", "1234");
            dal.AjouterUtilisateur("Jérémie", "1234");
            dal.AjouterVote(idSondage, 1, 1);

            ViewResult view = (ViewResult)controleur.AfficheResultat(idSondage);

            List<Resultats> model = (List<Resultats>)view.Model;
            Assert.AreEqual(1, model.Count);
            Assert.AreEqual("Resto pinambour", model[0].Nom);
            Assert.AreEqual(1, model[0].NombreDeVotes);
            Assert.AreEqual("0102030405", model[0].Telephone);
        }
        [TestCleanup]
        public void Clean()
        {
            dal.Dispose();
        }
    }
    [TestClass]
    public class TeClass
    {
        public IEnumerable GetValues(int limit)
        {
            Console.WriteLine("Debut itr");
            for (int i = 0; i < limit; i++)
            {
                if (i % 2 == 0)
                {
                    yield return i;
                }
            }
            Console.WriteLine("Fin itr");
        }

        [TestMethod]
        public void Test()
        {
            var v = GetValues(10);
            Console.WriteLine("Saut "+v.GetType().FullName);
            v = GetValues(10);
            Console.WriteLine("Saut " + v.GetType().FullName);
            foreach (object o in v)
            {
                Console.WriteLine(o);
            }
            SubClass subClass = new SubClass();
            SuperClass super = subClass;
            super.Field = 15;
            Console.WriteLine(super.GetField());
            Console.WriteLine(subClass.GetField());
        }
    }
    public class SuperClass
    {
        public int Field;
    }
    public class SubClass:SuperClass
    {
        public MyStruct m = new MyStruct();
        public ref MyStruct GetM()
        {
            return ref m;
        }
    }
    public struct MyStruct
    {
        public int Field;
        public MyStruct(int Param)
        {
            Field = Param;
        }
        public MyStruct(MyStruct Param)
        {
            Console.WriteLine("Copy");
            Field = Param.Field;
        }
    }
    /*public class MaRefClasse
    {
        int re;
        public ref int GetRe()
        {
            return ref re;
        }
    }*/
    [TestClass]
    public class AutresTest
    {
        [TestMethod]
        public void Copie()
        {
            MyStruct str = new MyStruct(10);
            MyStruct copy = str;
            Assert.AreEqual(10, copy.Field);
        }
        [TestMethod]
        public void Copie2()
        {
            /*SubClass sub = new SubClass();
            sub.GetM().Field = 10;
            MyStruct str = sub.m;
            MyStruct copy = str;
            Assert.AreEqual(10, copy.Field);*/
      /*string unicodeString = "Maths use \u03a0 (Pi) for calculations";

      // You can convert a string into a byte array
      byte[] asciiBytes = Encoding.ASCII.GetBytes(unicodeString);

      // You can convert a byte array into a char array
      char[] asciiChars = Encoding.ASCII.GetChars(asciiBytes);
      string asciiString = new string(asciiChars);
      Console.WriteLine(unicodeString);
      // The resulting string is different due to the unsupported character for ASCII encoding
      Console.WriteLine($"Unicode string: {unicodeString}");
      Console.WriteLine($"ASCII string: {asciiString}");*/
    }
  }
    [TestClass]
    public class ListeGeneTest
    {
        [TestMethod]
        public void InsererVide()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0,5);
            Assert.AreEqual(1, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.IsNull(list.Racine.Suivant);
            Assert.AreEqual(5, list.Premier);
            Assert.AreEqual(5, list.Dernier);
        }
        [TestMethod]
        public void InsererLoin()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(1, 5);
            Assert.AreEqual(1, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.IsNull(list.Racine.Suivant);
            Assert.AreEqual(5, list.Premier);
            Assert.AreEqual(5, list.Dernier);
        }
        [TestMethod]
        public void InsererPremier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(0, 6);
            Assert.AreEqual(2, list.Nb);
            Assert.AreEqual(6, list.Racine.Elt);
            Assert.AreEqual(5, list.Racine.Suivant.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.AreEqual(6, list.Premier);
            Assert.AreEqual(5, list.Dernier);
            Assert.AreSame(list.Racine.Suivant.Precedent, list.Racine);
            Assert.AreSame(list.Racine.Suivant.Precedent.Suivant, list.Racine.Suivant);
        }
        [TestMethod]
        public void InsererDernier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            Assert.AreEqual(2, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.AreEqual(5, list.Premier);
            Assert.AreEqual(6, list.Dernier);
            Assert.AreSame(list.Racine.Suivant.Precedent, list.Racine);
            Assert.AreSame(list.Racine.Suivant.Precedent.Suivant, list.Racine.Suivant);
        }
        [TestMethod]
        public void InsererMilieu()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Inserer(1, 7);
            Assert.AreEqual(3, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.AreEqual(7, list.Racine.Suivant.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Suivant.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.AreEqual(5, list.Premier);
            Assert.AreEqual(6, list.Dernier);
            Assert.AreSame(list.Racine.Suivant.Precedent, list.Racine);
        }
        [TestMethod]
        public void InsererMilieuSecond()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Inserer(2, 7);
            list.Inserer(1, 8);
            Assert.AreEqual(4, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.AreEqual(8, list.Racine.Suivant.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Suivant.Elt);
            Assert.AreEqual(7, list.Racine.Suivant.Suivant.Suivant.Elt);
            Assert.IsNull(list.Racine.Precedent);
            Assert.AreEqual(5, list.Premier);
            Assert.AreEqual(7, list.Dernier);
        }
        [TestMethod]
        public void SupprimerDernier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Inserer(2, 7);
            list.Inserer(1, 8);
            list.Supprimer(3);
            Assert.AreEqual(3, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.AreEqual(8, list.Racine.Suivant.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Suivant.Elt);
        }
        [TestMethod]
        public void SupprimerPremier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Inserer(2, 7);
            list.Inserer(1, 8);
            list.Supprimer(0);
            Assert.AreEqual(3, list.Nb);
            Assert.AreEqual(8, list.Racine.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Elt);
            Assert.AreEqual(7, list.Racine.Suivant.Suivant.Elt);
        }
        [TestMethod]
        public void SupprimerMilieu()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Inserer(2, 7);
            list.Inserer(1, 8);
            list.Supprimer(1);
            Assert.AreEqual(3, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
            Assert.AreEqual(6, list.Racine.Suivant.Elt);
            Assert.AreEqual(7, list.Racine.Suivant.Suivant.Elt);
        }
        [TestMethod]
        public void SupprimerDernierPremier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Supprimer(1);
            Assert.AreEqual(1, list.Nb);
            Assert.AreEqual(5, list.Racine.Elt);
        }
        [TestMethod]
        public void SupprimerPremierDernier()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Inserer(1, 6);
            list.Supprimer(0);
            Assert.AreEqual(1, list.Nb);
            Assert.AreEqual(6, list.Racine.Elt);
        }
        [TestMethod]
        public void SupprimerRacine()
        {
            ListeGene<int> list = new ListeGene<int>();
            list.Inserer(0, 5);
            list.Supprimer(0);
            Assert.AreEqual(0, list.Nb);
            Assert.IsNull(list.Racine);
        }
    }
    public class ListeGene<T>
    {
        public T Premier {
            get {
                if (Racine == null)
                {
                    return default(T);
                }
                return Racine.Elt;
            }
        }
        public T Dernier {
            get {
                if (Racine == null)
                {
                    return default(T);
                }
                Element<T> elt = Racine;
                while (true)
                {
                    Element<T> s = elt.Suivant;
                    if (s == null)
                    {
                        break;
                    }
                    elt = s;
                }
                return elt.Elt;
            }
        }
        public int Nb
        {
            get
            {
                if (Racine == null)
                {
                    return 0;
                }
                Element<T> elt = Racine;
                int nb = 1;
                while (true)
                {
                    Element<T> s = elt.Suivant;
                    if (s == null)
                    {
                        break;
                    }
                    nb++;
                    elt = s;
                }
                return nb;
            }
        }
        public Element<T> Racine;
        public void Ajout(T elt)
        {
            Inserer(Nb, elt);
        }
        public void Supprimer(int indice)
        {
            Element<T> courant = Racine;
            for (int i = 0; i < indice; i++)
            {
                if (courant == null)
                {
                    break;
                }
                courant = courant.Suivant;
            }
            if (courant == null)
            {
                return;
            }
            if (courant.Precedent == null)
            {
                if (courant.Suivant == null)
                {
                    Racine = null;
                    return;
                }
                courant.Suivant.Precedent = null;
                Racine = courant.Suivant;
                courant.Suivant = null;
                return;
            }
            if (courant.Suivant == null)
            {
                courant.Precedent.Suivant = null;
                courant.Precedent = null;
                return;
            }
            courant.Precedent.Suivant = courant.Suivant;
            courant.Suivant.Precedent = courant.Precedent;
            courant.Precedent = null;
            courant.Suivant = null;
        }
        public void Inserer(int indice, T elt)
        {
            if (Racine == null)
            {
                Element<T> ins = new Element<T>();
                ins.Elt = elt;
                Racine = ins;
                return;
            }
            if (indice == 0)
            {
                Element<T> ins = new Element<T>();
                ins.Elt = elt;
                ins.Suivant = Racine;
                Racine.Precedent = ins;
                Racine = ins;
                return;
            }
            Element<T> courant = Racine;
            int to = indice - 1;
            for (int i = 0; i < to; i++)
            {
                if (courant == null)
                {
                    break;
                }
                courant = courant.Suivant;
            }
            if (courant == null)
            {
                return;
            }
            Element<T> ins2 = new Element<T>();
            ins2.Precedent = courant;
            ins2.Elt = elt;
            ins2.Suivant = courant.Suivant;
            courant.Suivant = ins2;
        }
    }
    public class Element<T>
    {
        public Element<T> Precedent;
        public Element<T> Suivant;
        public T Elt;
    }

    public static class SuperClassUtil
    {
        public static int GetField(this SuperClass sup)
        {
            return sup.Field;
        }
        public static int GetField(this SubClass sup)
        {
            return sup.Field*2;
        }
  }
}
