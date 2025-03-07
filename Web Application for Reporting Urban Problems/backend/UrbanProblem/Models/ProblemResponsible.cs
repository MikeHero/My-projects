namespace UrbanProblem.Models
{
    public class ProblemResponsible
    {
        public int ProblemId { get; set; }
        public int ResponsibleId { get; set; }
        public Problem Problem { get; set; }
        public Responsible Responsible { get; set; }
    }
}
