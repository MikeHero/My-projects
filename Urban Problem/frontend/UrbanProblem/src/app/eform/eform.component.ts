import { Component } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { FormularService } from '../Services/formular.service';

@Component({
  selector: 'app-eform',
  templateUrl: './eform.component.html',
  styleUrl: './eform.component.css'
})
export class EformComponent {
  formular: FormGroup;
  impozit = 0;

  constructor(
    private fb: FormBuilder,
    private formularService: FormularService
    ) {
      this.formular = this.fb.group({
      nume: ['', [Validators.required, Validators.maxLength(50)]],
      judet: ['', Validators.required],
      localitate: ['', Validators.required],
      cnp: ['', [Validators.required, Validators.pattern(/^[0-9]{13}$/)]],
      salariuBrut: [0, [Validators.required, Validators.min(0)]],
      email: ['', [Validators.required, Validators.email]],
      numarTelefon: ['', [Validators.required, Validators.pattern(/^[0-9]{10}$/)]],
      impozit: [{ value: 0, disabled: true }],
      ibanBeneficiar: ['', [Validators.required, Validators.minLength(10), Validators.maxLength(10)]]
    });
  }

  // Calculează impozitul atunci când salariul brut se modifică
  onSalariuBrutChange(): void {
    const salariuBrut = this.formular.get('salariuBrut')?.value || 0;
    this.impozit = salariuBrut * 0.18;
    this.formular.get('impozit')?.setValue(this.impozit);
  }

  onSubmit(): void {
    if (this.formular.valid) {
      const formData = this.formular.getRawValue();
      this.formularService.submitForm(formData).subscribe(
        (response) => {
          const blob = new Blob([response], { type: response.type });
          const url = window.URL.createObjectURL(blob);
          const a = document.createElement('a');
          a.href = url;
          a.download = 'formular.txt';
          a.click();
          window.URL.revokeObjectURL(url);
        },
        (error) => {
          console.error('Error submitting form', error);
          alert('A apărut o eroare la trimiterea formularului');
        }
      );
    }
  }
}
