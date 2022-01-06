import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ImgComponentComponent } from './img-component.component';

describe('ImgComponentComponent', () => {
  let component: ImgComponentComponent;
  let fixture: ComponentFixture<ImgComponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ImgComponentComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ImgComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
