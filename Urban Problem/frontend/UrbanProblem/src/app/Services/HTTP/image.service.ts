import { HttpClient } from '@angular/common/http';
import { Injectable, OnInit } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ImageService {

  readonly UrbanProblemApiUrl = "https://localhost:7242/api"

  constructor(private http: HttpClient) { }

  getImage(probId: number): Observable<any[]> {
    return this.http.get<any>(this.UrbanProblemApiUrl + `/Image/${probId}`);
  }

  deleteImage(probId: number|string) {
    return this.http.delete(this.UrbanProblemApiUrl + `/Image/${probId}`);
  }

}
