import { Component, Input } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-feedback',
  templateUrl: './feedback.component.html',
  styleUrl: './feedback.component.css'
})
export class FeedbackComponent {
  @Input() feedback: any;
  formGroup: FormGroup;

  constructor(private fb: FormBuilder, private http: HttpClient) {
    this.formGroup = this.fb.group({
      sugestion: ['', Validators.required],
      ageGroup: ['', Validators.required],
      grade: [0, [Validators.required, Validators.min(1), Validators.max(5)]],
      agreement: [false, Validators.requiredTrue]
    });
  }

  onSubmit() {
    if (window.confirm('Is all the inserted data true?')) {
      if (this.formGroup.valid) {
        const formData = { ...this.formGroup.value, ...this.feedback };
        this.http.post('https://localhost:7242/api/Feedback', formData, { responseType: 'text' }).subscribe(
          response => console.log('Form submitted successfully', response),
          error => console.error('Error submitting form', error)
        );
      } else {
        console.error('Form is invalid');
      }
    }
  }
}
