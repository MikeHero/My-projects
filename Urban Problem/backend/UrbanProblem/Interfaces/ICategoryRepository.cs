using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface ICategoryRepository
    {
        ICollection<Category> GetCategories();
        Category GetCategory(int id);
        ICollection<Problem> getProblemByCategory(int categoryId);
        bool CategoryExists(int id);
        bool CreateCategory(Category category);
        bool UpdateCategory(Category category);
        bool DeleteCategory(Category category);
        bool Save();
    }
}
