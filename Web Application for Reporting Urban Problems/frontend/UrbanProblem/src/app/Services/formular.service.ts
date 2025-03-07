import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class FormularService {

  private apiUrl = "https://localhost:7242/api/Formular";

  constructor(private http: HttpClient) {}

  submitForm(formData: any): Observable<Blob> {
    return this.http.post(`${this.apiUrl}`, formData, { responseType: 'blob' });
  }
}
