import { Component, OnInit } from '@angular/core';

import {OpersService} from '../opers.service';

@Component({
  selector: 'app-opers',
  templateUrl: './opers.component.html',
  styleUrls: ['./opers.component.css']
})
export class OpersComponent implements OnInit {
  first=0;
  second=0;
  sumres=0;
  prodres=0;
  constructor(private opersService:OpersService) { }

  ngOnInit() {
  }
  sum():void{
    this.opersService.sum(this.first,this.second).subscribe(res => {this.sumres = res;});
  }
  prod():void{
    this.opersService.prod(this.first,this.second).subscribe(res => {this.prodres = res;});
  }
}
