#include<iostream>
#include<cstdlib>
#include<conio.h>//input funckija
#include<fstream>
#include<windows.h>
using namespace std;

struct tslog{
	char imeprez[50];
	int rez;
};

fstream dat;
tslog slog;
bool gameO;
const int sirina=20;
const int visina=20;
int x,y,tokenx,tokeny,rezultat,zidx,zidy,zid2x,zid2y;
enum smjer {Stop=0, Lijevo,Desno,Gore,Dolje};
smjer s;
int b;
int level=1;

void unos(char*niz){
	cin.getline(niz,50);
	if(cin.gcount()==1){
		cin.getline(niz,50);
	}
}

void setup(){
	gameO=false;
	s=Stop;
	x=sirina/2;
	y=visina/2;
	tokenx=rand()%sirina;//token x
	tokeny=rand()%visina;//token y
	zidx=rand()%sirina;//Prvi zid x
	zidy=rand()%visina;//Prvi zid y
	zidx=rand()%visina;//Drugi zid x
	zidy=rand()%sirina;//Drugi zid y
	zid2x=zidx%2;//Treci zid x
	zid2y=zidy%2;//Treci zid y
	zid2x=zidy%2;//Treci zid x
	zid2y=zidx%2;//Treci zid y
	rezultat=0;
}

void crtanje(){
	system("cls");//cleara ekran
	for(int i=0;i<sirina+2;i++){
		cout<<".";
	}
	cout<<endl;
	
	for(int i=0;i<visina;i++){
		for(int j=0;j<sirina;j++){
			if(j==0){
				cout<<".";
			}
			if(i==y && j==x){
				cout<<"O";
			}

			else if(i==tokeny && j==tokenx){
				cout<<"@";
			}
			else if(i==zidy && j==zidx){
				cout<<"#";					
			}
			else if(i==zidx && j==zidy){
				cout<<"#";					
			}
			else if(i==zid2x && j==zid2y){
				cout<<"#";					
			}
			else if(i==zid2y && j==zid2x){
				cout<<"#";					
			}
			else{
				cout<<" ";	
			}
			if(j==sirina-1){
				cout<<".";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<sirina+2;i++){
		cout<<".";
	}
	cout<<endl;
	cout<<"Skupljas @ s likom (O)"<<endl;
	cout<<"W-ides gore, A-ides levo, D-ides desno, S-ides dole"<<endl;
	cout<<"G-Igra se prekida (Game Over)"<<endl;
	cout<<"Nesmes dirnuti ograde rubova i barijere(#) jer ispadas"<<endl;
	cout<<"Level: "<<level<<endl;
	cout<<"Rezultat je: "<<rezultat<<endl;
	if(b==0){
		cout<<"Brzina lika: 10"<<endl;
	}
	else
		cout<<"Brzina lika: "<<b<<endl;
}

void input(){
	
	if(_kbhit()){//ako je gumb na tipkovnici stisnut
		switch(_getch()){
			case 'a': s=Lijevo;break;
			case 'w': s=Gore;break;
			case 's': s=Dolje;break;
			case 'd': s=Desno;break;
			case 'g': gameO=true;break;
		}
	}
}

void logic(){

	switch(s){
		case Lijevo: x--;break;
		case Desno: x++;break;
		case Gore: y--;break;
		case Dolje: y++;break;
	}
	if(x>sirina || x<0 || y>visina || y<0){
		gameO=true;
	}

	if(x==tokenx && y==tokeny){
		rezultat+=10;
		level++;
		tokenx=rand()%visina;
		tokeny=rand()%sirina;
		zidx=rand()%sirina;
		zidy=rand()%visina;
		zid2x=zidx%2;
		zid2y=zidy%2;
	}
	if(x==zidx && y==zidy){
		cout<<"Prvi"<<endl;
		gameO=true;
	}
	if(x==zidy && y==zidx){
		cout<<"Prvi"<<endl;
		gameO=true;
	}
	if(x==zid2x && y==zid2y){
		cout<<"Prvi"<<endl;
		gameO=true;
	}
	if(x==zid2y && y==zid2x){
		cout<<"Prvi"<<endl;
		gameO=true;
	}		
}	
	

void ispis(){
	dat.open("rez.dat",ios::in|ios::binary);
	while(1){
		dat.read((char*)&slog,sizeof(slog));
		if(dat.eof()) break;
		cout<<"---------------\n";
		cout<<"Igrac: "<<slog.imeprez<<endl;
		cout<<"Rezultat: "<<slog.rez<<endl;
		cout<<"---------------\n";
	}
	dat.close();dat.clear();
}


int main(){
int a;
do{
	cout<<"Izbornik"<<endl;
	cout<<"---------------\n";
	cout<<"1. Start"<<endl;
	cout<<"2. Rezultati"<<endl;
	cout<<"3. Brzina lika"<<endl;
	cout<<"4. Izlaz"<<endl;
	cout<<"---------------\n";
	cout<<"Odabir: ";cin>>a;
	switch(a){
		case 1:	dat.open("rez.dat",ios::out|ios::app|ios::binary);
				cout<<"Ime igraca: ";unos(slog.imeprez);
				setup();
				while(!gameO){
					crtanje();
					input();
					logic();
					Sleep(b);
				}
				slog.rez=rezultat;
				dat.write((char*)&slog,sizeof(slog));
				dat.close();dat.clear();break;
		case 2: ispis();break;
		case 3: 	cout<<"Promjena brzine lika"<<endl;
					cout<<"10-------50-------100"<<endl;
					cout<<"Brzo----Srednje---Sporo"<<endl;
					cout<<"Odabir(10 - 100): ";cin>>b;
					break;
	}

}while(a!=4);
 return 0;
}
