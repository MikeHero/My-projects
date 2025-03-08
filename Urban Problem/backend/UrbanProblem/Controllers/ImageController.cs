using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using UrbanProblem.Dto;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;
using UrbanProblem.Repository;

namespace UrbanProblem.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class ImageController : ControllerBase
    {
        private readonly IImageRepository _imageRepository;
        private readonly IProblemRepository _problemRepository;
        private readonly IMapper _mapper;

        public ImageController(IImageRepository imageRepository, IProblemRepository problemRepository, IMapper mapper)
        {
            _imageRepository = imageRepository;
            _problemRepository = problemRepository;
            _mapper = mapper;
        }

        [HttpGet("{probId}")]
        [ProducesResponseType(200, Type = typeof(Responsible))]
        [ProducesResponseType(400)]
        public IActionResult GetImagesByProblem(int probId)
        {
            if (! _problemRepository.ProblemExists(probId))
                return NotFound();

            var images = _mapper.Map<List<ImageDto>>(
                _imageRepository.GetImagesOfAProblem(probId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(images);
        }

        [HttpPost("{probId}")]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateImage(int probId, [FromForm] IFormFile imageFile)
        {
            if (imageFile == null || imageFile.Length == 0)
            {
                return BadRequest("No image uploaded.");
            }

            if (imageFile.Length > 25 * 1024 * 1024) // 25MB limit
            {
                return BadRequest("File size exceeds the limit of 25MB.");
            }

            var problem = _problemRepository.GetProblem(probId);

            if (problem == null)
            {
                return NotFound("Problem not found.");
            }

            if (imageFile.ContentType == "image/jpeg" || imageFile.ContentType == "image/jpg")
            {
                var image = new Image
                {
                    Problem = problem,
                };

                if (!_imageRepository.CreateImage(image, imageFile))
                {
                    ModelState.AddModelError("", "Something went wrong while saving.");
                    return StatusCode(500, ModelState);
                }

                return NoContent();
            }
            else
            {
                return BadRequest("Invalid image format. Only JPG images are allowed.");
            }
        }

        [HttpDelete("{imageId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteImage(int imageId)
        {
            if (!_imageRepository.ImageExists(imageId))
                return NotFound();

            var imageToDelete = _imageRepository.GetImage(imageId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_imageRepository.DeleteImage(imageToDelete));
            {
                ModelState.AddModelError("", "Something went wrong deleting image");
            }

            return NoContent();
        }
    }
}
