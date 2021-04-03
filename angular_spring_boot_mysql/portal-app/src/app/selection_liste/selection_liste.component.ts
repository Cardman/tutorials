import { Component, OnInit, EventEmitter, Output } from '@angular/core';
import { FormBuilder, FormGroup, Validators, ValidationErrors, FormArray, AbstractControl } from '@angular/forms';
import {SelectionListeService} from '../services/selection_liste.service';

@Component({
  selector: 'selection_liste',
  templateUrl: './selection_liste.component.html',
  styleUrls: []
})
export class SelectionListeComponent implements OnInit {

  userForm: FormGroup;
  @Output() newItemEvent = new EventEmitter<string[]>();

  constructor(private formBuilder: FormBuilder, private selectionListeService: SelectionListeService) {

  }

  ngOnInit():void {
    this.userForm = this.formBuilder.group({
      //hobbies: [this.formBuilder.array([]),this.count]
      hobbies: this.formBuilder.array([])
    });
    this.userForm.get('hobbies').setValidators(this.count);
  }
  getHobbies(): FormArray {
    return this.userForm.get('hobbies') as FormArray;
  }
  onSubmitForm():void {
    this.selectionListeService.selection_liste=[];
    this.getHobbies().controls.forEach(v => this.selectionListeService.selection_liste.push(v.value));
    this.newItemEvent.emit(this.selectionListeService.selection_liste);
  }
  onAddHobby():void {
    const hob = this.formBuilder.control(null, this.content)
    this.getHobbies().push(hob);
  }

  count(ct:AbstractControl):ValidationErrors {
    var arr = ct as FormArray
    if (arr === null || arr === undefined){
       return {'absent_ct':-1};
    }
    var nb = arr.length
    return nb > 2?null:{'bad_count':nb};
  }
  content(ct:AbstractControl):ValidationErrors {
   var val = ct.value as string;
   if (val === undefined || val === null ){
     return {'absent':''};
   }
   if (val.length < 4){
     return {'too_short':val.length};
   }
   if (val[0] === val[val.length - 1]){
     return {'same_letter':val[0]};
   }
   return null;
  }
}


