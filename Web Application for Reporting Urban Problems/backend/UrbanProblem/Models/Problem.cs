namespace UrbanProblem.Models
{
    public class Problem
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Location { get; set; }
        public double? Latitude { get; set; }
        public double? Longitude { get; set; }
        public String Description { get; set; }
        public bool Priority { get; set; }
        public bool Solved { get; set; }
        public DateTime Date { get; set; }
        public ICollection<Review> Reviews { get; set; }
        public ICollection<ProblemResponsible> ProblemResponsibles { get; set; }
        public ICollection<ProblemCategory> ProblemCategories { get; set; }
        public ICollection<Image>? Images { get; set; }
    }
}
