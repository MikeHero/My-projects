import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators, ValidatorFn, AbstractControl, FormControl } from '@angular/forms';
import { User } from '../../Models/User';
import { ProblemService } from '../../Services/HTTP/problem.service';
import moment from 'moment-timezone';

@Component({
  selector: 'app-add-problem',
  templateUrl: './add-problem.component.html',
  styleUrl: './add-problem.component.css'
})
export class AddProblemComponent implements OnInit {
  registrationForm!: FormGroup;
  user!: User;
  userSubmitted!: boolean;

  problemForm!: FormGroup;
  responsibleId!: number;
  categoryId!: number;
  title!: string;
  description!: string;
  location!: string;
  longitude!: number;
  latitude!: number;

  selectedFiles: File[] = [];
  currentTime!: Date;
  formattedDate = '';

  

  constructor(private fb: FormBuilder, private problemService: ProblemService ) { }
  
  onCoordinatesChanged(coords: { latitude: number; longitude: number }) {
    this.latitude = coords.latitude;
    this.longitude = coords.longitude;
    console.log('Coordinates updated:', this.latitude, this.longitude);
  }


  ngOnInit(): void {
    this.problemForm = this.fb.group({
      description: ['', Validators.required],
      title: ['', Validators.required],
      location: ['', Validators.required],
      responsibleId: [null, Validators.required],  
      categoryId: [null, Validators.required]      
    });
  }

  // createRegistrationForm() {
  //   this.registrationForm = this.fb.group({
  //     categoryId: [null, Validators.required],
  //     username: [null, Validators.required],
  //     email: [null, [Validators.required, Validators.email]],
  //     passwword: [null, [Validators.required, Validators.minLength(3)]],
  //     confirmPassword: [null, Validators.required],
  //     mobile: [null, [Validators.required, Validators.maxLength(10)]]
  //   }, {validators: this.passwordMatchingValidator})
  // }

  // passwordMatchingValidator: ValidatorFn = (control: AbstractControl): { [key: string]: boolean } | null => {
  //   const password = control.get('password')?.value;
  //   const confirmPassword = control.get('confirmPassword')?.value;
  //   return password === confirmPassword ? null : { notmatched: true };
  // };


  // ------------------------------------
  // Getter methods for all form controls
  // ------------------------------------
  // get userName() {
  //   return this.registrationForm.get('userName') as FormControl;
  // }

  // get email() {
  //   return this.registrationForm.get('email') as FormControl;
  // }
  // get password() {
  //   return this.registrationForm.get('password') as FormControl;
  // }
  // get confirmPassword() {
  //   return this.registrationForm.get('confirmPassword') as FormControl;
  // }
  // get mobile() {
  //   return this.registrationForm.get('mobile') as FormControl;
  // }
  // ------------------------


  // onSubmit() {
  //   console.log("salut")
  //   this.userSubmitted = true;

  //   if( this.registrationForm.valid)
  //   {
  //     //this.user = Object.assign(this.user, this.registrationForm.value);
  //     // this.userService.addUser(this.userData())
  //     this.registrationForm.reset();
  //     this.userSubmitted = false;
  //     // this.alertify.success("Congrats, you are successfully registered");
  //   } else {
  //     // this.alertify.error("Kindly provide the required fields")
  //   }
  // }  
  updateTime() {
    this.currentTime = new Date();
    
    // Convert the date to Romanian time using 'Europe/Bucharest' timezone
    const romanianTime = moment(this.currentTime).tz('Europe/Bucharest').format('dddd, MMMM Do YYYY, HH:mm:ss');
    
    this.formattedDate = romanianTime;
    console.log('Romanian time:', this.formattedDate);
  }

    onFileChange(event: any) {
      if (event.target.files && event.target.files.length) {
        this.selectedFiles = Array.from(event.target.files);
      }
    }

    onSubmit(): void {
      if (this.problemForm.valid) {
        const formValues = this.problemForm.value;
    
        const formData = new FormData();
        formData.append('title', formValues.title);
        formData.append('location', formValues.location);
        console.log("lat:", this.latitude);
        formData.append('latitude', this.latitude ? this.latitude.toString() : '');
        formData.append('longitude', this.longitude ? this.longitude.toString() : '');
        this.currentTime = new Date() // Convert to ISO string for backend compatibility
        this.updateTime();
        formData.append('date', this.currentTime.toISOString());
        formData.append('description', formValues.description);
        const responsibleId = formValues.responsibleId;
        const catId = formValues.categoryId;
    
        for (let file of this.selectedFiles) {
          formData.append('images', file, file.name);
        }
    
        this.problemService.addProblem(formData, responsibleId, catId).subscribe({
          next: (response) => {
            if (response && response.status === 200) {
              console.log('Problem added successfully', response.body);
              this.problemForm.reset();
              this.selectedFiles = [];
            } else {
              console.error('Unexpected status code:', response.status);
            }
          },
          error: (error) => {
            console.error('There was an error adding the problem!', error);
          }
        });
      }
    }
    

  // userData(): User{
  //   return this.user = {
  //     userName: this.userName.value,
  //     email: this.email.value,
  //     password: this.password.value,
  //     mobile: this.mobile.value
  //   }
  // }
}
