import { Component, OnInit } from '@angular/core';
import { Emitters } from '../emitters';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {
  message = '';

  constructor(private http: HttpClient) {}

  ngOnInit(): void {
    this.http.get('https://localhost:7242/api/User', { withCredentials: true }).subscribe(
      (res: any) => {
        this.message = `Greetings ${res.name} !`;
        Emitters.authEmitter.emit(true);
      },
      err => {
        this.message = 'You are not logged in';
        Emitters.authEmitter.emit(false);
      }
    );
  }
}
