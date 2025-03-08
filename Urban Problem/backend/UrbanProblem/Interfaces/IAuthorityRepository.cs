using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IAuthorityRepository
    {
        ICollection<Authority> GetAuthorities();
        Authority GetAuthority(int id);
        Authority GetAuthorityByResponsible(int responsibleId);
        ICollection<Responsible> GetResponsiblesFromAnAuthority(int authorityId);
        bool AuthorityExists(int id);
        bool CreateAuthority(Authority authority);
        bool UpdateAuthority(Authority authority);
        bool DeleteAuthority(Authority authority);
        bool Save();
    }
}
