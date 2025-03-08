using Microsoft.EntityFrameworkCore;
using UrbanProblem.Models;

namespace UrbanProblem.Data
{
    public class DataContext : DbContext
    {
        public DataContext(DbContextOptions<DataContext> options) : base(options)
        {

        }

        public DbSet<Category> Categories { get; set; }
        public DbSet<Authority> Authorities { get; set; }
        public DbSet<Responsible> Responsibles { get; set; }
        public DbSet<Problem> Problems { get; set; }
        public DbSet<ProblemResponsible> ProblemResponsibles { get; set; }
        public DbSet<ProblemCategory> ProblemCategories { get; set; }
        public DbSet<Review> Reviews { get; set; }
        public DbSet<Reporter> Reporters { get; set; }
        public DbSet<Feedback> Feedbacks { get; set; }
        public DbSet<User> Users { get; set; }

        public DbSet<Image> Images { get; set; }

        public DbSet<Formular> Formular { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>(entity =>
            {
                entity.HasIndex(e => e.Email).IsUnique();
            });
            
            modelBuilder.Entity<ProblemCategory>()
              .HasKey(pc => new { pc.ProblemId, pc.CategoryId });
            modelBuilder.Entity<ProblemCategory>()
                .HasOne(p => p.Problem)
                .WithMany(pc => pc.ProblemCategories)
                .HasForeignKey(p => p.ProblemId);
            modelBuilder.Entity<ProblemCategory>()
               .HasOne(p => p.Category)
               .WithMany(pc => pc.ProblemCategories)
               .HasForeignKey(c => c.CategoryId);

            modelBuilder.Entity<ProblemResponsible>()
                .HasKey(pr => new { pr.ProblemId, pr.ResponsibleId });
            modelBuilder.Entity<ProblemResponsible>()
                .HasOne(p => p.Problem)
                .WithMany(pc => pc.ProblemResponsibles)
                .HasForeignKey(p => p.ProblemId);
            modelBuilder.Entity<ProblemResponsible>()
               .HasOne(p => p.Responsible)
               .WithMany(pc => pc.ProblemResponsibles)
               .HasForeignKey(c => c.ResponsibleId);
        }

    }
}
