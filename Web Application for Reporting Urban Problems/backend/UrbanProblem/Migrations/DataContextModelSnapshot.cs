﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using UrbanProblem.Data;

#nullable disable

namespace UrbanProblem.Migrations
{
    [DbContext(typeof(DataContext))]
    partial class DataContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "6.0.23")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder, 1L, 1);

            modelBuilder.Entity("UrbanProblem.Models.Authority", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.ToTable("Authorities");
                });

            modelBuilder.Entity("UrbanProblem.Models.Category", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("Type")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.ToTable("Categories");
                });

            modelBuilder.Entity("UrbanProblem.Models.Feedback", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("AgeGroup")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<bool>("Agreement")
                        .HasColumnType("bit");

                    b.Property<int>("Grade")
                        .HasColumnType("int");

                    b.Property<string>("Sugestion")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.ToTable("Feedbacks");
                });

            modelBuilder.Entity("UrbanProblem.Models.Formular", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("CNP")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("IbanBeneficiar")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<double>("Impozit")
                        .HasColumnType("float");

                    b.Property<string>("Judet")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Localitate")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("NumarTelefon")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Nume")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<double>("SalariuBrut")
                        .HasColumnType("float");

                    b.HasKey("Id");

                    b.ToTable("Formular");
                });

            modelBuilder.Entity("UrbanProblem.Models.Image", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<byte[]>("ImageData")
                        .IsRequired()
                        .HasColumnType("varbinary(max)");

                    b.Property<string>("ImageURL")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<int>("ProblemId")
                        .HasColumnType("int");

                    b.HasKey("Id");

                    b.HasIndex("ProblemId");

                    b.ToTable("Images");
                });

            modelBuilder.Entity("UrbanProblem.Models.Problem", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<DateTime>("Date")
                        .HasColumnType("datetime2");

                    b.Property<string>("Description")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<double?>("Latitude")
                        .HasColumnType("float");

                    b.Property<string>("Location")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<double?>("Longitude")
                        .HasColumnType("float");

                    b.Property<bool>("Priority")
                        .HasColumnType("bit");

                    b.Property<bool>("Solved")
                        .HasColumnType("bit");

                    b.Property<string>("Title")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.ToTable("Problems");
                });

            modelBuilder.Entity("UrbanProblem.Models.ProblemCategory", b =>
                {
                    b.Property<int>("ProblemId")
                        .HasColumnType("int");

                    b.Property<int>("CategoryId")
                        .HasColumnType("int");

                    b.HasKey("ProblemId", "CategoryId");

                    b.HasIndex("CategoryId");

                    b.ToTable("ProblemCategories");
                });

            modelBuilder.Entity("UrbanProblem.Models.ProblemResponsible", b =>
                {
                    b.Property<int>("ProblemId")
                        .HasColumnType("int");

                    b.Property<int>("ResponsibleId")
                        .HasColumnType("int");

                    b.HasKey("ProblemId", "ResponsibleId");

                    b.HasIndex("ResponsibleId");

                    b.ToTable("ProblemResponsibles");
                });

            modelBuilder.Entity("UrbanProblem.Models.Reporter", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("FirstName")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("LastName")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.ToTable("Reporters");
                });

            modelBuilder.Entity("UrbanProblem.Models.Responsible", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("Area")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<int>("AuthorityId")
                        .HasColumnType("int");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.HasIndex("AuthorityId");

                    b.ToTable("Responsibles");
                });

            modelBuilder.Entity("UrbanProblem.Models.Review", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<int>("ProblemId")
                        .HasColumnType("int");

                    b.Property<int>("Rating")
                        .HasColumnType("int");

                    b.Property<int>("ReporterId")
                        .HasColumnType("int");

                    b.Property<string>("Text")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Title")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.HasIndex("ProblemId");

                    b.HasIndex("ReporterId");

                    b.ToTable("Reviews");
                });

            modelBuilder.Entity("UrbanProblem.Models.User", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("Id"), 1L, 1);

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasColumnType("nvarchar(450)");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<string>("Password")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.HasKey("Id");

                    b.HasIndex("Email")
                        .IsUnique();

                    b.ToTable("Users");
                });

            modelBuilder.Entity("UrbanProblem.Models.Image", b =>
                {
                    b.HasOne("UrbanProblem.Models.Problem", "Problem")
                        .WithMany("Images")
                        .HasForeignKey("ProblemId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Problem");
                });

            modelBuilder.Entity("UrbanProblem.Models.ProblemCategory", b =>
                {
                    b.HasOne("UrbanProblem.Models.Category", "Category")
                        .WithMany("ProblemCategories")
                        .HasForeignKey("CategoryId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("UrbanProblem.Models.Problem", "Problem")
                        .WithMany("ProblemCategories")
                        .HasForeignKey("ProblemId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Category");

                    b.Navigation("Problem");
                });

            modelBuilder.Entity("UrbanProblem.Models.ProblemResponsible", b =>
                {
                    b.HasOne("UrbanProblem.Models.Problem", "Problem")
                        .WithMany("ProblemResponsibles")
                        .HasForeignKey("ProblemId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("UrbanProblem.Models.Responsible", "Responsible")
                        .WithMany("ProblemResponsibles")
                        .HasForeignKey("ResponsibleId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Problem");

                    b.Navigation("Responsible");
                });

            modelBuilder.Entity("UrbanProblem.Models.Responsible", b =>
                {
                    b.HasOne("UrbanProblem.Models.Authority", "Authority")
                        .WithMany("Responsibles")
                        .HasForeignKey("AuthorityId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Authority");
                });

            modelBuilder.Entity("UrbanProblem.Models.Review", b =>
                {
                    b.HasOne("UrbanProblem.Models.Problem", "Problem")
                        .WithMany("Reviews")
                        .HasForeignKey("ProblemId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("UrbanProblem.Models.Reporter", "Reporter")
                        .WithMany("Reviews")
                        .HasForeignKey("ReporterId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Problem");

                    b.Navigation("Reporter");
                });

            modelBuilder.Entity("UrbanProblem.Models.Authority", b =>
                {
                    b.Navigation("Responsibles");
                });

            modelBuilder.Entity("UrbanProblem.Models.Category", b =>
                {
                    b.Navigation("ProblemCategories");
                });

            modelBuilder.Entity("UrbanProblem.Models.Problem", b =>
                {
                    b.Navigation("Images");

                    b.Navigation("ProblemCategories");

                    b.Navigation("ProblemResponsibles");

                    b.Navigation("Reviews");
                });

            modelBuilder.Entity("UrbanProblem.Models.Reporter", b =>
                {
                    b.Navigation("Reviews");
                });

            modelBuilder.Entity("UrbanProblem.Models.Responsible", b =>
                {
                    b.Navigation("ProblemResponsibles");
                });
#pragma warning restore 612, 618
        }
    }
}
