export class User {

  id: string;
  firstName: string;
  lastName: string;
  email: string;
  last: Date=new Date();
}
export class UserCriteria {

    id:number=0;

    firstName: string='';

    lastName: string='';

    email: string='';
    last: Date=null;

}

export class UserCriteria3 {

    begin: Date=null;
    end: Date=null;
    onlyNullFlag: boolean=false;
}

export class UserCriteria4 {

    begin: string|null=null;
    end: string|null=null;
    onlyNullFlag: boolean=false;

}