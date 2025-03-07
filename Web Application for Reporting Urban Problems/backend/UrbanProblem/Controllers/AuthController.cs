using Microsoft.AspNetCore.Mvc;
using UrbanProblem.Dto;
using UrbanProblem.Helper;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;
using UrbanProblem.Repository;

namespace UrbanProblem.Controllers
{
    [Route("/api")]
    [ApiController]
    public class AuthController : Controller
    {
        private readonly IUserRepository _userRepository;
        private readonly JwtService _jwtService;

        public AuthController(IUserRepository userRepository, JwtService jwtService)
        {
            _userRepository = userRepository;
            _jwtService = jwtService;
        }

        [HttpPost("Register")]
        public IActionResult Register(RegisterDto dto)
        {
            if (dto == null)
                return BadRequest(ModelState);

            var user = _userRepository.GetUsers().
                Where(c => c.Email.Trim().ToUpper() == dto.Email.TrimEnd().ToUpper())
                .FirstOrDefault();

            if (user != null)
            {
                ModelState.AddModelError("", "User already exists");
                return StatusCode(422, ModelState);
            }

            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var userMap = new User
            {
                Name = dto.Name,
                Email = dto.Email,
                Password = BCrypt.Net.BCrypt.HashPassword(dto.Password)
            };

            if (!_userRepository.CreateUser(userMap))
            {
                ModelState.AddModelError("", "Something went wrong while savin");
                return StatusCode(500, ModelState);
            }

            return Ok("Successfully created");

        }

        [HttpPost("Login")]
        public IActionResult Login(LoginDto dto)
        {
            if (dto == null)
                return BadRequest(ModelState);

            var user = _userRepository.GetUser(dto.Email);

            if (user == null)
                return BadRequest(new { message = "Invalid Credentials" });

            if( !BCrypt.Net.BCrypt.Verify(dto.Password, user.Password))
                return BadRequest(new { message = "Invalid Credentials" });

            var jwt = _jwtService.Generate(user.Id);

            Response.Cookies.Append("jwt", jwt, new CookieOptions
            {
                HttpOnly = true
            });

            return Ok(new
            {
                jwt
            }); ;

        }

        [HttpGet("User")]
        public IActionResult User()
        {
            try
            {
                var jwt = Request.Cookies["jwt"];
                if (string.IsNullOrEmpty(jwt))
                {
                    return Unauthorized(new { message = "JWT token is missing" });
                }

                var token = _jwtService.Verify(jwt);
                if (token == null)
                {
                    return Unauthorized(new { message = "JWT token verification failed" });
                }

                int userId;
                if (!int.TryParse(token.Issuer, out userId))
                {
                    return Unauthorized(new { message = "Invalid token issuer" });
                }

                var user = _userRepository.GetUser(userId);
                if (user == null)
                {
                    return NotFound(new { message = "User not found" });
                }

                return Ok(user);
            }
            catch (Exception ex)
            {
                // More detailed logging for the exception
                Console.WriteLine(ex.ToString());
                return Unauthorized(new { message = "An error occurred", details = ex.Message });
            }
        }

        /*[HttpGet("User")]
        public IActionResult User()
        {
            try
            {
                var jwt = Request.Cookies["jwt"];
                var token = _jwtService.Verify(jwt);

                int userId = int.Parse(token.Issuer);

                var user = _userRepository.GetUser(userId);
                return Ok(user);
            }
            catch(Exception ex)
            {
                return Unauthorized();
            }
        }*/

        [HttpPost("Logout")]
        public IActionResult Logout()
        {
            Response.Cookies.Delete("jwt");
            return Ok(new
            {
                message = "success"
            });
        }


    }
}
