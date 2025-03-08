using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IFeedbackRepository
    {
        bool CreateFeedback(Feedback feedback);
        bool Save();
    }
}
