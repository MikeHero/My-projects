﻿namespace UrbanProblem.Models
{
    public class Reporter
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public ICollection<Review> Reviews { get; set; }
    }
}
