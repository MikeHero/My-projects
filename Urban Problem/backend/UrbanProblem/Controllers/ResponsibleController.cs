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
    public class ResponsibleController : Controller
    {
        private readonly IResponsibleRepository _responsibleRepository;
        private readonly IMapper _mapper;
        private readonly IAuthorityRepository _authorityRepository;

        public ResponsibleController(IResponsibleRepository responsibleRepository, IMapper mapper
            , IAuthorityRepository authorityRepository)
        {
            _responsibleRepository = responsibleRepository;
            _mapper = mapper;
            _authorityRepository = authorityRepository;
        }

        [HttpGet]
        [ProducesResponseType(200, Type = typeof(IEnumerable<Responsible>))]
        public IActionResult GetResponsibles()
        {
            var responsibles = _mapper.Map<List<ResponsibleDto>>(_responsibleRepository.GetResponsibles());

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(responsibles);
        }

        [HttpGet("{ResponsibleId}")]
        [ProducesResponseType(200, Type = typeof(Responsible))]
        [ProducesResponseType(400)]
        public IActionResult GetResponsible(int ResponsibleId)
        {
            if (!_responsibleRepository.ResponsibleExists(ResponsibleId))
                return NotFound();

            var responsible = _mapper.Map<ResponsibleDto>(_responsibleRepository.GetResponsible(ResponsibleId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(responsible);
        }

        [HttpGet("{responsibleId}/problem")]
        [ProducesResponseType(200, Type = typeof(Responsible))]
        [ProducesResponseType(400)]
        public IActionResult GetProblemByResponsible(int responsibleId)
        {
            if (!_responsibleRepository.ResponsibleExists(responsibleId))
                return NotFound();

            var responsible = _mapper.Map<List<ProblemDto>>(
                _responsibleRepository.GetProblemByResponsible(responsibleId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(responsible);
        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateResponsible([FromQuery] int authorityId, [FromBody] ResponsibleDto responsibleCreate)
        {
            if (responsibleCreate == null)
                return BadRequest(ModelState);

            var responsibles = _responsibleRepository.GetResponsibles().
                Where(r => r.Name.Trim().ToUpper() == responsibleCreate.Name.TrimEnd().ToUpper())
                .FirstOrDefault();

            if (responsibles != null)
            {
                ModelState.AddModelError("", "Responsible already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var responsibleMap = _mapper.Map<Responsible>(responsibleCreate);

            responsibleMap.Authority = _authorityRepository.GetAuthority(authorityId);

            if (!_responsibleRepository.CreateResponsible(responsibleMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");
        }

        [HttpPut("{responsibleId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult UpdateResponsible(int responsibleId, 
            [FromBody] ResponsibleDto updatedResponsible)
        {
            if (updatedResponsible == null)
                return BadRequest(ModelState);

            if (responsibleId != updatedResponsible.Id)
                return BadRequest(ModelState);

            if (!_responsibleRepository.ResponsibleExists(responsibleId))
                return NotFound();

            if (!ModelState.IsValid)
                return BadRequest();

            var responsibleMap = _mapper.Map<Responsible>(updatedResponsible);

            if (!_responsibleRepository.UpdateResponsible(responsibleMap))
            {
                ModelState.AddModelError("", "Something went wrong updating responsible");
                return StatusCode(500, ModelState);
            }

            return NoContent();
        }

        [HttpDelete("{responsibleId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteResponsible(int responsibleId)
        {
            if (!_responsibleRepository.ResponsibleExists(responsibleId))
                return NotFound();

            var responsibleToDelete = _responsibleRepository.GetResponsible(responsibleId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_responsibleRepository.DeleteResponsible(responsibleToDelete))
            {
                ModelState.AddModelError("", "Something went wrong deleting responsible");
            }

            return NoContent();
        }


    }
}
