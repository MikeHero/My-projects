using Microsoft.AspNetCore.Mvc;
using UrbanProblem.Dto;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;
using UrbanProblem.Repository;

namespace UrbanProblem.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class FeedbackController : Controller
    {
        private readonly IFeedbackRepository _feedbackRepository;

        public FeedbackController(IFeedbackRepository feedbackRepository)
        {
            _feedbackRepository = feedbackRepository;
        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateFeedback([FromBody] Feedback feedbackCreate)
        {
            if (feedbackCreate == null)
                return BadRequest(ModelState);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_feedbackRepository.CreateFeedback(feedbackCreate))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");
        }
    }
}
