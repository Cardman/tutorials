using ChoixResto.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using System.Linq;
using System.Reflection;
using System.Web;

namespace ChoixResto.Models
{
    public class Utilisateur
    {
        public int Id { get; set; }
        [Required, MaxLength(80)]
        public string Prenom { get; set; }
        [Required, MaxLength(80)]
        public string Mdp { get; set; }
        [Range(18, 120)]
        public int Age { get; set; }
    }
    [Table("Restos")]
    public class Resto
    //: IValidatableObject
    {
        public int Id { get; set; }
        [Required(ErrorMessage = "Le nom du restaurant doit être saisi")]
        public string Nom { get; set; }
        [Display(Name = "Téléphone")]
        [RegularExpression(@"^[0-9]{3,10}$", ErrorMessage = "Le numéro de téléphone est incorrect")]
        [AuMoinsUnDesDeux(Parametre1 = "Telephone", Parametre2 = "Email", ErrorMessage = "Vous devez saisir au moins un moyen de contacter le restaurant")]
        public string Telephone { get; set; }
        [AuMoinsUnDesDeux(Parametre1 = "Telephone", Parametre2 = "Email", ErrorMessage = "Vous devez saisir au moins un moyen de contacter le restaurant")]
        public string Email { get; set; }

        /*public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)
        {
            if (string.IsNullOrWhiteSpace(Telephone) && string.IsNullOrWhiteSpace(Email))
            {
                yield return new ValidationResult("Vous devez saisir au moins un moyen de contacter le restaurant", new[] { "Telephone", "Email" });
            }
        }*/
    }
    public class Votes
    {
        public virtual List<RestaurantCheckBoxViewModel> Restos { get; set; }
        public virtual Utilisateur Utilisateur { get; set; }
        public int IdSondage;
        public bool Error;
        public string Err()
        {
            if (!Error)
            {
                return "";
            }
            return "Veuillez cocher une case";
        }
        /*public List<Vote> CreerVotes()
        {
            var ListVo = new List<Vote>();
            foreach (var r in Restos)
            {
                Vote v = new Vote();
                v.Resto = r.Rest;
                v.Utilisateur = Utilisateur;
                ListVo.Add(v);
            }
            return ListVo;
        }*/
    }
    public class Welcome
    {
        public List<Resto> Bdd;
        public List<Sondage> Sondages;
        public string Prenom;
    }
    public class Vote
    {
        public int Id { get; set; }
        public virtual Resto Resto { get; set; }
        public virtual Utilisateur Utilisateur { get; set; }
    }
    public class Sondage
    {
        public int Id { get; set; }
        public DateTime Date { get; set; }
        public virtual List<Vote> Votes { get; set; }
    }
    public class BddContext : DbContext
    {
        public DbSet<Sondage> Sondages { get; set; }
        public DbSet<Resto> Restos { get; set; }
        public DbSet<Utilisateur> Utilisateurs { get; set; }
    }
    public interface IDal : IDisposable
    {
        void CreerRestaurant(string nom, string telephone);
        void ModifierRestaurant(int id, string nom, string telephone);
        List<Resto> ObtientTousLesRestaurants();
        bool RestaurantExiste(string v);
        Utilisateur ObtenirUtilisateur(int v);
        List<Sondage> ObtenirSondages();
        Utilisateur ObtenirUtilisateur(string v);
        int AjouterUtilisateur(string v1, string v2);
        Utilisateur Authentifier(string v1, string v2);
        bool ADejaVote(int v1, string v2);
        int CreerUnSondage();
        void AjouterVote(int idSondage, int v, int idUtilisateur);
        List<Resultats> ObtenirLesResultats(int idSondage);
        bool ADejaVoteBis(int idSon, string v);
    }
    public class Dal : IDal
    {
        public static int NbInst;
        private BddContext bdd;

        public Dal()
        {
            bdd = new BddContext();
            NbInst++;
        }
        public void CreerRestaurant(string nom, string telephone)
        {
            bdd.Restos.Add(new Resto { Nom = nom, Telephone = telephone });
            bdd.SaveChanges();
        }
        public void ModifierRestaurant(int id, string nom, string telephone)
        {
            Resto restoTrouve = bdd.Restos.FirstOrDefault(resto => resto.Id == id);
            if (restoTrouve != null)
            {
                restoTrouve.Nom = nom;
                restoTrouve.Telephone = telephone;
                restoTrouve.Email = "gmail.com";
                bdd.SaveChanges();
            }
        }
        public List<Resto> ObtientTousLesRestaurants()
        {
            return bdd.Restos.ToList();
        }

        public void Dispose()
        {
            bdd.Dispose();
        }

        public bool RestaurantExiste(string v)
        {
            return bdd.Restos.FirstOrDefault(resto => resto.Nom == v) != null;
        }

        public Utilisateur ObtenirUtilisateur(int v)
        {
            return bdd.Utilisateurs.FirstOrDefault(ut => ut.Id == v);
        }

        public Utilisateur ObtenirUtilisateur(string v)
        {
            try
            {
                int Id = int.Parse(v);
                return bdd.Utilisateurs.FirstOrDefault(ut => ut.Id == Id);
            } catch (Exception e)
            {
                return null;
            }
        }

        public int AjouterUtilisateur(string v1, string v2)
        {
            var Ut = new Utilisateur { Prenom = v1, Mdp = v2, Age = 18 };
            bdd.Utilisateurs.Add(Ut);
            bdd.SaveChanges();
            return Ut.Id;
        }

        public Utilisateur Authentifier(string v1, string v2)
        {
            return bdd.Utilisateurs.FirstOrDefault(Ut => Ut.Prenom == v1 && Ut.Mdp == v2);
        }

        public bool ADejaVote(int v1, string v2)
        {
            var Son = bdd.Sondages.FirstOrDefault(So => So.Id == v1);
            if (Son == null)
            {
                return false;
            }
            var Ut = ObtenirUtilisateur(v2);
            if (Ut == null)
            {
                return false;
            }
            return Son.Votes.FirstOrDefault(Vote => Vote.Utilisateur.Id == Ut.Id) != null;
        }
        public bool ADejaVoteBis(int idSondage, string idStr)
        {
            var utilisateur = ObtenirUtilisateur(idStr);
            if (utilisateur != null)
            {
                Sondage sondage = bdd.Sondages.First(s => s.Id == idSondage);
                if (sondage.Votes == null)
                {
                    return false;
                }
                return sondage.Votes.Any(v => v.Utilisateur != null && v.Utilisateur.Id == utilisateur.Id);
            }
            return false;
        }
        public int CreerUnSondage()
        {
            var Son = new Sondage { };
            Son.Date = DateTime.Now;
            Son.Votes = new List<Vote>();
            bdd.Sondages.Add(Son);
            bdd.SaveChanges();
            return Son.Id;
        }

        public void AjouterVote(int idSondage, int v, int idUtilisateur)
        {
            var Son = bdd.Sondages.FirstOrDefault(So => So.Id == idSondage);
            if (Son == null)
            {
                return;
            }
            var Ut = ObtenirUtilisateur(idUtilisateur);
            var restoTrouve = bdd.Restos.FirstOrDefault(resto => resto.Id == v);
            if (Ut == null || restoTrouve == null)
            {
                return;
            }
            if (Son.Votes.FirstOrDefault(Vote => Vote.Resto == restoTrouve && Vote.Utilisateur == Ut) != null)
            {
                return;
            }
            Son.Votes.Add(new Vote {Resto = restoTrouve, Utilisateur = Ut });
            bdd.SaveChanges();
        }
        public List<Sondage> ObtenirSondages()
        {
            return bdd.Sondages.ToList();
        }
        public List<Resultats> ObtenirLesResultats(int idSondage)
        {
            var Son = bdd.Sondages.FirstOrDefault(So => So.Id == idSondage);
            if (Son == null)
            {
                return new List<Resultats>();
            }
            List<Resultats> Res = new List<Resultats>();
            foreach (var v in Son.Votes.GroupBy(Vote => Vote.Resto))
            {
                var Re = new Resultats();
                var restoTrouve = v.Key;
                Re.Nom = restoTrouve.Nom;
                Re.NombreDeVotes = v.Count();
                Re.Telephone = restoTrouve.Telephone;
                Res.Add(Re);
            }
            return Res;
        }
    }
    public class Resultats
    {
        public string Nom { get; set; }
        public int NombreDeVotes { get; set; }
        public string Telephone { get; set; }
    }
    public class AuMoinsUnDesDeuxAttribute : ValidationAttribute
    {
        public string Parametre1 { get; set; }
        public string Parametre2 { get; set; }

        public AuMoinsUnDesDeuxAttribute() : base("Vous devez saisir au moins un moyen de contacter le restaurant")
        {
        }

        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            PropertyInfo[] proprietes = validationContext.ObjectType.GetProperties();
            PropertyInfo info1 = proprietes.FirstOrDefault(p => p.Name == Parametre1);
            PropertyInfo info2 = proprietes.FirstOrDefault(p => p.Name == Parametre2);

            string valeur1 = info1.GetValue(validationContext.ObjectInstance) as string;
            string valeur2 = info2.GetValue(validationContext.ObjectInstance) as string;

            if (string.IsNullOrWhiteSpace(valeur1) && string.IsNullOrWhiteSpace(valeur2))
                return new ValidationResult(ErrorMessage);
            return ValidationResult.Success;
        }
    }
    public class DalEnDur : IDal
    {
        private List<Resto> listeDesRestaurants;
        private List<Utilisateur> listeDesUtilisateurs;
        private List<Sondage> listeDessondages;

        public DalEnDur()
        {
            listeDesRestaurants = new List<Resto>
        {
            new Resto { Id = 1, Nom = "Resto pinambour", Telephone = "0102030405"},
            new Resto { Id = 2, Nom = "Resto pinière", Telephone = "0102030405"},
            new Resto { Id = 3, Nom = "Resto toro", Telephone = "0102030405"},
        };
            listeDesUtilisateurs = new List<Utilisateur>();
            listeDessondages = new List<Sondage>();
        }

        public List<Resto> ObtientTousLesRestaurants()
        {
            return listeDesRestaurants;
        }

        public void CreerRestaurant(string nom, string telephone)
        {
            int id = listeDesRestaurants.Count == 0 ? 1 : listeDesRestaurants.Max(r => r.Id) + 1;
            listeDesRestaurants.Add(new Resto { Id = id, Nom = nom, Telephone = telephone });
        }

        public void ModifierRestaurant(int id, string nom, string telephone)
        {
            Resto resto = listeDesRestaurants.FirstOrDefault(r => r.Id == id);
            if (resto != null)
            {
                resto.Nom = nom;
                resto.Telephone = telephone;
            }
        }

        public bool RestaurantExiste(string nom)
        {
            return listeDesRestaurants.Any(resto => string.Compare(resto.Nom, nom, StringComparison.CurrentCultureIgnoreCase) == 0);
        }

        public int AjouterUtilisateur(string nom, string motDePasse)
        {
            int id = listeDesUtilisateurs.Count == 0 ? 1 : listeDesUtilisateurs.Max(u => u.Id) + 1;
            listeDesUtilisateurs.Add(new Utilisateur { Id = id, Prenom = nom, Mdp = motDePasse });
            return id;
        }

        public Utilisateur Authentifier(string nom, string motDePasse)
        {
            return listeDesUtilisateurs.FirstOrDefault(u => u.Prenom == nom && u.Mdp == motDePasse);
        }

        public Utilisateur ObtenirUtilisateur(int id)
        {
            return listeDesUtilisateurs.FirstOrDefault(u => u.Id == id);
        }

        public Utilisateur ObtenirUtilisateur(string idStr)
        {
            int id;
            if (int.TryParse(idStr, out id))
                return ObtenirUtilisateur(id);
            return null;
        }

        public int CreerUnSondage()
        {
            int id = listeDessondages.Count == 0 ? 1 : listeDessondages.Max(s => s.Id) + 1;
            listeDessondages.Add(new Sondage { Id = id, Date = DateTime.Now, Votes = new List<Vote>() });
            return id;
        }

        public void AjouterVote(int idSondage, int idResto, int idUtilisateur)
        {
            Vote vote = new Vote
            {
                Resto = listeDesRestaurants.First(r => r.Id == idResto),
                Utilisateur = listeDesUtilisateurs.First(u => u.Id == idUtilisateur)
            };
            Sondage sondage = listeDessondages.First(s => s.Id == idSondage);
            sondage.Votes.Add(vote);
        }
        public bool ADejaVoteBis(int idSondage, string idStr)
        {
            var utilisateur = ObtenirUtilisateur(idStr);
            if (utilisateur != null)
            {
                Sondage sondage = listeDessondages.First(s => s.Id == idSondage);
                if (sondage.Votes == null)
                {
                    return false;
                }
                return sondage.Votes.Any(v => v.Utilisateur != null && v.Utilisateur.Id == utilisateur.Id);
            }
            return false;
        }
        public bool ADejaVote(int idSondage, string idStr)
        {
            Utilisateur utilisateur = ObtenirUtilisateur(idStr);
            if (utilisateur == null)
                return false;
            Sondage sondage = listeDessondages.First(s => s.Id == idSondage);
            return sondage.Votes.Any(v => v.Utilisateur.Id == utilisateur.Id);
        }
        public List<Sondage> ObtenirSondages()
        {
            return listeDessondages;
        }
        public List<Resultats> ObtenirLesResultats(int idSondage)
        {
            List<Resto> restaurants = ObtientTousLesRestaurants();
            List<Resultats> resultats = new List<Resultats>();
            Sondage sondage = listeDessondages.First(s => s.Id == idSondage);
            foreach (IGrouping<int, Vote> grouping in sondage.Votes.GroupBy(v => v.Resto.Id))
            {
                int idRestaurant = grouping.Key;
                Resto resto = restaurants.First(r => r.Id == idRestaurant);
                int nombreDeVotes = grouping.Count();
                resultats.Add(new Resultats { Nom = resto.Nom, Telephone = resto.Telephone, NombreDeVotes = nombreDeVotes });
            }
            return resultats;
        }

        public void Dispose()
        {
            listeDesRestaurants = new List<Resto>();
            listeDesUtilisateurs = new List<Utilisateur>();
            listeDessondages = new List<Sondage>();
        }
    }
}