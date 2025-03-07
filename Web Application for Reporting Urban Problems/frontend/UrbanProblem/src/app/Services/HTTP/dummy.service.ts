import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Problem } from '../../Models/Problem';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DummyService {

  private problemsUrl = 'assets/problems.json';  // Path to your JSON file
  readonly problemApiUrl = "https://localhost:7074/api";

  constructor(private http: HttpClient) {

  }

  getProblems(): Observable <any[]> {
     return this.http.get<any[]>(this.problemsUrl);
    //return this.http.get<any[]>(this.problemsUrl + '/problems');
  }
}
