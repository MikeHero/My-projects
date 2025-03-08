import { Component, OnInit } from '@angular/core';
import { ImageService } from '../../Services/HTTP/image.service';
import { ProblemService } from '../../Services/HTTP/problem.service';
import { ActivatedRoute, Router } from '@angular/router';
import { Problem } from '../../Models/Problem';
import { DummyService } from '../../Services/HTTP/dummy.service';

@Component({
  selector: 'problem-list',
  templateUrl: './problem-list.component.html',
  styleUrls: ['./problem-list.component.css']
})
export class ProblemListComponent 
//implements OnInit 
{

  problemList: Problem[] = [];

  
  constructor(  private problemService: ProblemService, private dummyService: DummyService ) {
  
  }

  // ngOnInit(): void {
  //   console.log("Salut!")
  //   this.dummyService.getProblems().subscribe((data: Problem[]) => {
  //     this.problemList = data;
  //   })
  //   console.log("Salut2!")
  // }
  
  ngOnInit(): void {
    this.problemService.getProblemList().subscribe((data: Problem[]) => {
      this.problemList = data;
  
      // Iterate over each problem to fetch its image URL
      this.problemList.forEach((problem: Problem) => {
        console.log(`Problem ID: ${problem.id}`);
        
        // Fetch the image for each problem
        this.problemService.getProblemImage(problem.id).subscribe((imageData: any) => {
          console.log(`Image data for Problem ID ${problem.id}:`, imageData);  // Log the full response
  
          // Check if imageData is an array and has at least one element
          if (Array.isArray(imageData) && imageData.length > 0) {
            // Access imageURL with the correct case-sensitive key
            problem.ImageURL = imageData[0].imageURL;  // Correcting the key to match "imageURL"
          } else {
            console.error(`No valid image data found for Problem ID ${problem.id}`);
          }
  
          // Log the image URL after it's been fetched and assigned
          console.log(`Image for Problem ID ${problem.id}: ${problem.ImageURL}`);
        }, error => {
          console.error(`Error fetching image for problem ID ${problem.id}:`, error);
        });
      });
    }, error => {
      console.error('Error fetching problems:', error);
    });
  }
  
  
  
  
  
  
  
  
  



}
