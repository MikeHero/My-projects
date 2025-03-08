using AutoMapper;
using Microsoft.EntityFrameworkCore;
using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class ReporterRepository : IReporterRepository
    {
        private readonly DataContext _context;
        private readonly IMapper _mapper;

        public ReporterRepository(DataContext context, IMapper mapper)
        {
            _context = context;
            _mapper = mapper;
        }

        public bool CreateReporter(Reporter reporter)
        {
            _context.Add(reporter);
            return Save();
        }

        public bool DeleteReporter(Reporter reporter)
        {
            _context.Remove(reporter);
            return Save();
        }

        public Reporter GetReporter(int reporterId)
        {
            return _context.Reporters.Where(r => r.Id == reporterId).
                Include(e => e.Reviews).FirstOrDefault();
        }

        public ICollection<Reporter> GetReporters()
        {
            return _context.Reporters.ToList();
        }

        public ICollection<Review> GetReviewsByReporter(int reporterId)
        {
            return _context.Reviews.Where(r => r.Reporter.Id == reporterId).ToList();
        }

        public bool ReporterExists(int reporterId)
        {
            return _context.Reporters.Any(r => r.Id == reporterId);
        }

        public bool Save()
        {
            var saved = _context.SaveChanges();
            return saved > 0 ? true : false;
        }

        public bool UpdateReporter(Reporter reporter)
        {
            _context.Update(reporter);
            return Save();
        }
    }
}
