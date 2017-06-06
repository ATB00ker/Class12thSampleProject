#include<fstream.h>
#include<process.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
int log=1;
int global=0;
int flagger=0;
int start=0;
double q=0;
long save;
class bank
{
protected:
	  char pass[30];
	  long accno;
	  char name[30];
	  double balance;
	  char acctype;
public:
 bank()
 {
 accno=1000;
 strcpy(name,"sample");
 balance=0;
 acctype='S';
 strcpy(pass,"sample");
 }
 int compare(char*);
 void Delete();
 void Changer();
 void Transfer();
 void commence();
 void deposite();
 void withdraw();
 void display();
 void password();
 void static box();
}s,e,tra,tr;
class user: public bank
{
public:
static void logout();
};
void user::logout()
{
clrscr();
gotoxy(6,6);
cout<<"Are You Sure?(Y/N)";
bank::box();
char t;
t=getch();
if(t=='y'||t=='Y')
{
log=1;
global=0;
  _setcursortype(_NOCURSOR);
 for(int load=0;load<=3;load++)
  {
  gotoxy(77,10);
  cout<<'|';
  gotoxy(6,10);
  cout<<"logging out";
  for(int dot=0;dot<=4;dot++)
  {
  delay(150);
  cout<<'.';
  }
  gotoxy(6,10);
  clreol();
 }
}
else if(t=='n'||t=='N')
return;
else
 {gotoxy(10,11);
  cout<<"Wrong input";
  getch();
  logout();
 }
}
int bank::compare(char* passw)
{
if(strcmp(pass,passw)==0)
 return 1;
else
 return 0;
}
void bank::Changer()
{
strcpy(pass,"bank123");
ofstream fout;
fout.open("Bank.dat",ios::binary|ios::app);
if(!fout)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 101: Could NOT find the file!";
  getch();
  return;
  }
fout.seekp(global,ios::beg);
fout.write((char*)&s,sizeof(s));
fout.close();
getch();
}
int Delete_check(int check)
{
char line[5];
int m;
ofstream f("deleted.txt",ios::app);
if(!f)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 102: Could NOT find the file!";
  getch();
  abort();
  }
f.close();
ifstream fin("deleted.txt",ios::app);
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 103: Could NOT find the file!";
  getch();
  abort();
  }
while(fin.getline(line,5,'\n'))
 {
 m=(line[0]-48)*1000+(line[1]-48)*100+(line[2]-48)*10+(line[3]-48);
 if(check==m)
  {
  return 1;
  }
 }
return 0;
}
void Loder()
{
 for(int load=0;load<=3;load++)
  {
  gotoxy(77,10);
  cout<<'|';
  gotoxy(5,10);
  cout<<"Loading";
   for(int dot=0;dot<=4;dot++)
   {
   delay(150);
   cout<<'.';
   }
   gotoxy(5,10);
   clreol();
  }
gotoxy(77,10);
cout<<'|';
gotoxy(6,10);
cout<<"*Process succesful*";
gotoxy(5,12);
cout<<"Press any key To continue";
getch();
}
void authenticator()
{
int y=3;
char passw[30];
int check,know;
ifstream fin;
fin.open("Bank.dat",ios::binary);
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 104: Could NOT find the file!";
  getch();
  return;
  }
while(y!=0)
 {
 clrscr();
 bank::box();
 gotoxy(5,5);
 cout<<"Enter Your Acount Number: ";
 gotoxy(5,6);
 cout<<"Enter Password: ";
 gotoxy(31,5);
 cin>>check;
 gotoxy(21,6);
 for(int i=0;passw[i-1]!=13;i++)
  {
  passw[i]=getch();
  if(passw[i]!=13)
    cout<<'*';
  if(passw[i]==8)
   {
   cout<<"\b\b  \b\b";
   i=i-2;
   }
  }
  passw[i-1]='\0';
  if(Delete_check(check)==1)
   {
   gotoxy(5,8);
   cout<<"Sorry! This account has been deleted!";
   getch();
   return;
   }
  if(check<999)
   {
   gotoxy(5,8);
   cout<<"Illigal Account Number,Please try Again!";
   y--;
   gotoxy(5,10);
   cout<<"YOU have "<<y<<" number of tries left";
   for(i=0;i<5;i++)
    {
    cout<<"\a";
    delay(150);
    }
   continue;
   }
  if((check-1000)>start)
   {
   gotoxy(5,8);
   cout<<"Wrong Account Number,Please Try Again!";
   y--;
   gotoxy(5,10);
   cout<<"YOU have "<<y<<" number of tries left";
   for(i=0;i<5;i++)
    {
    cout<<"\a";
    delay(150);
    }
   continue;
   }
  fin.seekg((check-1001)*sizeof(s),ios::beg);
  fin.read((char*)&s,sizeof(s));
  know=s.compare(passw);
  if(know==1)
   {
   gotoxy(6,9);
   cout<<"*Login Success!*"<<endl;
   global=check-1001;
   log=0;
   for(int load=0;load<=3;load++)
    {
    gotoxy(77,11);
    cout<<'|';
    gotoxy(5,11);
    cout<<"Loading";
    for(int dot=0;dot<=4;dot++)
     {
     delay(150);
     cout<<'.';
     }
    gotoxy(5,11);
    clreol();
    }
   y=3;
   clrscr();
   return;
   }
  if(know==0)
  {
  y--;
  gotoxy(5,10);
  cout<<"INCORRECT PASSWORD!";
  gotoxy(5,11);
  cout<<"Please try again!";
  gotoxy(5,12);
  cout<<"YOU have "<<y<<" number of tries left";
   for(i=0;i<5;i++)
   {
   cout<<"\a";
   delay(150);
   }
  }
}
 fin.close();
 clrscr();
 bank::box();
 gotoxy(5,5);
 cout<<"WRONG PASSWORD!";
 gotoxy(5,6);
 cout<<"YOUR PASSWORD is changed for security reasons!";
 gotoxy(5,7);
 cout<<"PLEASE CONTACT SUPPORT!";
 fin.close();
 s.Changer();
 y=3;
 getch();
 clrscr();
}
void Retrive()
{
clrscr();
bank::box();
ifstream f;
ofstream fout("temp");
if(!f)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 105: Could NOT find the file!";
  getch();
  return;
  }
if(!fout)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 106: Could NOT find the file!";
  getch();
  return;
  }
int check,tel=0;
char line[5];
int m;
f.open("deleted.txt",ios::app|ios::in);
if(!f)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 111: Could NOT find the file!";
  getch();
  return;
  }
f.seekg(0);
gotoxy(5,5);
cout<<"Enter the account Number You want to retrive: ";
cin>>check;
if((Delete_check(check))==0)
 {
 gotoxy(5,7);
 cout<<"The acount Number YOU entered is not in our records!";
 getch();
 return;
 }
while(f.getline(line,5,'\n'))
 {
 m=(line[0]-48)*1000+(line[1]-48)*100+(line[2]-48)*10+(line[3]-48);
 tel=(f.tellg());
 if(check==m)
  {
  gotoxy(5,7);
  cout<<"We have found the record!";
  gotoxy(5,8);
  cout<<"Please enter following Details to Retrive data!";
  getch();
  f.seekg(0);
  while(f.getline(line,5,'\n'))
   {
   m=(line[0]-48)*1000+(line[1]-48)*100+(line[2]-48)*10+(line[3]-48);
   if(f.tellg()!=tel)
    {
    fout<<m;
    fout.put('\n');
    }
   f.getline(line,5,'\n');
   }
  f.close();
  fout.close();
  remove("deleted.txt");
  rename("temp","deleted.txt");
  authenticator();
  clrscr();
  bank::box();
   if(log==0)
   {
   log=1;
   global=0;
   gotoxy(5,6);
   cout<<"WE are retriving YOUR account DATA!";
   gotoxy(5,8);
   cout<<"THANK YOU!"<<(char)1;
   Loder();
   f.close();
   return;
   }
   fout.open("deleted.txt",ios::app);
   if(!fout)
    {
    clrscr();
    bank::box();
    gotoxy(5,6);
    cout<<"Error 102: Could NOT find the file!";
    getch();
    return;
    }
   fout<<check;
   fout.put('\n');
   fout.close();
   gotoxy(5,5);
   cout<<"Account NOT retrived as Details given are invaild";
   gotoxy(5,7);
   cout<<"Please RETRY,Thank You!"<<(char)1;
   getch();
   f.close();
  }
 }
}
void bank::commence()
{
bank::box();
start++;
accno=start+1000;
gotoxy(5,6);
cout<<"Welcome NEW user\n";
gotoxy(5,8);
cout<<"Please fill the following form to become a member!\n";
gotoxy(5,10);
cout<<"Its really Simple!\n";
gotoxy(5,12);
cout<<"Enter YOUR name\n";
gotoxy(5,14);
cout<<"Account type you desire:";
gotoxy(6,16);
textcolor(4);
cout<<"S-SAVE\n";
gotoxy(6,17);
cout<<"C-CURRENT\n";
textcolor(9);
gotoxy(5,19);
cout<<"AND a password!";
gotoxy(50,43);
cout<<"Press any key to Continue\n";
  getch();
  clrscr();
  bank::box();
  gotoxy(5,5);
  cout<<"Enter YOUR Name: ";
  gets(name);
  int a=0;
  do
    {
     gotoxy(5,7);
     cout<<"Enter Desired Account Type: ";
     cin>>acctype;
     if(acctype=='s'||acctype=='c'||acctype=='C'||acctype=='S')
    {
     cout<<'\n';
     a=1;
    }
     else
     {
     gotoxy(5,8);
     cout<<"Illegal Input\n";
     gotoxy(5,9);
     cout<<"ACCOUNT TYPE:\n";
     gotoxy(5,10);
     cout<<"S-SAVE\n";
     gotoxy(5,11);
     cout<<"C-CURRENT\n";
     gotoxy(5,12);
     cout<<"Enter Only S Or C\n";
     getch();
     clrscr();
     bank::box();
     gotoxy(5,5);
     cout<<"Enter YOUR Name: "<<name<<endl;
     }
    }while(a==0);
 password();
 balance=0;
 ofstream fout;
 if(!fout)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 106: Could NOT find the file!";
  getch();
  return;
  }
 fout.open("Bank.dat",ios::binary|ios::app);
 fout.seekp(sizeof(s)*(accno-1001),ios::beg);
 fout.write((char*)&s,sizeof(s));
 fout.close();
}
void bank::password()
{
char pas[30];
char pasw[30];
int i;
int a=0;
do
 {
 gotoxy(5,9);
 cout<<"Enter a password of your choice: ";
 for(i=0;pas[i-1]!=13;i++)
  {
  pas[i]=getch();
  if(pas[i]!=13)
  cout<<'*';
  if(pas[i]==8)
   {
   cout<<"\b\b \b\b";
   i=i-2;
   }
  }
 pas[i-1]='\0';
 gotoxy(5,10);
 cout<<"PLEASE Re-enter to confirm: ";
 for(i=0;pasw[i-1]!=13;i++)
  {
  pasw[i]=getch();
  if(pasw[i]!=13)
  cout<<'*';
  if(pasw[i]==8)
   {
   cout<<"\b\b \b\b";
   i=i-2;
   }
  }
  pasw[i-1]='\0';
 if(strcmp(pas,pasw)==0)
 {
 strcpy(pass,pas);
 gotoxy(5,12);
 cout<<"*Process succesful*";
 gotoxy(5,13);
 cout<<"Account Number of YOUR accout is "<<accno<<endl;
 a=1;
 getch();
 }
 else
  {
  gotoxy(5,12);
  cout<<"Error!\n";
  gotoxy(5,13);
  cout<<"Passwords you entered did not match,Account NOT Created!\n";
  gotoxy(5,14);
  cout<<"Please RETRY!";
  gotoxy(5,15);
  getch();
  clrscr();
  bank::box();
  gotoxy(5,5);
  cout<<"Account Number of YOUR accout is "<<accno<<endl;
  gotoxy(5,7);
  cout<<"Enter Desired Account Type: "<<acctype<<endl;
  }
 }while(a==0);
}
void bank::deposite()
{
ofstream f1;
ifstream fin;
if(!f1)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 107: Could NOT find the file!";
  getch();
  return;
  }
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 108: Could NOT find the file!";
  getch();
  return;
  }
balance+=q;
f1.open("temp",ios::binary);
fin.open("Bank.dat",ios::binary|ios::app);
while(fin.read((char*)&e,sizeof(e)))
 {
 if(((fin.tellg()/sizeof(s))-1)==global)
 f1.write((char*)&s,sizeof(s));
 else
 f1.write((char*)&e,sizeof(e));
 }
fin.close();
f1.close();
remove("Bank.dat");
rename("temp","Bank.dat");
q=0;
}
void bank::withdraw()
{
if(balance-q>=2000)
{
balance-=q;
ofstream f1;
ifstream fin;
if(!f1)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 108: Could NOT find the file!";
  getch();
  return;
  }
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 109: Could NOT find the file!";
  getch();
  return;
  }
f1.open("temp",ios::binary);
fin.open("Bank.dat",ios::binary|ios::app);
while(fin.read((char*)&e,sizeof(e)))
 {
 if(((fin.tellg()/sizeof(s))-1)==global)
 f1.write((char*)&s,sizeof(s));
 else
 f1.write((char*)&e,sizeof(e));
 }
fin.close();
f1.close();
Loder();
remove("Bank.dat");
rename("temp","Bank.dat");
return;
}
if(balance-q<2000)
 {
 flagger=1;
 gotoxy(6,11);
 cout<<"Error!Transaction Cannot be done!";
 gotoxy(6,13);
 cout<<"Bank Balance Reduces To less than 2000,For Purposes a minimum of ";
 gotoxy(6,14);
 cout<<"2000 shall always remain in account";
 getch();
 }
q=0;
}
void bank::display()
{
clrscr();
bank::box();
  gotoxy(5,6);
  cout<<"Your account Details :";
  gotoxy(12,8);
  cout<<"Account Number: "<<accno;
  gotoxy(12,10);
  cout<<"Name: "<<name;
  gotoxy(12,12);
  cout<<"Balance: "<<balance;
  gotoxy(12,14);
  cout<<"Account Type: "<<acctype;
  getch();
}
void bank::Delete()
{
clrscr();
bank::box();
char a;
gotoxy(5,5);
cout<<"Are YOU sure?(Y/N)";
a=getch();
if(a=='y'||a=='Y')
 {
 clrscr();
 bank::box();
  if(balance>2000)
   {
   q=balance-2000;
   gotoxy(5,5);
   cout<<"Total money Withdrawed "<<balance-2000<<" (Rs.2000 is in";
   gotoxy(5,6);
   cout<<"the account for various purposes)";
   withdraw();
   }
  else
   {
   gotoxy(5,5);
   cout<<"Balance of 2000 is kept for various purposes.";
   }
 gotoxy(5,8);
 cout<<"Account can be recovered from the main menu.";
 ofstream fout("deleted.txt",ios::app);
 fout<<accno;
 fout.put('\n');
 fout.close();
 log=1;
 global=0;
 gotoxy(5,14);
 cout<<"THANK YOU"<<(char)1;
 Loder();
}
else
 {
 clrscr();
 bank::box();
 return;
 }
q=0;
}
void bank::Transfer()
{
clrscr();
bank::box();
int check,amount,local;
gotoxy(5,5);
cout<<"Enter the Account Number of The Person";
gotoxy(5,6);
cout<<"You want to send money: ";
cin>>check;
if(Delete_check(check)==1)
 {
 gotoxy(5,8);
 cout<<"Sorry! This account has been deleted!";
 getch();
 return;
 }
if(check<999)
   {
   gotoxy(5,8);
   cout<<"Illigal Account Number,Please try Again!";
   getch();
   return;
   }
  if((check-1000)>start)
   {
   gotoxy(5,8);
   cout<<"Wrong Account Number,Please Try Again!";
   getch();
   return;
   }
  if(check==accno)
   {
   gotoxy(5,8);
   cout<<"Invalid Choice!YOU cannot send money from ";
   gotoxy(5,9);
   cout<<"an account to Itself!";
   getch();
   return;
   }
ifstream fin;
fin.open("Bank.dat",ios::binary);
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 110: Could NOT find the file!";
  getch();
  return;
  }
fin.seekg((check-1001)*sizeof(tr));
fin.read((char*)&tr,sizeof(tr));
gotoxy(5,8);
cout<<"Enter the Amount YOU want To send: ";
cin>>amount;
q=amount;
s.withdraw();
if(flagger==1)
flagger=0;
else if(flagger==0)
 {
 q=amount;
 tra=s;
 s=tr;
 local=global;
 global=check-1001;
 s.deposite();
 s=tra;
 global=local;
 q=0;
 }
 q=0;
}
void bank::box()
{
int i;
gotoxy(4,4);
for(i=0;i<73;i++)
 {
 cout<<'-';
 }
gotoxy(76,4);
for(i=5;i<46;i++)
 {
 gotoxy(77,i);
 cout<<'|';
 }
for(i=5;i<46;i++)
 {
 gotoxy(3,i);
 cout<<'|';
 }
 gotoxy(4,46);
 for(i=0;i<73;i++)
 {
 cout<<'-';
 }
  time t;
  date d;
  gettime(&t);
  getdate(&d);
  gotoxy(59,8);
  if((int)t.ti_hour<10)
   {
   if((int)t.ti_min<10)
   cout<<"TIME: "<<'0'<<(int)t.ti_hour<<':'<<'0'<<(int)t.ti_min;
   else
   cout<<"TIME: "<<'0'<<(int)t.ti_hour<<':'<<(int)t.ti_min;
   }
  if((int)t.ti_hour>10)
   {
   if((int)t.ti_min<10)
   cout<<"TIME: "<<(int)t.ti_hour<<':'<<'0'<<(int)t.ti_min;
   else
   cout<<"TIME: "<<(int)t.ti_hour<<':'<<(int)t.ti_min;
   }
  gotoxy(59,9);
   cout<<"DATE: "<<(int)d.da_day<<'-'<<(int)d.da_mon<<'-'<<(int)d.da_year;
}
void main()
{
_setcursortype(_NOCURSOR);
clrscr();
textbackground(7);
textcolor(9);
bank::box();
gotoxy(27,2);
cout<<"WINTER HOLIDAY HOMEWORK";
gotoxy(27,23);
cout<<"HINDUSTAN BANK APPLICATION";
gotoxy(60,47);
cout<<"-MADE BY";
gotoxy(65,48);
cout<<"AJAY TRIPATHI";
getch();
ifstream fin;
ofstream fout;
if(!fin)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 111: Could NOT find the file!";
  getch();
  return;
  }
if(!fout)
  {
  clrscr();
  bank::box();
  gotoxy(5,6);
  cout<<"Error 112: Could NOT find the file!";
  getch();
  return;
  }
fout.open("Bank.dat",ios::binary|ios::app);
fout.close();
fin.open("Bank.dat",ios::binary);
fin.seekg(0,ios::end);
start=(fin.tellg()/sizeof(s));
int e;
while(1)
{
 clrscr();
  gotoxy(33,2);
  cout<<"HINDUSTAN BANK";
  gotoxy(31,6);
  if(log==1)
  {
  cout<<"ENTER YOUR CHOICE\n\n   1.Become a NEW Member\n\n   2.Login as an Existing Member\n\n   3.Retrive Account\n\n   4.Exit";
  }
  if(log==0)
  {
  cout<<"ENTER YOUR CHOICE\n\n   1.View Details of your account\n\n   2.Deposit money in your account\n\n   3.Withdraw money in your account\n\n   4.Send Money\n\n   5.Delete your account\n\n   6.logout\n\n";
  }
  bank::box();
  e=getch();
  switch(e-48)
  {
  case 1:
	  if(log==0)
	  {
      clrscr();
	  s.display();
	  break;
	  }
	  if(log==1)
	  {
      clrscr();
	  s.commence();
	  break;
	  }
  case 2:
      if(log==1)
      {
      authenticator();
      break;
      }
      if(log==0)
       {
       clrscr();
       bank::box();
       gotoxy(6,6);
       cout<<"How much money do you wish to deposite?";
       gotoxy(6,8);
       cout<<"I Want to deposite: ";
       cin>>q;
       s.deposite();
       Loder();
       clrscr();
       bank::box();
       break;
       }
  case 3:
      if(log==1)
      {
      Retrive();
      break;
      }
      if(log==0)
       {
       clrscr();
       bank::box();
       gotoxy(6,6);
       cout<<"How much do wish to withdraw?";
       gotoxy(6,8);
       cout<<"I want to withdraw: ";
       cin>>q;
       s.withdraw();
       clrscr();
       bank::box();
       break;
       }
  case 4:
      if(log==1)
      return;
      if(log==0)
       {
       clrscr();
       s.Transfer();
       break;
       }
   case 5:
      if(log==1)
       {
       clrscr();
       bank::box();
       gotoxy(6,6);
       cout<<"Invalid Input";
       delay(750);
       break;
       }
      if(log==0)
       {
       clrscr();
       s.Delete();
       break;
       }
   case 6:
       if(log==1)
       {
       clrscr();
       bank::box();
       gotoxy(6,6);
       cout<<"Invalid Input";
       delay(750);
       break;
       }
      if(log==0)
       {
       clrscr();
       user::logout();
       break;
       }
  default:
	   clrscr();
	   bank::box();
	   gotoxy(6,6);
	   cout<<"Invaild input";
	   delay(750);
  }
 }
}
