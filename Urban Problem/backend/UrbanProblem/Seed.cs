using System.Diagnostics.Metrics;
using UrbanProblem.Data;
using UrbanProblem.Models;

namespace UrbanProblem
{
    public class Seed
    {
        private readonly DataContext dataContext;
        public Seed(DataContext context)
        {
            this.dataContext = context;
        }
        public void SeedDataContext()
        {
            if (!dataContext.ProblemResponsibles.Any())
            {
                var problemResponsibles = new List<ProblemResponsible>()
                {
                    new ProblemResponsible()
                    {
                        Problem = new Problem()
                        {
                            Title = "Pasaj inundat",
                            Location = "Pasajul Obor",
                            Description = "Pasajul este inundat. Circulatia este oprita.",
                            Date = new DateTime(2023,10,5),     // year, month, day
                            ProblemCategories = new List<ProblemCategory>()
                            {
                                new ProblemCategory { Category = new Category() { Type = "Inundatie"}}
                            },
                            Reviews = new List<Review>()
                            {
                                new Review { Title= "Prea multa apa", Text = "Il propun pe delfinu Flipper comandant la circulatie", Rating = 3,
                                Reporter = new Reporter(){ FirstName = "Ilie", LastName = "Moromete" } },
                                new Review { Title= "Avea dreptate Noe", Text = "O sa-mi cumpar barca", Rating = 5,
                                Reporter = new Reporter(){ FirstName = "Mirel", LastName = "Palada" } },
                                new Review { Title= "Ajutor! Inundatie", Text = "Basescu mai venea in vizita cand era inundatie", Rating = 4,
                                Reporter = new Reporter(){ FirstName = "Marius", LastName = "Tuca" } },
                            },
                            Images = null,
                            Latitude = 44.44971853745421,
                            Longitude = 26.124325690989274,
                            Priority = true,
                            Solved = true,
                        },
                        Responsible = new Responsible()
                        {
                            Name = "Toma Caragiu",
                            Area = "Sector 2",
                            Authority = new Authority()
                            {
                                Name = "Politia rutiera"
                            }
                        }
                    },
                    new ProblemResponsible()
                    {
                        Problem = new Problem()
                        {
                            Title = "Groapa asfalt",
                            Location = "In fata Bibliotecii Nationale(Timpuri Noi)",
                            Description = "In fiecare zi trec pe aici in drum spre serviciu.",
                            Date = new DateTime(2020,1,1),
                            ProblemCategories = new List<ProblemCategory>()
                            {
                                new ProblemCategory { Category = new Category() { Type = "Drum dezafectat"}}
                            },
                            Reviews = new List<Review>()
                            {
                                new Review { Title= "Groapa", Text = "N-am, daca n-am", Rating = 2,
                                Reporter = new Reporter(){ FirstName = "Ilie", LastName = "Moromete" } },
                                new Review { Title= "Votati PSD", Text = "Ne meritam soarta", Rating = 3,
                                Reporter = new Reporter(){ FirstName = "Mirel", LastName = "Palada" } },
                                new Review { Title= "Drum dezafectat", Text = "Da dom'le sa fure, da' sa si faca ceva", Rating = 3,
                                Reporter = new Reporter(){ FirstName = "Marius", LastName = "Tuca" } },
                            },
                            Images = null,
                            Latitude = 44.42616037903486,   
                            Longitude = 26.109955673102622,
                            Priority = false,
                            Solved = false,
                        },
                        Responsible = new Responsible()
                        {
                            Name = "Dem Radulescu",
                            Area = "Sector 3",
                            Authority = new Authority()
                            {
                                Name = "Primarie Sector 3"
                            }
                        }
                    },
                    new ProblemResponsible()
                    {
                        Problem = new Problem()
                        {
                            Title = "Furtuna puternica, copac cazut",
                            Location = "Strada Kiseleff, langa Antipa",
                            Description = "Bine ca nu a fost nimeni ranit. Pacat de masina, totusi!",
                            Date = new DateTime(2024,3,11),
                            ProblemCategories = new List<ProblemCategory>()
                            {
                                new ProblemCategory { Category = new Category() { Type = "Accident"}}
                            },
                            Reviews = new List<Review>()
                            {
                                new Review { Title= "Pacat de masina", Text = "Asta vine dupa facultati", Rating = 6,
                                Reporter = new Reporter(){ FirstName = "Ilie", LastName = "Moromete" } },
                                new Review { Title= "Vin alegerile", Text = "Aici e mana lu' Videanu", Rating = 2,
                                Reporter = new Reporter(){ FirstName = "Mirel", LastName = "Palada" } },
                                new Review { Title= "Copac daramat", Text = "Nici la mine in Caracal nu vezi asa ceva", Rating = 3,
                                Reporter = new Reporter(){ FirstName = "Marius", LastName = "Tuca" } },
                            },
                            Images = null,
                            Latitude = 44.43951412504414,  
                            Longitude = 26.08691535240682,
                            Priority = false,
                            Solved = false,
                        },
                        Responsible = new Responsible()
                        {
                            Name = "Florin Piersic",
                            Area = "Sector 1",
                            Authority = new Authority()
                            {
                                Name = "Primarie Sector 1"
                            }
                        }
                    }
                };
                dataContext.ProblemResponsibles.AddRange(problemResponsibles);
                dataContext.SaveChanges();
            }
        }
    }
}
