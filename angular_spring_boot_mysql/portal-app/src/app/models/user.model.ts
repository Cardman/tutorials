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