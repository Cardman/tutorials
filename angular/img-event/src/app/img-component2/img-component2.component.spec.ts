import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ImgComponent2Component } from './img-component2.component';

describe('ImgComponent2Component', () => {
  let component: ImgComponent2Component;
  let fixture: ComponentFixture<ImgComponent2Component>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ImgComponent2Component ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ImgComponent2Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
