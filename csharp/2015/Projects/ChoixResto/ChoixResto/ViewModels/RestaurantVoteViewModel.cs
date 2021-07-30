using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace ChoixResto.ViewModels
{
    public class RestaurantVoteViewModel : IValidatableObject
    {
        public List<RestaurantCheckBoxViewModel> ListeDesResto { get; set; }

        public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)
        {
            if (ListeDesResto != null && !ListeDesResto.Any(r => r.EstSelectionne))
            {
                yield return new ValidationResult("Vous devez choisir au moins un restaurant", new[] { "ListeDesResto" });
            }

            /*List<ValidationResult> errs = new List<ValidationResult>();
            foreach (RestaurantCheckBoxViewModel r in ListeDesResto)
            {
                if (r.EstSelectionne)
                {
                    return new List<ValidationResult>();
                }
                ValidationResult res = new ValidationResult("Une case doit etre cochee");
                errs.Add(res);
            }
            return errs;*/
            // à faire !
        }
    }
}