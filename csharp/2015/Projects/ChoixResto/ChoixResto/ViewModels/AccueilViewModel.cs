using ChoixResto.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace ChoixResto.ViewModels
{
    public class AccueilViewModel
    {
        [Display(Name = "Le message")]
        public string Message { get; set; }
        public DateTime Date { get; set; }
        public string Login { get; set; }
        public Models.Resto Resto { get; set; }
        public List<Models.Resto> ListeDesRestos { get; set; }
        public string GetNom()
        {
            return Resto.Nom;
        }
    }
    public class RestaurantCheckBoxViewModel
    {
        public int Id { get; set; }
        public Resto Rest { get; set; }
        public string NomEtTelephone { get; set; }
        public bool EstSelectionne { get; set; }
    }
    
}