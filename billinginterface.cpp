#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>


using namespace std;

static int count;
class menu //menu related operations//
{
	int itmcode;
	char itmname[50];
	string itemname;
	char ch;
	float dis,price;
	public:
		 void createmenu()
		 {
		 ch='y';
		 	
		 while(ch=='y')
		 {
		 	cout<<"\n\n please enter the itemcode\n";
		 	cin>>itmcode;
		 	cout<<"\n please enter the item name\n";
		 	cin>>itmname;
		 	cout<<"\nplease enter the price\n";
		 	cin>>price;
		 	cout<<"enter the discount";
		 	cin>>dis;
		 	cout<<"another item(y/n)";
		 	cin>>ch;
		 count++;
		 getch();
		 }
	}
		 void showmenu()
		 {
		 	cout<<"\nThe item code is : "<<itmcode;
	 cout<<"\nThe Name of the item is : "<<itmname;
	 cout<<"\nThe Price of the item is : "<<price;
	 cout<<"\nthe discount is:"<<dis;
	 getch();
		 }
	
		 
				
				menu(int x,string y,int z)//parameter constructor//
				{
					itmcode=x;
					itemname = y;
					price=z;
					getch();
				}
				menu()//default constructor NOTE = BOTH MENU FUNCTIONS ARE AN EXAMPLE OF CONSTRUCTOR OVERLOADING//
				{
					itmcode=102;
                    itemname="chickenburger";
					price=45;
					getch(); 					
			
				}
				~menu()//destructor//
				{
				}
				
				void display()
				{
					cout<<"your order is"<<itmname<<" and it's cost is "<<price;
				}
				menu operator + (menu& y)//operator overloading
			{
				price = price + y.price;
				return *this;
				
			
			}
			
			int retitmcode()
			{return itmcode;}
			
			float retprice()
			{return price;}
			
			char* retitmname()
			{return itmname;}
			
			float retdis()
			{return dis;}
			
				friend class account;//friend class declaration all member functions of account are friend functions to menu//
				
	};
	class account
{
    string name;
	float discount;
    float amount;
	public:
		account operator +(const menu& y)//operator overloading const is to make sure member function does not change the reciever object//
		 {
			amount = amount + y.price ;
			return *this;
		}
	float custdiscount(menu a,menu b )
	{
		int d;
		float t;
		amount = t;
		d= a.price + b.price;
		if(d>=300)
		{
		amount = t - (t/10);
		cout<<"amount after discount is:"<<amount;
	}
	else
	cout<<"no discount";
		
	}
	
};	


template <class T> class waiting//template class//
{
	string r;
	int n;
	public:
		
	waiting(){ r="none"; n=0; return; }
	~waiting(){return;}
	
	 void wait(T value);
};
		template <class T> void waiting<T>::wait(T value)//using scope resolution to define function outside of a class//
		{
			cout<<"enter string and waiting number";
			cin>>r>>n;
			cout<<"yourorder/name:"<<r<<"your waiting number is:"<<n;
			
		}
		

//end of class//**************

//file handling//*************

fstream fp;
menu pr;
//function to write in file//
void write_product()
{
 fp.open("new.dat",ios::out|ios::app);
 pr.createmenu();
 fp.write((char*)&pr,sizeof(menu));
 fp.close();
 cout<<"the item has been created";
 getch();
}

//function to read all records from file//

void display_all()
{
	 
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("new.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(menu)))
	{
		pr.showmenu();
		cout<<"\n=======================\n";
		getch();
	}
	fp.close();
	getch();
}

//function to read specific record from file//

void display_sp(int n)
{
	int flag=0;
	 fp.open("new.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(menu)))
    {
    	if(pr.retitmcode()==n)
    	{
    		
    		pr.showmenu();
    		flag=1;
    		getch();
    	}
    }
    fp.close();
    if(flag==0)
    cout<<"record does not exist";
    getch();
}

//function to modify records//

void modify_product()
{
	int no,found=0;
    
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    fp.open("new.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(menu)) && found==0)
    {
    	if(pr.retitmcode()==no)
    	{
    		pr.showmenu();
    		 cout<<"\nPlease Enter The New Details of Menu"<<endl;
    		 pr.createmenu();
    		  int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(menu));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		    getch();
    	}
    }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}

//function to delete record//

void delete_product()
	{
    int no;
    
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin>>no;
    fp.open("new.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(menu)))
    {
    	if (pr.retitmcode()!=no)
    	{
    			 fp2.write((char*)&pr,sizeof(menu));
    	}
    	fp2.close();
    fp.close();
    remove("new.dat");
    rename("Temp.dat","new.dat");
    cout<<"\n\n\tRecord Deleted ..";
	getch();	
    }
}

//function to display all product price list//

void rmenu()
{
	
     fp.open("new.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
    
     }

     cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&pr,sizeof(menu)))
	 {
	   cout<<pr.retitmcode()<<"\t\t"<<pr.retitmname()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
     getch();
}

//function to place order and generating bill//

void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\nEnter The Product No. Of The Product : ";
	 cin>>order_arr[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";getch();
      cout<<"\n\n********************************INVOICE************************\n";
      cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
      for(int x=0;x<=c;x++)
      {
      	fp.open("new.dat",ios::in);
		 fp.read((char*)&pr,sizeof(menu));
		  while(!fp.eof())
			{
			if(pr.retitmcode()==order_arr[x])
			{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retitmname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
			}
				fp.read((char*)&pr,sizeof(menu));
      }
       fp.close();
	 }
       cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    getch();
}
//introduction//
void intro()
{

	
	cout<<"\t\t\tFAST FOOD MENU SELECTION\n\n";
	cout<<"made by:\n";
	cout<<"HARDIK SETHI(14BIT0044)\n";
	cout<<"ATIF ASLAM(14BIT0002)\n";
	cout<<"SAMEER SINGH(14BIT0004)\n";
	getch();
}

//administrator//
void admin_menu()
{
  
  char ch2;
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\t1.CREATE PRODUCT";
  cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t3.QUERY ";
  cout<<"\n\n\t4.MODIFY PRODUCT";
  cout<<"\n\n\t5.DELETE PRODUCT";
  cout<<"\n\n\t6.VIEW PRODUCT MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': 
	      write_product();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       
	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       display_sp(num);
	       break;
      case '4': modify_product();break;
      case '5': delete_product();break;
      case '6': rmenu();
		getch();
      case '7': break;
      default:cout<<"\a";admin_menu();
   }
}




//end of file functions//*******


int main()
{

 char ch;
  intro();
  do
    {
	  
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': 
			   place_order();
			   getch();
			   break;
		  case '2': admin_menu();
			    break;
		  case '3':
		  default :cout<<"\a";
	}
    }while(ch!='3');
	
	
	
	getch();
}
