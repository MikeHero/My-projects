import { Component, OnInit } from '@angular/core';
import { navbarData } from './nav-data';
import { Emitters } from '../../user/emitters';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'navbar',
  templateUrl: './nav-bar.component.html',
  styleUrls: ['./nav-bar.component.css']
})
export class NavBarComponent implements OnInit {
  authenticated = false;
  userName: string = ''; // This will store the user's name

  navData = navbarData;

  constructor(private http: HttpClient) {}

  ngOnInit(): void {
    this.checkAuthentication();

    // Subscribe to the authentication emitter to update UI dynamically
    Emitters.authEmitter.subscribe((auth: boolean) => {
      this.authenticated = auth;
      if (auth) {
        this.fetchUserName(); // Fetch the user's name once authenticated
      }
    });
  }

  checkAuthentication(): void {
    // Check if the user is authenticated and set the authenticated state
    this.http.get('https://localhost:7242/api/User', { withCredentials: true }).subscribe(
      (res: any) => {
        this.userName = res.name; // Set the username if the user is authenticated
        Emitters.authEmitter.emit(true); // Emit authenticated status
      },
      err => {
        Emitters.authEmitter.emit(false); // Emit unauthenticated status if error occurs
      }
    );
  }

  fetchUserName(): void {
    // Fetch the user's name if authenticated
    this.http.get('https://localhost:7242/api/User', { withCredentials: true }).subscribe(
      (res: any) => {
        this.userName = res.name; // Update the user's name
      },
      err => {
        console.error('Failed to fetch user name', err); // Handle the error
      }
    );
  }

  logout(): void {
    this.http.post('https://localhost:7242/api/Logout', {}, { withCredentials: true }).subscribe(
      () => {
        this.authenticated = false;
        this.userName = ''; // Clear the user name after logout
        Emitters.authEmitter.emit(false); // Emit unauthenticated status
      },
      err => {
        console.error('Logout failed', err); // Handle logout error
      }
    );
  }
}
