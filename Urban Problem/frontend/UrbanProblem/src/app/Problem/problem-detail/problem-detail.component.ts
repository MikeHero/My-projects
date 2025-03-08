import { Component, Input, OnInit } from '@angular/core';
import { Problem } from '../../Models/Problem';
import { ActivatedRoute, Router } from '@angular/router';
import { ProblemService } from '../../Services/HTTP/problem.service';

@Component({
  selector: 'app-problem-detail',
  templateUrl: './problem-detail.component.html',
  styleUrls: ['./problem-detail.component.css']
})
export class ProblemDetailComponent implements OnInit {
  public problemId!: number;
  problem = new Problem();
  
  @Input()
  formattedDate!: string;
  
  constructor(
    private route: ActivatedRoute, 
    private router: Router,
    private problemService: ProblemService
  ) {}

  ngOnInit() {
    this.problemId = Number(this.route.snapshot.params['id']);
    
    // Retrieve the query parameter for formattedDate
    this.route.queryParams.subscribe(params => {
      this.formattedDate = params['formattedDate'] || 'No date provided';
    });

    this.route.data.subscribe(
      (data) => {
        this.problem = data['prp'] as Problem;
        console.log("Problem data:", this.problem);
      }
    );

    if (this.problem.ImageURL == "") {
      this.problemService.getProblemImage(this.problemId).subscribe((imageData: any) => {
        console.log(`Image data for Problem ID ${this.problemId}:`, imageData);

        if (Array.isArray(imageData) && imageData.length > 0) {
          this.problem.ImageURL = imageData[0].imageURL;
        } else {
          console.error(`No valid image data found for Problem ID ${this.problem.id}`);
        }
      });
    }

    this.route.params.subscribe((params) => {
      this.problemId = Number(params['id']);
      this.problemService.getProblem(this.problemId).subscribe((data) => {
        this.problem = data as Problem;
      }, error => {
        this.router.navigate(['/']);
      });
    });
  }

  postReview() {
    // Implementation of post review
  }
}
