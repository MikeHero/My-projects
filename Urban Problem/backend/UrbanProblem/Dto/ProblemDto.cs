namespace UrbanProblem.Dto
{
    public class ProblemDto
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Location { get; set; }
        public bool Priority { get; set; }
        public String Description { get; set; }
        public bool Solved { get; set; }
        public DateTime Date { get; set; }
        public double? Latitude { get; set; }
        public double? Longitude { get; set; }
    }
}
