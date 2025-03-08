namespace UrbanProblem.Models
{
    public class ProblemCategory
    {
        public int ProblemId { get; set; }
        public int CategoryId { get; set; }
        public Problem Problem { get; set; }
        public Category Category { get; set; }
    }
}
