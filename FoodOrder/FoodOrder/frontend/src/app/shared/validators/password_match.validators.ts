import { AbstractControl } from "@angular/forms"

export const PasswordsMatchvalidator = (passwordControlname: string, confirmPasswordControlName: string) =>
    {
        const validator = (form : AbstractControl) => {
            const passwordControl = form.get(passwordControlname);
            const confirmPasswordControl = form.get(confirmPasswordControlName);

            if( !passwordControl || !confirmPasswordControl)
                return ;

            if( passwordControl.value !== confirmPasswordControl.value) {
                confirmPasswordControl.setErrors({notMatch: true});
            }
            else
            {
                const errors = confirmPasswordControl.errors;
                if(!errors)
                    return ;

                delete errors["notMatch"];
                confirmPasswordControl.setErrors(errors)
            }
        }
        return validator;
    }