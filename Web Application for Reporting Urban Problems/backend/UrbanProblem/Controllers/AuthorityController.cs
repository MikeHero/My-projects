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
    public class AuthorityController : Controller
    {
        private readonly IAuthorityRepository _authorityRepository;
        private readonly IMapper _mapper;

        public AuthorityController(IAuthorityRepository authorityRepository, IMapper mapper)
        {
            _authorityRepository = authorityRepository;
            _mapper = mapper;
        }

        [HttpGet]
        [ProducesResponseType(200, Type = typeof(IEnumerable<Authority>))]
        public IActionResult GetAuthorities()
        {
            var authorities = _mapper.Map<List<AuthorityDto>>(_authorityRepository.GetAuthorities());

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(authorities);
        }

        [HttpGet("authorityId")]
        [ProducesResponseType(200, Type = typeof(Authority))]
        [ProducesResponseType(400)]
        public IActionResult GetProblem(int authorityId)
        {
            if (!_authorityRepository.AuthorityExists(authorityId))
                return NotFound();

            var authority = _mapper.Map<AuthorityDto>(_authorityRepository.GetAuthority(authorityId));

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            return Ok(authority);
        }

        [HttpGet("/responsibles/{responsibleId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(200, Type = typeof(Authority))]
        public IActionResult GetAuthorityOfAResponible(int responsibleId) 
        {
            var authority = _mapper.Map<AuthorityDto>(
                _authorityRepository.GetAuthorityByResponsible(responsibleId));

            if (!ModelState.IsValid)
                return BadRequest();
            
            return Ok(authority);

        }

        [HttpPost]
        [ProducesResponseType(204)]
        [ProducesResponseType(400)]
        public IActionResult CreateAuthority([FromBody] AuthorityDto authorityCreate)
        {
            if (authorityCreate == null)
                return BadRequest(ModelState);

            var authority = _authorityRepository.GetAuthorities().
                Where(c => c.Name.Trim().ToUpper() == authorityCreate.Name.TrimEnd().ToUpper())
                .FirstOrDefault();

            if (authority != null)
            {
                ModelState.AddModelError("", "Authority already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var authorityMap = _mapper.Map<Authority>(authorityCreate);

            if (!_authorityRepository.CreateAuthority(authorityMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");
        }

        [HttpPut("{authorityId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult UpdateCategory(int authorityId, [FromBody] AuthorityDto updatedAuthority)
        {
            if (updatedAuthority == null)
                return BadRequest(ModelState);

            if (authorityId != updatedAuthority.Id)
                return BadRequest(ModelState);

            if (! _authorityRepository.AuthorityExists(authorityId))
                return NotFound();

            if (!ModelState.IsValid)
                return BadRequest();

            var authorityMap = _mapper.Map<Authority>(updatedAuthority);

            if (!_authorityRepository.UpdateAuthority(authorityMap))
            {
                ModelState.AddModelError("", "Something went wrong updating authority");
                return StatusCode(500, ModelState);
            }

            return NoContent();
        }

        [HttpDelete("{authorityId}")]
        [ProducesResponseType(400)]
        [ProducesResponseType(204)]
        [ProducesResponseType(404)]
        public IActionResult DeleteAuthority(int authorityId)
        {
            if (!_authorityRepository.AuthorityExists(authorityId))
                return NotFound();

            var authorityToDelete = _authorityRepository.GetAuthority(authorityId);

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            if (!_authorityRepository.DeleteAuthority(authorityToDelete))
            {
                ModelState.AddModelError("", "Something went wrong deleting category");
            }

            return NoContent();
        }
    }
}
