using Microsoft.EntityFrameworkCore;
using UrbanProblem.Models;

namespace UrbanProblem.Interfaces
{
    public interface IUserRepository
    {
        ICollection<User> GetUsers();
        User GetUser(string email);
        User GetUser(int id);
        bool CreateUser(User user);
        public bool UserExists(string email);
        public bool Save();
    }
}
