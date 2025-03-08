using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using UrbanProblem.Data;
using UrbanProblem.Dto;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;
using UrbanProblem.Repository;

namespace UrbanProblem.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ProblemController : Controller
    {
        private readonly IProblemRepository _problemRepository;
        private readonly IReviewRepository _reviewRepository;
        private readonly IMapper _mapper;
        private readonly DataContext _context;

        public ProblemController(IProblemRepository problemRepository,  
            IReviewRepository reviewRepository,
            IMapper mapper,
            DataContext context)
        {
            _problemRepository = problemRepository;
            _reviewRepository = reviewRepository;
            _mapper = mapper;
            _context = context;
        }

        [HttpGet]
        [ProducesResponseType(200, Type = typeof(IEnumerable<Problem>) )]
        public IActionResult GetProblems()
        {
            var problems = _mapper.Map<List<ProblemDto>>(_problemRepository.GetProblems());

            if(!ModelState.IsValid)
                return BadRequest(ModelState);
            
            return Ok(problems);
        }

        [HttpGet("{probId}")]
        [ProducesResponseType(200, Type = typeof(Problem))]
        [ProducesResponseType(400)]
        public IActionResult GetProblem(int probId)
        {
            if (!_problemRepository.ProblemExists(probId))
                return NotFound();

            var problem = _mapper.Map<ProblemDto>(_problemRepository.GetProblem(probId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);
            
            return Ok(problem);
        }

        [HttpGet("{probId}/rating")]
        [ProducesResponseType(200, Type = typeof(decimal))]
        [ProducesResponseType(400)]
        public IActionResult GetProblemRating(int probId)
        {
            if (!_problemRepository.ProblemExists(probId))
                return NotFound();

            var rating = _problemRepository.GetProblemRating(probId);

            if (!ModelState.IsValid)
                return BadRequest();
            
            return Ok(rating);
        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public async Task<IActionResult> CreateProblem(
            [FromQuery] int responsibleId,
            [FromQuery] int catId,
            [FromForm] ProblemDto problemCreate,
            [FromForm] List<IFormFile> images)
        {
            if (problemCreate == null)
                return BadRequest(ModelState);

            var problems = _problemRepository.GetProblems().
                Where(c => c.Title.Trim().ToUpper() == problemCreate.Title.TrimEnd().ToUpper())
                .FirstOrDefault();

            if (problems != null)
            {
                ModelState.AddModelError("", "Problem already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var problemMap = _mapper.Map<Problem>(problemCreate);

            if (!_problemRepository.CreateProblem(responsibleId, catId, problemMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }


            if (images != null && images.Any())
            {
                foreach (var image in images)
                {
                    var imageFileName = $"Photo_{Guid.NewGuid()}.jpg"; // Unique file name
                    var imagePath = Path.Combine("wwwroot/images", imageFileName); // Assuming you save images to wwwroot/images

                    using (var stream = new FileStream(imagePath, FileMode.Create))
                    {
                        await image.CopyToAsync(stream);
                    }

                    var imageEntity = new Image
                    {
                        Problem = problemMap,
                        ImageData = System.IO.File.ReadAllBytes(imagePath),
                        ImageURL = $"/images/{imageFileName}" // Relative URL to access the image
                    };

                    _context.Images.Add(imageEntity);
                }
                _context.SaveChanges();
            }

            return Ok(new { message = "Successfully created" });
        }

        [HttpPut("{probId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult UpdateProblem(int probId, 
        [FromQuery] int responsibleId, [FromQuery] int catId,
        [FromBody] ProblemDto updatedProblem)
        {
            if (updatedProblem == null)
                return BadRequest(ModelState);

            if (probId != updatedProblem.Id)
                return BadRequest(ModelState);

            if (!_problemRepository.ProblemExists(probId))
                return NotFound();

            if (!ModelState.IsValid)
                return BadRequest();

            var problemMap = _mapper.Map<Problem>(updatedProblem);

            if (!_problemRepository.UpdateProblem(responsibleId, catId, problemMap))
            {
                ModelState.AddModelError("", "Something went wrong updating problem");
                return StatusCode(500, ModelState);
            }

            return NoContent();
        }

        [HttpDelete("{probId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteProblem(int probId)
        {
            if (!_problemRepository.ProblemExists(probId))
                return NotFound();

            var reviewsToDelete = _reviewRepository.GetReviewsOfAProblem(probId);

            var problemToDelete = _problemRepository.GetProblem(probId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (_reviewRepository.DeleteReviews(reviewsToDelete.ToList()))
            {
                ModelState.AddModelError("", "Something went wrong while deleting reviews to the problem");
            }

            if (! _problemRepository.DeleteProblem(problemToDelete))
            {
                ModelState.AddModelError("", "Something went wrong deleting problem");
            }

            return NoContent();
        }

    }


}
