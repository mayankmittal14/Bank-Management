#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>

// This function is used to add graphics in the program
void printmsg(){
	int gdriver = DETECT, gmode, i;
	initgraph(&gdriver, &gmode, "C:\\Turboc3\\BGI");

	setcolor(10);
	cprintf("Banking project");

	settextstyle(4, 0, 9);
	outtextxy(20, 100, "Banking project");

	settextstyle(7, 0, 4);
	outtextxy(30, 300, "Made by:");
	outtextxy(20, 350, "Mayank Mittal");

	textcolor(128);
	delay(2);
}

// Main class
class cus{
public:
	char name[20];
	float blnc;
	int ac_no;
	void input();
};

// This function is used to add account
void cus::input(){
	cout << "\n\t Name: ";
	cin >> name;

	cout << "\n\t Account no: ";
	cin >> ac_no;

	cout << "\n\t Balance: ";
	cin >> blnc;
};


class acc : public cus{
public:
	float intrst;
	int tim;
	void add();
	void subtract();
	void output();
	acc();
};


acc::acc(){
	tim = 0;
	intrst = 0;
}

// This function is used to see the details of existing account
void acc::output(){
	cout << "\n\t Name: " << name;
	cout << "\n\t Total balance: " << blnc;
	cout << "\n\t Interest: " << intrst;
}

// This function is used to add money to the account
void acc::add(){
	int i;
	tim++;
	cout << "\n\t Amount: ";
	cin >> i;
	intrst = intrst + blnc * tim * .08;
	blnc = blnc + intrst + i;
};

// This function is used to withdraw money from the account
void acc::subtract(){
	int j;
	cout << "\n\t Amount: ";
	cin >> j;
	blnc = blnc - j;
};

// Class for loan
class loan : public acc{
public:
	float lon;
	loan(){
		lon = 0;
	}

	void payloan();
	void getloan();
};

// This function is used to get loan
void loan::getloan(){
	int l;
	if(lon == 0){
		cout << "\n\t Enter loan: ";
		cin >> l;

		if(l <= (l * 1.50)){
			cout << "\n\t You can get loan";
			lon = l + l * 0.1;
		}
		else{
			cout << "\n\t Sorry.";
			lon = 0;
		}
	}
	else
		cout << "\n\t You have previous loan.";
}

// This function is used to pay loan
void loan::payloan(){
	int m;
	if(lon == 0)
		cout << "\n\t You have no loan.";
	else{
		cout << "\n\t You have to pay " << lon;
		cout << "\n\t Enter your payment: ";
		cin >> m;

		lon = lon - m;
		if(lon <= 0){
			cout << "\n\t OK. Your loan paid.";
			lon = 0;
		}
		else
			cout << "\n\t Loan to be paid = " << lon;
	}
}

// Function to see information of existing account
void show(){
	loan a;
	int i, found = 0;

	fstream file;
	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0);

	cout << "\n\t Insert account no: ";
	cin >> i;

	for( ; ; ){
		file.read((char*)&a, sizeof(a));
		if(!file)
			break;

		if(i == a.ac_no){
			a.output();
			found = 1;
			break;
		}
	}

	if(found != 1){
		cout << "\n\t Not exist.";
	}

	file.close();
	getch();
};

// Function to deposit
void add_a(){
	loan a;
	fstream file;
	int i, k, found = 0;

	cout << "\n\t Insert account no: ";
	cin >> i;

	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0);

	for(k=0; ; k++){
		file.read((char*)&a, sizeof(a));

		if(!file)
			break;
		
		if(i == a.ac_no){
			a.add();
			found = 1;
			break;
		}
	}

	if(found == 1){
		int n = k * sizeof(a);
		file.seekp(n);
		file.write((char *)&a, sizeof(a));
		cout << "\n\t Information added.....";
		file.close();
	}
	else
		cout << "\n\t Account not exist.....";

	getch();
};

void subtract_a(){
	loan a;
	fstream file;
	int i, k, found = 0;

	cout << "\n\t Insert account no: ";
	cin >> i;

	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);
	file.seekg(0);

	for(k = 0;; k++){
		file.read((char*)&a, sizeof(a));
		if(!file)
			break;
		
		if(i == a.ac_no){
			a.subtract();
			found = 1;
			break;
		}
	}

	if(found == 1){
		int n = k * sizeof(a);
		file.seekp(n);
		file.write((char *)&a, sizeof(a));
		
		cout << "\n\t Information added.....";
		file.close();
	}
	else
		cout << "\n\t Account not exist.....";

	getch();
};

// Function to delete account
void dlt(){
	loan a[100];
	fstream file;
	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);
	int i, l, found = 0;
	cout << "\n\t Insert account no: ";
	cin >> i;
	file.seekg(0);

	for(int k = 0; ; k++){
		file.read((char*)&a[k], sizeof(a[k]));

		if(!file)
			break;
	}

	file.close();
	
	file.open("final.dat", ios::out | ios::binary);
	for(l = 0; l < k; l++){
		if(i == a[l].ac_no){
			cout << "\n\t Account deleted.";
			found = 1;
		}
		else
			file.write((char *)&a[l], sizeof(a[l]));
	}

	if(found == 0)
		cout << "\n\t Account not found";
	
	file.close();
	getch();
};


void loanf(){
	loan a;
	fstream file;
	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);

	int i, found = 0;
	cout << "\n\t Account no: ";
	cin >> i;

	file.seekg(0);

	for(int k = 0;; k++){
		file.read((char*)&a, sizeof(a));

		if(!file)
			break;

		if(i == a.ac_no){
			a.getloan();
			int n = k * sizeof(a);

			file.seekp(n);
			file.write((char *)&a, sizeof(a));

			found = 1;
			break;
		}
	}

	file.close();

	if(found == 0)
		cout << "\n\t This account is not exist in file.";

	getch();
};


void pay(){
	loan a;
	fstream file;
	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);

	int i, found = 0;
	cout << "Account no: ";
	cin >> i;

	file.seekg(0);

	for(int k = 0; ; k++){
		file.read((char*)&a, sizeof(a));

		if(!file)
			break;

		if(i == a.ac_no){
			a.payloan();
			int n = k * sizeof(a);

			file.seekp(n);
			file.write((char *)&a, sizeof(a));

			found = 1;
			break;
		}
	}

	if(found == 0)
		cout << "\n\t This account is not exist in file.";

	file.close();
	getch();
};


void inputdata(loan a){
	fstream file;
	file.open("final.dat", ios::ate | ios::in | ios::out | ios::binary);
	file.seekp(0, ios::end);
	file.clear();
	file.write((char *)&a, sizeof(a));
	file.close();
}

//--//--//--//--/MAIN PROGRAM/--//--//--//--//
int main(){
	printmsg();
	getch();
	clrscr();
	int i;

	for( ; ; ){
		loan a;
		clrscr();

		cout << "\n\n\t<<<<<<<<<<<<<<<<<< M E N U >>>>>>>>>>>>>>>>>>>>>>>>\n";
		cout << setw(57) << "       ___________________________________________________\n";
		cout << setw(57) << "       ___________________________________________________\n";
		cout << setw(57) << "       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\n\t 1. OPEN NEW ACCOUNT";
		cout << "\n\t 2. INFORMATION OF EXISTING ACCOUNT";
		cout << "\n\t 3. DEPOSIT";
		cout << "\n\t 4. WITHDRAW";
		cout << "\n\t 5. DELETE ACCOUNT";
		cout << "\n\t 6. LOAN";
		cout << "\n\t 7. PAY";
		cout << "\n\t 8. EXIT";
		cout << "\n\t Your Choice: ";
		cin >> i;
		clrscr();

		switch (i){
		case 1:
			a.input();
			inputdata(a);
			cout << "\n\t Account created.....";
			getch();
			break;

		case 2:
			show();
			break;

		case 3:
			add_a();
			break;

		case 4:
			subtract_a();
			break;

		case 5:
			dlt();
			break;

		case 6:
			loanf();
			break;

		case 7:
			pay();
			break;

		default:
			setcolor(3);
			settextstyle(7, 0, 5.5);
			outtextxy(50, 200, "THANKS FOR VISITING");
			getch();
			exit(0);
		}
	}

	return 0;
}