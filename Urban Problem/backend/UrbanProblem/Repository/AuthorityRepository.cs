using AutoMapper;
using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class AuthorityRepository : IAuthorityRepository
    {
        private readonly DataContext _context;
        private readonly IMapper _mapper;

        public AuthorityRepository(DataContext context, IMapper mapper)
        {
            _context = context;
            _mapper = mapper;
        }
        public bool AuthorityExists(int id)
        {
            return _context.Authorities.Any(a => a.Id == id);
        }

        public bool CreateAuthority(Authority authority)
        {
            _context.Add(authority);
            return Save();
        }

        public bool DeleteAuthority(Authority authority)
        {
            _context.Remove(authority);
            return Save();
        }

        public ICollection<Authority> GetAuthorities()
        {
            return _context.Authorities.ToList();
        }

        public Authority GetAuthority(int id)
        {
            return _context.Authorities.Where(a => a.Id == id).FirstOrDefault();
        }

        public Authority GetAuthorityByResponsible(int responsibleId)
        {
            return _context.Responsibles.Where(r => r.Id == responsibleId).Select(a => a.Authority).FirstOrDefault();
        }

        public ICollection<Responsible> GetResponsiblesFromAnAuthority(int authorityId)
        {
            return _context.Responsibles.Where(a => a.Authority.Id == authorityId).ToList();
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0) ? true : false;
        }

        public bool UpdateAuthority(Authority authority)
        {
            _context.Update(authority);
            return Save();
        }
    }
}
