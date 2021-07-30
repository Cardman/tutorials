using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class AccueilController : Controller
    {
        // GET: Accueil
        public string Index(string id)
        {
            return "couper "+id;
        }
    }
}