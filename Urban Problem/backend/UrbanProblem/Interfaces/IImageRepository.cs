using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IImageRepository
    {
        ICollection<Image> GetImagesOfAProblem(int probId);

        Image GetImage(int id);

        bool ImageExists(int id);
        bool CreateImage(Image image, IFormFile file);
        bool DeleteImage(Image image);
        bool Save();
    }
}
