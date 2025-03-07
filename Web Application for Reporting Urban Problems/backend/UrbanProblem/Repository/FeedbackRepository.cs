using Microsoft.EntityFrameworkCore;
using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class FeedbackRepository : IFeedbackRepository
    {
        private readonly DataContext _context;

        public FeedbackRepository(DataContext contex)
        {
            _context = contex;
        }
        public bool CreateFeedback(Feedback feedback)
        {
            _context.Add(feedback);
            return Save();
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0) ? true : false;
        }
    }
}
