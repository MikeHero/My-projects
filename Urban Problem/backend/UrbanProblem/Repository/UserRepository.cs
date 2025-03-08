using UrbanProblem.Data;
using UrbanProblem.Interfaces;
using UrbanProblem.Models;

namespace UrbanProblem.Repository
{
    public class UserRepository : IUserRepository
    {
        private readonly DataContext _context;

        public UserRepository(DataContext context)
        {
            _context = context;
        }
        public bool CreateUser(User user)
        {
            _context.Add(user);
            return Save();
        }

        public bool UserExists(string email)
        {
            return _context.Users.Any(c => c.Email == email);
        }
        public bool Save()
        {
            var saved = _context.SaveChanges();
            return (saved > 0) ? true : false;
        }

        public ICollection<User> GetUsers()
        {
            return _context.Users.ToList();
        }

        public User GetUser(string email)
        {
            return _context.Users.FirstOrDefault(u => u.Email == email);
        }

        public User GetUser(int id)
        {
            return _context.Users.FirstOrDefault(u => u.Id == id);
        }
    }
}
