import { Component, OnInit, EventEmitter, Output } from '@angular/core';
import { FormBuilder, FormGroup, Validators, ValidationErrors, FormArray, AbstractControl } from '@angular/forms';

@Component({
  selector: 'selection_liste',
  templateUrl: './selection_liste.component.html',
  styleUrls: []
})
export class SelectionListeComponent implements OnInit {

  userForm: FormGroup;
  @Output() newItemEvent = new EventEmitter<string[]>();
  @Output() newItemEvent2 = new EventEmitter<string[]>();
  @Output() closeFyout = new EventEmitter<boolean>();
  choices = ["ONE","TWO","THREE","FOUR","FIVE","SIX"];
  minHob = 2;
  minLen = 4;

  constructor(private formBuilder: FormBuilder) {

  }

  ngOnInit():void {
    this.userForm = this.formBuilder.group({
      //hobbies: [this.formBuilder.array([]),this.count]
      hobbies: this.formBuilder.array([],this.count.bind(this)),
      mult: [[],[]]
    });
    //this.userForm.get('hobbies').setValidators(this.count);
  }
  getHobbies(): FormArray {
    return this.userForm.get('hobbies') as FormArray;
  }
  onSubmitForm():void {
    var selection_liste=[];
    this.getHobbies().controls.forEach(v => selection_liste.push(v.value));
    this.newItemEvent.emit(selection_liste);
    this.newItemEvent2.emit(this.userForm.get('mult').value);
  }
  onCloseFlyout():void {
    this.closeFyout.emit(false);
  }
  onAddHobby():void {
    const hob = this.formBuilder.control(null, this.content.bind(this))
    this.getHobbies().push(hob);
  }
  onRemHobby(ct:AbstractControl):void {
    var hobs = this.getHobbies();
    var len = hobs.length;
    for (var i = 0; i < len; i++){
        if (hobs.at(i) === ct){
            hobs.removeAt(i);
            break;
        }
    }
  }

  count(ct:AbstractControl):ValidationErrors {
    var arr = ct as FormArray
    if (arr === null || arr === undefined){
       return {'absent_ct':-1};
    }
    var nb = arr.length
    return nb > this.minHob?null:{'bad_count':nb};
  }
  content(ct:AbstractControl):ValidationErrors {
   var val = ct.value as string;
   if (val === undefined || val === null ){
     return {'absent':''};
   }
   if (val.length < this.minLen){
     return {'too_short':val.length};
   }
   if (val[0] === val[val.length - 1]){
     return {'same_letter':val[0]};
   }
   return null;
  }
}


