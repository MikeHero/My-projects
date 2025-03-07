namespace UrbanProblem.Models
{
    public class Image
    {
        public int Id { get; set; }
        public string ImageURL { get; set; }
        public Problem Problem { get; set; }
        public byte[] ImageData { get; set; }
    }
}
