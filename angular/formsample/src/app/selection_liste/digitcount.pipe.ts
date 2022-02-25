import { Pipe, PipeTransform } from '@angular/core';
@Pipe({ 
   name: 'digitcount' 
}) 
export class DigitcountPipe implements PipeTransform { 
   transform(val : number, ...args: string[]) : number {
      if (args.length > 1 && args[0] == 'zero' && args[1] == 'zero'){
          let res = 0;
          for (let c of val.toString().split('')){
              if( c !== '0') {res++;}
          }
          return res * 2; 
      }
      if (args.length > 0 && args[0] == 'zero'){
          let res = 0;
          for (let c of val.toString().split('')){
              if( c !== '0') {res++;}
          }
          return res; 
      }
      return val.toString().length; 
   } 
}