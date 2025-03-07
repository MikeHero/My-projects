using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IReporterRepository
    {
        ICollection<Reporter> GetReporters();
        Reporter GetReporter(int reporterId);
        ICollection<Review> GetReviewsByReporter(int reporterId);
        bool ReporterExists(int reporterId);
        bool CreateReporter(Reporter reporter);
        bool UpdateReporter(Reporter reporter);
        bool DeleteReporter(Reporter reporter);
        bool Save();
    }
}
