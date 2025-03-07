namespace UrbanProblem.Models
{
    public class Responsible
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Area { get; set; }
        public Authority Authority {  get; set; }
        public ICollection<ProblemResponsible> ProblemResponsibles { get; set; }
    }
}
