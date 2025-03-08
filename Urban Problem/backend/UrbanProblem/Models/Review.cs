namespace UrbanProblem.Models
{
    public class Review
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Text { get; set; }
        public int Rating { get; set; }
        public Reporter Reporter { get; set; }
        public Problem Problem { get; set; }
    }
}
