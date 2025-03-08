import { LOCALE_ID, NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';



import { AppComponent } from './app.component';
import { FooterComponent } from './Partials/footer/footer.component';
import { NavBarComponent } from './Navbar/nav-bar/nav-bar.component';
import { ClockComponent } from './Partials/clock/clock.component';



import { Routes, RouterModule } from '@angular/router';
import { DatePipe } from '@angular/common';
import { registerLocaleData } from '@angular/common';
import localeRo from '@angular/common/locales/ro';
import { LandingPageComponent } from './Pages/LandingPage/LandingPage.component';

registerLocaleData(localeRo);



import { ProblemCardComponent } from './Problem/problem-card/problem-card.component';
import { ProblemListComponent } from './Problem/problem-list/problem-list.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { FormsModule } from '@angular/forms';
import { TestComponent } from './Pages/test/test.component';
import { Test2Component } from './Pages/test2/test2.component';
import { HttpClientModule } from '@angular/common/http';
import { ProblemDetailComponent } from './Problem/problem-detail/problem-detail.component';
import { AddProblemComponent } from './Problem/add-problem/add-problem.component';
import { ReactiveFormsModule } from '@angular/forms';
import { FeedbackComponent } from './Pages/feedback/feedback.component';
import { ProblemDetailResolverService } from './Problem/problem-detail/problem-detail-resolver.service';
import { TabsModule } from 'ngx-bootstrap/tabs';
import { ToastrModule } from 'ngx-toastr';
import { MapComponent } from './Partials/map/map.component';
import { TitleComponent } from './Partials/title/title.component';
import { LoginComponent } from './user/login/login.component';
import { RegisterComponent } from './user/register/register.component';
import { HomeComponent } from './user/home/home.component';
import { UserComponent } from './user/user/user.component';
import { NavComponent } from './user/nav/nav.component';
import { EformComponent } from './eform/eform.component';

const appRoutes: Routes= [
  {path: '', component: LandingPageComponent},
  //{path: '', component: EformComponent},
  {path: 'add-problem', component: AddProblemComponent},
  {path: 'problem-card', component: ProblemCardComponent},
  {path: 'app-test', component: TestComponent},
  {path: 'app-test2', component: Test2Component},
  {path: 'problem-list', component: ProblemListComponent},
  {path: 'home', component: HomeComponent},
  {path: 'register', component: RegisterComponent},
  {path: 'user', component: UserComponent},
  {path: 'login', component: LoginComponent},
  {path: 'app-feedback', component: FeedbackComponent},
  {path: 'problem-detail/:id', 
    component: ProblemDetailComponent, 
    resolve: {prp: ProblemDetailResolverService}},
  // {path: '**', component: LandingPageComponent},  // wildcard route for a 404 page
]

@NgModule({
  declarations: [
    AppComponent,
    FooterComponent,
    NavBarComponent,
    ProblemListComponent,
    ProblemCardComponent,
    ClockComponent,
    LandingPageComponent,
    TestComponent,
    Test2Component,
    ProblemDetailComponent,
    AddProblemComponent,
    FeedbackComponent,
    MapComponent,
    TitleComponent,
    LoginComponent,
    RegisterComponent,
    HomeComponent,
    EformComponent,
  ],
  imports: [
    BrowserModule,
    RouterModule.forRoot(appRoutes),
    BrowserAnimationsModule,
    FormsModule,
    HttpClientModule,
    ReactiveFormsModule,
    TabsModule.forRoot(),
    ToastrModule.forRoot(), 
  ],
  providers: [
    DatePipe, 
    {provide: LOCALE_ID, useValue: 'ro-RO'}
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
