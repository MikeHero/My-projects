using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using System.Text.Json.Serialization;
using UrbanProblem.Data;
using UrbanProblem.Helper;
using UrbanProblem.Interfaces;
using UrbanProblem.Repository;

namespace UrbanProblem
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var myAllowSpecificOrigins = "_myAllowSpecificOrigins";

            // Add services to the container.

            builder.Services.AddControllers();
            builder.Services.AddTransient<Seed>();

            builder.Services.AddControllers().AddJsonOptions(x =>
                             x.JsonSerializerOptions.ReferenceHandler = ReferenceHandler.IgnoreCycles);

            builder.Services.AddAutoMapper(AppDomain.CurrentDomain.GetAssemblies());
            builder.Services.AddScoped<IProblemRepository, ProblemRepository>();
            builder.Services.AddScoped<ICategoryRepository, CategoryRepository>();
            builder.Services.AddScoped<IAuthorityRepository, AuthorityRepository>();
            builder.Services.AddScoped<IResponsibleRepository, ResponsibleRepository>();
            builder.Services.AddScoped<IReviewRepository,  ReviewRepository>();
            builder.Services.AddScoped<IReporterRepository, ReporterRepository>();
            builder.Services.AddScoped<IFeedbackRepository, FeedbackRepository>();
            builder.Services.AddScoped<IUserRepository, UserRepository>();
            builder.Services.AddScoped<IImageRepository, ImageRepository>();

            // builder.Services.AddCors(); DECOMENTEAZA MA ????

            builder.Services.AddScoped<JwtService>();

            // Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
            builder.Services.AddEndpointsApiExplorer();
            builder.Services.AddSwaggerGen();
            builder.Services.AddDbContext<DataContext>(options =>
            options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")),
            ServiceLifetime.Scoped);


            //Enable CORS
            builder.Services.AddCors(options =>
            {
                options.AddPolicy(name: myAllowSpecificOrigins,
                    builder =>
                    {
                        builder.WithOrigins("http://localhost:4200")
                        .AllowAnyMethod()
                        .AllowCredentials()
                        .AllowAnyHeader();
                    });

            });

            var app = builder.Build();

            if (args.Length == 1 && args[0].ToLower() == "seeddata")
                SeedData(app);

            void SeedData(IHost app)
            {
                var scopedFactory = app.Services.GetService<IServiceScopeFactory>();
                using (var scope = scopedFactory.CreateScope())
                {
                    var service = scope.ServiceProvider.GetService<Seed>();
                    service.SeedDataContext();
                }
            }

            // Manually set WebRootPath if null
            var webHostEnvironment = app.Services.GetService<IWebHostEnvironment>();
            if (string.IsNullOrEmpty(webHostEnvironment.WebRootPath))
            {
                webHostEnvironment.WebRootPath = Path.Combine(Directory.GetCurrentDirectory(), "wwwroot");
                Directory.CreateDirectory(webHostEnvironment.WebRootPath); // Ensure the directory exists
            }

            Console.WriteLine($"WebRootPath: {webHostEnvironment.WebRootPath}");

            // Configure the HTTP request pipeline.
            if (app.Environment.IsDevelopment())
            {
                app.UseSwagger();
                app.UseSwaggerUI();
            }

            // image
            app.UseStaticFiles();

            app.UseHttpsRedirection();
            app.UseCors(myAllowSpecificOrigins);

            app.UseAuthorization();


            app.MapControllers();

            app.Run();
        }
    }
}
