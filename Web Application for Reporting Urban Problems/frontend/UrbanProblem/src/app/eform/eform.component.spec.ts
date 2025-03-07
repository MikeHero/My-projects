import { ComponentFixture, TestBed } from '@angular/core/testing';

import { EformComponent } from './eform.component';

describe('EformComponent', () => {
  let component: EformComponent;
  let fixture: ComponentFixture<EformComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [EformComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(EformComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
