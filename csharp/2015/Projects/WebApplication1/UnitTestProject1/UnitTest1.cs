using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using WebApplication1.Models;
using System.Web;
using Moq;
using System.Web.Routing;
using WebApplication1;
using System.Web.Mvc;

namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void ObtenirLaMeteoDuJour_AvecUnBouchon_RetourneSoleil()
        {
            Meteo fausseMeteo = new Meteo
            {
                Temperature = 25,
                Temps = Temps.Soleil
            };
            Mock<IDal> mock = new Mock<IDal>();
            mock.Setup(dal => dal.ObtenirLaMeteoDuJour()).Returns(fausseMeteo);

            IDal fausseDal = mock.Object;
            Meteo meteoDuJour = fausseDal.ObtenirLaMeteoDuJour();
            Assert.AreEqual(25, meteoDuJour.Temperature);
            Assert.AreEqual(Temps.Soleil, meteoDuJour.Temps);
        }
        [TestMethod]
        public void Alea()
        {
            Mock<IGenerateur> mock = new Mock<IGenerateur>();
            mock.Setup(generateur => generateur.Valeur).Returns(5);

            Assert.AreEqual(5, mock.Object.Valeur);
        }
        [TestMethod]
        public void RouteTests()
        {
            Mock<HttpContextBase> mockContext = new Mock<HttpContextBase>();
            mockContext.Setup(c => c.Request.AppRelativeCurrentExecutionFilePath).Returns("~/Home/Index/2");
            RouteCollection routes = new RouteCollection();
            RouteConfig.RegisterRoutes(routes);
            RouteData routeData = routes.GetRouteData(mockContext.Object);
            Assert.IsNotNull(routeData);
            Assert.AreEqual("Home", routeData.Values["controller"]);
            Assert.AreEqual("Index", routeData.Values["action"]);
            Assert.AreEqual("2", routeData.Values["id"]);
        }
        [TestMethod]
        public void Routes_PageHome_RetourneControleurHomeEtMethodeIndex()
        {
            RouteData routeData = DefinirUrl("~/");
            Assert.IsNotNull(routeData);
            Assert.AreEqual("Home", routeData.Values["controller"]);
            Assert.AreEqual("Index", routeData.Values["action"]);
            Assert.AreEqual(UrlParameter.Optional, routeData.Values["id"]);
        }

        [TestMethod]
        public void Routes_PageHomeIndex2_RetourneControleurHomeEtMethodeIndexEtParam2()
        {
            RouteData routeData = DefinirUrl("~/Home/Index/2");
            Assert.IsNotNull(routeData);
            Assert.AreEqual("Home", routeData.Values["controller"]);
            Assert.AreEqual("Index", routeData.Values["action"]);
            Assert.AreEqual("2", routeData.Values["id"]);
        }

        [TestMethod]
        public void Routes_MeteoAujourdhui_RetourneControleurMeteoMethodeAfficherEtParametreAujourdhui()
        {
            DateTime aujourdhui = DateTime.Now;
            RouteData routeData = DefinirUrl(string.Format("~/{0}/{1}/{2}", aujourdhui.Day, aujourdhui.Month, aujourdhui.Year));
            Assert.IsNotNull(routeData);
            Assert.AreEqual("Meteo", routeData.Values["controller"]);
            Assert.AreEqual("Afficher", routeData.Values["action"]);
            Assert.AreEqual(aujourdhui.Day.ToString(), routeData.Values["jour"]);
            Assert.AreEqual(aujourdhui.Month.ToString(), routeData.Values["mois"]);
            Assert.AreEqual(aujourdhui.Year.ToString(), routeData.Values["annee"]);
        }
        [TestMethod]
        public void Routes_UrlBidon_RetourneNull()
        {
            RouteData routeData = DefinirUrl("/Url/bidon/pas/bonne");
            Assert.IsNull(routeData);
        }
        private static RouteData DefinirUrl(string url)
        {
            Mock<HttpContextBase> mockContext = new Mock<HttpContextBase>();
            mockContext.Setup(c => c.Request.AppRelativeCurrentExecutionFilePath).Returns(url);
            RouteCollection routes = new RouteCollection();
            RouteConfig.RegisterRoutes(routes);
            RouteData routeData = routes.GetRouteData(mockContext.Object);
            return routeData;
        }
    }
}
