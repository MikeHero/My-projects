import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, MaybeAsync, Resolve, RouterStateSnapshot } from '@angular/router';
import { Observable } from 'rxjs';
import { Problem } from '../../Models/Problem';
import { ProblemService } from '../../Services/HTTP/problem.service';

@Injectable({
  providedIn: 'root'
})
export class ProblemDetailResolverService implements Resolve<Problem>{

  constructor(private problemService: ProblemService ) { }
  resolve(route: ActivatedRouteSnapshot, state: RouterStateSnapshot): Observable<Problem>{
    const probId = +route.params['id'];  
    return this.problemService.getProblem(probId);
  }
}

