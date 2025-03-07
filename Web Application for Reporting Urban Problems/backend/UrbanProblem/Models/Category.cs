namespace UrbanProblem.Models
{
    public class Category
    {
        public int Id { get; set; }
        public string Type { get; set; }
        public ICollection<ProblemCategory> ProblemCategories { get; set; }

    }
}
