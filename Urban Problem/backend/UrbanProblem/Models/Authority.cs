namespace UrbanProblem.Models
{
    public class Authority
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public ICollection<Responsible> Responsibles { get; set; }
    }
}
