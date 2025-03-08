using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class ProblemRepository : IProblemRepository
    {
        private readonly DataContext _context;

        public ProblemRepository(DataContext context)
        {
            _context = context;
        }

        public bool CreateProblem(int responsibleId, int categoryId, Problem problem)
        {
            var problemResponsibleEntity = _context.Responsibles
                .Where(a => a.Id == responsibleId).FirstOrDefault();

            var category = _context.Categories
                .Where(a => a.Id == categoryId).FirstOrDefault();

            var problemResponsible = new ProblemResponsible()
            {
                Responsible = problemResponsibleEntity,
                Problem = problem,
            };

            _context.Add(problemResponsible);

            var problemCategory = new ProblemCategory()
            {
                Category = category,
                Problem = problem,
            };

            _context.Add(problemCategory);
            _context.Add(problem);

            return Save();
        }

        public bool DeleteProblem(Problem problem)
        {
            _context.Remove(problem);
            return Save();
        }

        public Problem GetProblem(int id)
        {
            return _context.Problems.Where(p => p.Id == id).FirstOrDefault();
        }

        public Problem GetProblem(string title)
        {
            return _context.Problems.Where(p => p.Title == title).FirstOrDefault();
        }

        public decimal GetProblemRating(int probId)
        {
            var review = _context.Reviews.Where(p => p.Problem.Id == probId);
            
            if (review.Count() <= 0)
                return 0;

            return ((decimal)review.Sum(r => r.Rating) / review.Count());
        }

        public ICollection<Problem> GetProblems()
        {
            return _context.Problems.OrderBy(p => p.Id).ToList();
        }

        public bool ProblemExists(int probId)
        {
            return _context.Problems.Any(p => p.Id == probId);
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0)? true : false ;
        }

        public bool UpdateProblem(int responsibleId, int categoryId, Problem Problem)
        {
            _context.Update(Problem);
            return Save();
        }
    }
}
