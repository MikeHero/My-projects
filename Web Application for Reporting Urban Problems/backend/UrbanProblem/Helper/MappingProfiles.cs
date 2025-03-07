using AutoMapper;
using UrbanProblem.Dto;
using UrbanProblem.Models;

namespace UrbanProblem.Helper
{
    public class MappingProfiles : Profile
    {
        public MappingProfiles()
        {
            CreateMap<Problem, ProblemDto>();
            CreateMap<Category, CategoryDto>();
            CreateMap<Authority, AuthorityDto>();
            CreateMap<Responsible, ResponsibleDto>();
            CreateMap<Review, ReviewDto>();
            CreateMap<Reporter, ReporterDto>();
            CreateMap<Image, ImageDto>();
            CreateMap<Formular, FormularDto>();

            // CreateCategory Post
            CreateMap<CategoryDto, Category>();
            CreateMap<AuthorityDto, Authority>();
            CreateMap<ResponsibleDto, Responsible>();
            CreateMap<ProblemDto, Problem>();
            CreateMap<ReviewDto, Review>();
            CreateMap<ReporterDto, Reporter>();
            CreateMap<ImageDto, Image>();
            CreateMap<FormularDto, Formular>();
        }
    }
}
