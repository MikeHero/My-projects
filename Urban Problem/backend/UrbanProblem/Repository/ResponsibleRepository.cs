using AutoMapper;
using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class ResponsibleRepository : IResponsibleRepository
    {
        private readonly DataContext _context;
        private readonly IMapper _mapper;

        public ResponsibleRepository(DataContext context, IMapper mapper)
        {  
            _context = context;
            _mapper = mapper;
        }

        public bool CreateResponsible(Responsible responsible)
        {
            _context.Add(responsible);
            return Save();
        }

        public bool DeleteResponsible(Responsible responsible)
        {
            _context.Remove(responsible);
            return Save();
        }

        public ICollection<Problem> GetProblemByResponsible(int responsibleId)
        {
            return _context.ProblemResponsibles.Where(p => p.Responsible.Id == responsibleId).Select(p => p.Problem).ToList();
        }

        public Responsible GetResponsible(int responsibleId)
        {
            return _context.Responsibles.Where(r => r.Id == responsibleId).FirstOrDefault();
        }

        public ICollection<Responsible> GetResponsibleOfAProblem(int probId)
        {
            return _context.ProblemResponsibles.Where(p => p.Problem.Id == probId).Select(r => r.Responsible).ToList();
        }

        public ICollection<Responsible> GetResponsibles()
        {
            return _context.Responsibles.ToList();
        }

        public bool ResponsibleExists(int responsibleId)
        {
            return _context.Responsibles.Any(r => r.Id == responsibleId);
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0) ? true : false;
        }

        public bool UpdateResponsible(Responsible responsible)
        {
            _context.Update(responsible);
            return Save();
        }
    }
}
