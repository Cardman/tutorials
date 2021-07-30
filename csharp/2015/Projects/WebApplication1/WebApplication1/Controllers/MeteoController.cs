using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class MeteoController : Controller
    {
        public string Afficher(int jour, int mois, int annee)
        {
            return "Il fait soleil le " + jour + "/" + mois + "/" + annee;
        }
    }
}