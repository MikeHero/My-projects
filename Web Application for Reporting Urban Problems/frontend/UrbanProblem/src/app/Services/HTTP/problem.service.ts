import { HttpClient, HttpParams, HttpResponse } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Problem } from '../../Models/Problem';
import { map } from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class ProblemService {
  readonly UrbanProblemApiUrl = "https://localhost:7242/api"

  constructor(private http:HttpClient) { }

  // getProblemList(): Observable<Problem[]>{
  //   return this.http.get<Problem[]>(this.UrbanProblemApiUrl + '/Problem');
  // }

  deleteProblem(id:number|string)
  {
    return this.http.delete(this.UrbanProblemApiUrl + `/Problem/${id}`);
  }

  addProblem(formData: FormData, responsibleId: number, catId: number): Observable<HttpResponse<any>> {
    const url = `${this.UrbanProblemApiUrl}/Problem?responsibleId=${responsibleId}&catId=${catId}`;
    return this.http.post(url, formData, { observe: 'response' });  // observe the full response
  }
  
  getProblemImage(probId: number): Observable<{ imageUrl: string }> {
    return this.http.get<{ imageUrl: string }>(this.UrbanProblemApiUrl + `/Image/${probId}`);
  }
  
  

  getProblemList(): Observable<Problem[]> {
    return this.http.get<any[]>(this.UrbanProblemApiUrl + '/Problem').pipe(
      map(problems => problems.map(p => ({
        id: p.id, // Transform `id` to `Id`
        Title: p.title,
        Description: p.description,
        Location: p.location,
        Latitude: p.latitude,
        Longitude: p.longitude,
        Priority: p.priority,
        Solved: p.solved,
        Date: new Date(p.date),
        ImageURL: ''  // Initialize the ImageURL field
      })))
    );
  }

  getProblem(id: number) {
    return this.getProblemList().pipe(
      map(problemsArray => {
        const problem = problemsArray.find(p => p.id === id);
        if (!problem) {
          throw new Error(`Problem with ID ${id} not found`);
        }
        return problem;
      }),
    );
  }

  
  
  
}



