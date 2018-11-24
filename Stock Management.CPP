
 #include<conio.h>
 #include<iostream.h>
 #include<string.h>
 #include<iomanip.h>
 #include<stdio.h>
 #include<fstream.h>

 fstream file;

 void menu1(); // stock
 void menu2(); // billing

 struct date  // for keeping the current date
 {
 int dd , mm , yy ;
 };



 class item      // Class for managing all items
 {
	int qty;
	float price;
	int ino;
	char iname[20];

 public:

	item()
	{
		qty=0;
		price=0;
		ino=0;
		strcpy(iname,"NA");
	}

	void getdata()     // function to get data about an item
	{
		cout << "Enter:\nName: ";
		gets(iname);
		cout << "\nPrice: ";
		cin >> price;
		cout << "\nQuantity: ";
		cin >> qty;
	}

	 void  previous()       // function to load last record into object
	 {
		file.open("idata.dat",ios::binary|ios::in);
		file.seekg(-sizeof(item),ios::end);
		file.read((char*)this,sizeof(*this));
		file.close();
	 }

	void newitem()         // function to create a new item
	{
		previous();
		cout << "New item...\n\n";
		getdata();
		ino++;
		cout << "\n\nNew item created!\n\n";
		file.open("idata.dat",ios::binary|ios::app);
		file.write((char*)this,sizeof(*this));
		file.close();
	}

	int changeqty(int x)
	{
	qty += x;
	return qty;
	}

	int changeprice(int x)
	{
	price += x;
	return price;
	}

	int getino()
	{
	return ino;
	}

	void displayall();          // function to display all the records

	void display() // display item details
	{
		cout << setw(8) << iname << setw(5) << price << setw(3) << qty;
	}

 };

	item search(int i)              // function to search for a record and display values
	{
		item itemp;

		file.open("idata.dat",ios::in|ios::binary);

		while(file)
		{
			file.read((char *)& itemp , sizeof(item));
			if(i==itemp.getino())
			{
				return itemp;
			}
		}
		item waste;
	file.close();
	return waste;
	}

 // non inline function - class item

	void item::displayall()          // function to display all the records
	{
		previous();
		int t=ino;
		for(int i=0;i<=t;i++)
		search(i).display();
	}


 class bills      // class to manage all bills
 {
	item items[5];		// a bill is a named array of items
	item temp;
	 int bno;
	 date bdate;
	 int ino,qty;  // temporary variables

 public:

	 void getdata()             // get the item information for a bill
	 {
	 cout << "Item number:";
	 cin >> ino;
	 cout << "Quantity required";
	 cin >> qty;
	 };

	 void  previous()       // function to load last record into object
	 {
		file.open("bdata.dat",ios::binary|ios::in);
		file.seekg(-sizeof(bills),ios::end);
		file.read((char*)this,sizeof(*this));
		file.close();
	 }

	 void displaybill() // display the current bill
	 {
	 float total=0,temp;

	 for (int i=0;;i++)
	 {
		items[i].display();
		temp = items[i].changeprice(0)*items[i].changeqty(0);
		cout << temp;
		total += temp;
	 }
	 }

	 void displayall()          // display all the bills
	 {
	 previous();
	 int t=bno;
	 for (int i=0;i<t;i++)
	 {
		*this = bsearch(bno);      // reads data file , finds the bill with bno and stores the bill in the current object
		displaybill();
	 }
	 }

	 int getbno()
	 {
	 return bno;
	 }

	 void newbill();

 };

 void bills::newbill()
 {
	 previous();
	 bno++;
	 cout << "Enter new date: (dd/mm/yy)";
	 cin >> bdate.dd
	     >> bdate.mm
	     >> bdate.yy;

	 char ch='y';
	 int i=0;        // no. of items in the bill
	 cout << "Enter Item details (MAX 5 ITEMS) :\n";
	 while(ch=='y'||ch=='Y')
	 {
		getdata();
		if(qty < search(ino).changeqty(0))    // cheking if sufficient stock is available for i-th item
		{
			items[i]=search(ino);
			i++;   // item is valid
		}
		else
		{
			cout << "Insuffcient Stock!\n";
		}
		cout << "Enter more items?(y/n)";
		cin >> ch;
	 }
	 file.open("bdata.dat", ios::binary|ios::app);
	 file.write((char *)this , sizeof(*this));
	 file.close();
 }

	bills bsearch(int i)              // function to search for a record and return it
	{
		bills bill;

		file.open("bdata.dat",ios::in|ios::binary);

		while(file)
		{
			file.read((char *)& bill , sizeof(bills));
			if(i==bill.getbno())
			{
				return bill;
			}
		}
		bills waste;
	file.close();
	return waste;               // returns waste bill if bill not found
	}

 void main()
 {
	clrscr();
	item items;
	int ch;
	do{
		cout << "********MAIN MENU********\n";
		cout << "1.Stock Management\n"
		     << "2.Billing\n"
		     << "3.Exit";
		cin >> ch;
		switch(ch){
		case 1:
			menu1();
		break;

		case 2:
			menu2();
		break;
		default:
			cout << "Invalid choice! Please try again...\n";
		}
	}while(ch!=0);
	getch();
}