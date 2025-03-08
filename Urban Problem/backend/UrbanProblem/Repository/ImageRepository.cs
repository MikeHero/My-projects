using AutoMapper;
using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class ImageRepository : IImageRepository
    {
        private readonly DataContext _context;
        private readonly IMapper _mapper;
        private readonly IWebHostEnvironment _hostEnvironment;

        public ImageRepository(DataContext context, IMapper mapper, IWebHostEnvironment hostEnvironment)
        {
            _context = context;
            _mapper = mapper;
            _hostEnvironment = hostEnvironment;
            Console.WriteLine($"WebRootPath: {_hostEnvironment.WebRootPath}");
        }
        public bool CreateImage(Image image, IFormFile file)
        {
            if (file == null || file.Length == 0)
            {
                return false;
            }

            // Ensure the problem is correctly loaded
            var problem = _context.Problems.FirstOrDefault(p => p.Id == image.Problem.Id);
            if (problem == null)
            {
                return false; // Or handle appropriately
            }

            // Set the problem object on the image
            image.Problem = problem;

            // Ensure image Id is set or use a placeholder for the initial filename
            var uploadsFolder = Path.Combine(_hostEnvironment.WebRootPath, $"Problem_{image.Problem.Id}_images");
            Directory.CreateDirectory(uploadsFolder);

            var imageFileName = $"Photo_{Guid.NewGuid()}.jpg"; // Use a GUID or other unique identifier for initial filename
            var imagePath = Path.Combine(uploadsFolder, imageFileName);
            
            image.ImageURL = imagePath;

            // Debug log to check image path
            Console.WriteLine($"Image Path: {imagePath}");

            using (var stream = new FileStream(imagePath, FileMode.Create))
            {
                file.CopyTo(stream);
            }

            image.ImageData = File.ReadAllBytes(imagePath);
            _context.Add(image);

            var saveResult = Save();
            if (saveResult)
            {
                // Rename the file to include the image Id after it has been saved and Id is generated
                var savedImage = _context.Images.FirstOrDefault(i => i.ImageData == image.ImageData);
                if (savedImage != null)
                {
                    var newFileName = $"Photo_{savedImage.Id}.jpg";
                    var newImagePath = Path.Combine(uploadsFolder, newFileName);
                    File.Move(imagePath, newImagePath); // Rename the file
                    
                    
                    
                    image.ImageURL = newImagePath;
                    _context.Update(image);
                    saveResult = Save();
                }
            }

            return saveResult;
        }

        public bool DeleteImage(Image image)
        {
            _context.Remove(image);
            return Save();
        }

        public Image GetImage(int id)
        {
            return _context.Images.Where(i => i.Id == id).FirstOrDefault();
        }

        public ICollection<Image> GetImagesOfAProblem(int probId)
        {
            return _context.Images.Where(i => i.Problem.Id == probId).ToList();
        }

        public bool ImageExists(int id)
        {
            return _context.Images.Any(i => i.Id == id);
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0) ? true : false;
        }
    }
}
