using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IResponsibleRepository
    {
        ICollection<Responsible> GetResponsibles();
        Responsible GetResponsible(int responsibleId);
        ICollection<Responsible> GetResponsibleOfAProblem(int probId);
        ICollection<Problem> GetProblemByResponsible(int responsibleId);
        bool ResponsibleExists(int responsibleId);
        bool CreateResponsible(Responsible responsible);
        bool UpdateResponsible(Responsible responsible);
        bool DeleteResponsible(Responsible responsible);
        bool Save();

    }
}
