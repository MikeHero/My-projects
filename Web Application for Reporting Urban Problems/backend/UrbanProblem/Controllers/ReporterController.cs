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
    public class ReporterController : Controller
    {
        private readonly IReporterRepository _reporterRepository;
        private readonly IMapper _mapper;

        public ReporterController(IReporterRepository reporterRepository, IMapper mapper)
        {
            _reporterRepository = reporterRepository;
            _mapper = mapper;
        }

        [HttpGet]
        [ProducesResponseType(200, Type = typeof(IEnumerable<Reporter>))]
        public IActionResult GetReporters()
        {
            var reporters = _mapper.Map<List<ReporterDto>>
                (_reporterRepository.GetReporters());

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(reporters);
        }

        [HttpGet("{reporterId}")]
        [ProducesResponseType(200, Type = typeof(Reporter))]
        [ProducesResponseType(400)]
        public IActionResult GetProblem(int reporterId)
        {
            if (!_reporterRepository.ReporterExists(reporterId))
                return NotFound();

            var problem = _mapper.Map<ReporterDto>(_reporterRepository.GetReporter(reporterId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(problem);
        }

        [HttpGet("{reporterId}/reviews")]
        public IActionResult GetReviewsByAReporter(int reporterId)
        {
            if (!_reporterRepository.ReporterExists(reporterId))
                return NotFound();

            var reviews = _mapper.Map<List<ReviewDto>>(
                _reporterRepository.GetReviewsByReporter(reporterId));

            if (!ModelState.IsValid)
                return BadRequest();

            return Ok(reviews);
        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateReporter([FromBody] ReporterDto reporterCreate)
        {
            if (reporterCreate == null)
                return BadRequest(ModelState);

            var reporter = _reporterRepository.GetReporters().
                Where(c => c.LastName.Trim().ToUpper() == reporterCreate.LastName.TrimEnd().ToUpper())
                .FirstOrDefault();
            
            if (reporter != null)
            {
                ModelState.AddModelError("", "Reporter already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var reporterMap = _mapper.Map<Reporter>(reporterCreate);

            if (!_reporterRepository.CreateReporter(reporterMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");
        }

        [HttpPut("{reporterId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult UpdateReporter(int reporterId,
        [FromBody] ReporterDto updateReporter)
        {
            if (updateReporter == null)
                return BadRequest(ModelState);

            if (reporterId != updateReporter.Id)
                return BadRequest(ModelState);

            if (!_reporterRepository.ReporterExists(reporterId))
                return NotFound();

            if (!ModelState.IsValid)
                return BadRequest();

            var reporterMap = _mapper.Map<Reporter>(updateReporter);

            if (!_reporterRepository.UpdateReporter(reporterMap))
            {
                ModelState.AddModelError("", "Something went wrong updating reporter");
                return StatusCode(500, ModelState);
            }

            return NoContent();
        }

        [HttpDelete("{reporterId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteReview(int reporterId)
        {
            if (!_reporterRepository.ReporterExists(reporterId))
                return NotFound();

            var reporterToDelete = _reporterRepository.GetReporter(reporterId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_reporterRepository.DeleteReporter(reporterToDelete))
            {
                ModelState.AddModelError("", "Something went wrong deleting reporter");
            }

            return NoContent();
        }
    }
}
