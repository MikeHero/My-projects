import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators, AbstractControl, ValidationErrors } from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {

  form!: FormGroup;
  successMessage: string = ''; // To display a success message

  constructor(
    private formBuilder: FormBuilder,
    private http: HttpClient,
    private router: Router
  ) { }

  ngOnInit(): void {
    // Initialize the form and its validators
    this.form = this.formBuilder.group({
      name: ['', Validators.required],
      email: ['', [Validators.required, Validators.email, this.emailDomainValidator]], // Email validation with custom domain validator
      password: ['', [Validators.required, Validators.minLength(6)]] // Password validation: required and min length 6
    });
  }

  // Submit function triggered only when the form is submitted
  submit(): void {
    if (this.form.invalid) {
      this.form.markAllAsTouched();  // Mark all fields to show errors
      return;
    }
  
    // Post data to the API and handle the plain text response
    this.http.post('https://localhost:7242/api/Register', this.form.getRawValue(), { responseType: 'text' })
      .subscribe(response => {
        console.log('Registration successful', response);  // Log the plain text response
        this.successMessage = 'Registration successful! Redirecting to login...';
  
        // Redirect after 3 seconds
        setTimeout(() => {
          console.log('Redirecting to login');
          this.router.navigate(['/login']);  // Ensure this works
        }, 3000); // 3 second delay
      },
      (error) => {
        console.error('Registration failed:', error); // Handle registration error
      });
  }
  

  // Custom validator to check for specific email domains
  emailDomainValidator(control: AbstractControl): ValidationErrors | null {
    const email = control.value;
    if (email && !email.endsWith('@gmail.com') && !email.endsWith('@yahoo.com')) {
      return { domainInvalid: true }; // Return an error object if the domain is invalid
    }
    return null; // Return null if validation passes
  }

  // Helper methods for validation
  get email() {
    return this.form.get('email');
  }

  get name() {
    return this.form.get('name');
  }

  get password() {
    return this.form.get('password');
  }
}
