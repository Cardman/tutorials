import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { OpersComponent } from './opers.component';

describe('OpersComponent', () => {
  let component: OpersComponent;
  let fixture: ComponentFixture<OpersComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ OpersComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(OpersComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
