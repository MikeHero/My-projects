using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using UrbanProblem.Dto;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;
using UrbanProblem.Repository;

namespace UrbanProblem.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ReviewController : Controller
    {
        private readonly IReviewRepository _reviewRepository;
        private readonly IProblemRepository _problemRepository;
        private readonly IReporterRepository _reporterRepository;
        private readonly IMapper _mapper;

        public ReviewController(IReviewRepository reviewRepository, 
            IProblemRepository problemRepository, 
            IReporterRepository reporterRepository,
            IMapper mapper)
        {
            _reviewRepository = reviewRepository;
            _problemRepository = problemRepository;
            _reporterRepository = reporterRepository;
            _mapper = mapper;
        }
        
        [HttpGet]
        [ProducesResponseType(200, Type = typeof(IEnumerable<Review>))]
        public IActionResult GetReviews()
        {
            var reviews = _mapper.Map<List<ReviewDto>>(_reviewRepository.GetReviews());

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(reviews);
        }

        [HttpGet("{reviewId}")]
        [ProducesResponseType(200, Type = typeof(Review))]
        [ProducesResponseType(400)]
        public IActionResult GetReview(int reviewId)
        {
            if (!_reviewRepository.ReviewExists(reviewId))
                return NotFound();

            var review = _mapper.Map<ReviewDto>(_reviewRepository.GetReview(reviewId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(review);
        }

        [HttpGet("problem/{probId}")]
        [ProducesResponseType(200, Type = typeof(Review))]
        [ProducesResponseType(400)]
        public IActionResult GetReviewsForAProblem(int probId)
        {
            var reviews = _mapper.Map<List<ReviewDto>>(
                _reviewRepository.GetReviewsOfAProblem(probId));

            if (!ModelState.IsValid)
                return BadRequest();
            
            return Ok(reviews);
        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateReview([FromQuery] int reporterId,
            [FromQuery]int probId, [FromBody] ReviewDto reviewCreate)
        {
            if (reviewCreate == null)
                return BadRequest(ModelState);

            var reviews = _reviewRepository.GetReviews()
                .Where(c => c.Title.Trim().ToUpper() == reviewCreate.Title.TrimEnd().ToUpper())
                .FirstOrDefault();

            if (reviews != null)
            {
                ModelState.AddModelError("", "Review already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var reviewMap = _mapper.Map<Review>(reviewCreate);

            reviewMap.Problem = _problemRepository.GetProblem(probId);
            reviewMap.Reporter = _reporterRepository.GetReporter(reporterId);

            if (!_reviewRepository.CreateReview(reviewMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");
        }

        [HttpPut("{reviewId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult UpdateReporter(int reviewId, [FromBody] ReviewDto updateReview)
        {
            if (updateReview == null)
                return BadRequest(ModelState);

            if (reviewId != updateReview.Id)
                return BadRequest(ModelState);

            if (!_reviewRepository.ReviewExists(reviewId))
                return NotFound();

            if (!ModelState.IsValid)
                return BadRequest();

            var reviewMap = _mapper.Map<Review>(updateReview);

            if (!_reviewRepository.UpdateReview(reviewMap))
            {
                ModelState.AddModelError("", "Something went wrong updating review");
                return StatusCode(500, ModelState);
            }

            return NoContent();
        }

        [HttpDelete("{reviewId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteReview(int reviewId)
        {
            if (!_reviewRepository.ReviewExists(reviewId))
                return NotFound();

            var reviewToDelete = _reviewRepository.GetReview(reviewId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_reviewRepository.DeleteReview(reviewToDelete))
            {
                ModelState.AddModelError("", "Something went wrong deleting review");
            }

            return NoContent();
        }
    }
}
