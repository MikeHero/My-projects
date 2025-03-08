using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IProblemRepository
    {
        ICollection<Problem> GetProblems();
        Problem GetProblem(int id);
        Problem GetProblem(string title);
        decimal GetProblemRating(int probId);
        bool ProblemExists(int probId);
        bool CreateProblem(int responsibleId, int categoryId, Problem Problem);
        bool UpdateProblem(int responsibleId, int categoryId, Problem Problem);
        bool DeleteProblem(Problem problem);
        bool Save();


    }
}
