import { Component, OnInit, EventEmitter,Input , Output } from '@angular/core';
import { FormBuilder, FormGroup, Validators, ValidationErrors, FormArray, AbstractControl } from '@angular/forms';

@Component({
  selector: 'app-sizer',
  templateUrl: './sizer.component.html',
  styleUrls: []
})

export class SizerComponent {

  @Input()  size: number | string;
  @Output() sizeChange = new EventEmitter<number>();

  dec() { this.resize(-1); }
  inc() { this.resize(+1); }

  resize(delta: number) {
    this.size = Math.min(40, Math.max(8, +this.size + delta));
    this.sizeChange.emit(this.size);
  }
}