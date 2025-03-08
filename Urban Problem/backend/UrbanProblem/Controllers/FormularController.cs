using Microsoft.AspNetCore.Mvc;
using System.Reflection.Metadata;
using UrbanProblem.Data;
using UrbanProblem.Dto;
using UrbanProblem.Models;
using System.IO;
using System.Text;
using Microsoft.EntityFrameworkCore;

namespace UrbanProblem.Controllers
{

    



    [Route("api/[controller]")]
    [ApiController]
    public class FormularController : Controller
    {   
        private readonly DataContext _context;

        public FormularController(DataContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> SubmitForm([FromBody] FormularDto model)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            var formular = new Formular
            {
                Nume = model.Nume, // Asignează noul câmp
                Judet = model.Judet,
                Localitate = model.Localitate,
                CNP = model.CNP,
                SalariuBrut = model.SalariuBrut,
                Email = model.Email,
                NumarTelefon = model.NumarTelefon,
                Impozit = model.SalariuBrut * 0.18,
                IbanBeneficiar = model.IbanBeneficiar
            };

            _context.Formular.Add(formular);
            await _context.SaveChangesAsync();

            // Generare conținut .txt cu câmpul Nume
            var content = new StringBuilder();
            content.AppendLine($"Nume: {formular.Nume}"); 
            content.AppendLine($"Judet: {formular.Judet}");
            content.AppendLine($"Localitate: {formular.Localitate}");
            content.AppendLine($"CNP: {formular.CNP}");
            content.AppendLine($"Salariu Brut: {formular.SalariuBrut}");
            content.AppendLine($"Email: {formular.Email}");
            content.AppendLine($"Numar Telefon: {formular.NumarTelefon}");
            content.AppendLine($"Impozit: {formular.Impozit}");
            content.AppendLine($"Iban Beneficiar: {formular.IbanBeneficiar}");

            var fileContent = Encoding.UTF8.GetBytes(content.ToString());

            return File(fileContent, "text/plain", "formular.txt");
        }

        /*
        [HttpPost]
        public async Task<IActionResult> SubmitForm([FromBody] FormularDto model)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            // Salvează datele în baza de date
            var formular = new Formular
            {
                Judet = model.Judet,
                Localitate = model.Localitate,
                CNP = model.CNP,
                SalariuBrut = model.SalariuBrut,
                Email = model.Email,
                NumarTelefon = model.NumarTelefon,
                Impozit = model.SalariuBrut * 0.18
            };

            _context.Formular.Add(formular);
            await _context.SaveChangesAsync();

            // Generare PDF sau TXT (cod pentru generare PDF mai jos)

            return Ok(new { Message = "Formular trimis cu succes" });
        }
        */

    }
}
