namespace UrbanProblem.Models
{
    public class Feedback
    {
        public int Id { get; set; }
        public string Sugestion { get; set; }

        public int Grade { get; set; }
        public string AgeGroup { get; set; }
        public bool Agreement { get; set; }
    }
}
