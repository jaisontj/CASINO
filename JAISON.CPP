# include <iostream.h>
# include <conio.h>
# include <stdio.h>
# include <string.h>
# include <dos.h>
# include <graphics.h>
# include <stdlib.h>
# include <fstream.h>

//*********************************************************************************
//BitMap Structure and functions------------------------------------------------------
//*****************************************************************************
struct A
{
	char type[2];                 /* Magic identifier            */
	unsigned long size;                       /* File size in bytes          */
	unsigned short int reserved1, reserved2;
	unsigned long offset;                     /* Offset to image data, bytes */
};
A HEADER,HEADER1;

struct B
{
	unsigned long size;               /* Header size in bytes      */
	unsigned long width,height;                /* Width and height of image */
	unsigned short int planes;       /* Number of colour planes   */
	unsigned short int bits;         /* Bits per pixel            */
	unsigned long compression;        /* Compression type          */
	unsigned long imagesize;          /* Image size in bytes       */
	unsigned long xresolution,yresolution;     /* Pixels per meter          */
	unsigned long ncolours;           /* Number of colours         */
	unsigned long importantcolours;   /* Important colours         */
};
B INFOHEADER,INFOHEADER1;		//This Global Function is used for the resolution of the bitmap. You can set the return value either 1,2 or 3. For me 3 is the best combination.

huge DetectSvga()
{
   return 4;
}

void Show(char a[10],int x,int y)
{
fstream File;		//Here you have to define the path of the bitmap file. Like according to this example i have to open one Board1.bmp file. So write you bitmap file path here.
int XCor=x,YCor=y;
File.open(a,ios::in);
unsigned char Ch;
File.read((char*)&HEADER,14); //This is the header part of the Bitmap. It always looks like same. Don't change the content hear. The value remains 14 here.
File.read((char*)&INFOHEADER,40); //This is another part of the bitmap, here also the value remains same like 40 here.
unsigned int i;
char ColorBytes[4];
char*PaletteData;
PaletteData=new char[256*3];
if(PaletteData)//if memory allocated successfully
{
	//read color data
for(i=0;i<256;i++)
{
	File.read(ColorBytes,4);
	PaletteData[(int)(i*3+2)]=ColorBytes[0]>>2;
	PaletteData[(int)(i*3+1)]=ColorBytes[1]>>2;
	PaletteData[(int)(i*3+0)]=ColorBytes[2]>>2;
}
outp(0x03c8,0);      //tell DAC that data is coming
for(i=0;i<256*3;i++) //send data to SVGA DAC
{
	outp(0x03c9,PaletteData[i]);
}
delete[]PaletteData;
}
for(i=0;i<INFOHEADER.height;i++)       //This for loop is used to display the bitmap.
{
	for(int j=0;j<INFOHEADER.width;)
	{
		File.read(&Ch,1); // Here Ch reads the color of your bitmap.
		putpixel(XCor+j++,YCor+INFOHEADER.height-i-1,Ch); //XCor and YCor are the X and Y cordinates. It depends upon you.
	}
}
File.close();
}

void black()
{
setfillstyle(0,0);
bar(0,0,10000,1000);
}
//*************************************************************************************
//****************LOADING SCREENS*********************************************************
//*************************************************************************************
void loginloading()
{
settextstyle(7,0,1);
for(int i=0;i<3;i++)
	{
	setcolor(255);
	outtextxy(700,700,"LOGGING IN....");
	delay(500);
	setcolor(0);
	outtextxy(700,700,"LOGGING IN....");
	delay(500);
	}
}

void billloading()
{
setcolor(87);
setfillstyle(1,255);
settextstyle(7,0,2);
rectangle(350,700,850,740);
for(int i=1;i<501;i++)
	{
	delay(10);
	bar(350,700,350+i,740);
	outtextxy(460,715,"PROCESSING BILL");
	}
}

void gameloading()
{
for(int j=0,x=60;j<2;j++,x-=20)
{
setcolor(209);
for(int i=0;i<30;i++)
	{
	delay(x);
	circle(950,700,i);
	}
setcolor(0);
for(i=30;i>-1;i--)
	{
	delay(x);
	circle(950,700,i);
	}
}
}

void savingloading()
{
settextstyle(1,0,2);
setfillstyle(1,255);
for(int i=0;i<361;i++)
	{
	delay(10);
	setcolor(1);
	outtextxy(570,690,"SAVING");
	setcolor(0);
	pieslice(600,700,0,i,50);
	}
setfillstyle(1,0);
for(i=0;i<300;i++)
	{
	delay(10);
	setcolor(1);
	outtextxy(570,690,"SAVING");
	setcolor(0);
	pieslice(600,700,0,i,50);
	}
}

void ending()
{
black();
setcolor(255);
outtextxy(100,100,"A PROJECT BY ,");
outtextxy(300,200,"JAISON.J.TITUS");
outtextxy(300,250,"NIKHIL RAJ");
outtextxy(300,300,"KASIM NAZEER");
settextstyle(7,0,2);
outtextxy(10,500,"OUR SPECIAL THANKS TO SHABNAM MA'AM WHO HELPED US THROUGHOUT THE PROJECT");
getch();
setcolor(RED);
setfillstyle(0,0);
for(int i=10,x=800;i<=400;i++,x--)
	{
	delay(0);
	line(1,i,1100,i);
	bar(1,1,1100,i-1);

	line(1,x,1100,x);
	bar(1,800,1100,x+1);
	}
bar(10,100,1500,800);
line(10,400,900,400);
for(i=10,x=1000;i<=500;i++,x--)
	{
	delay(2);
	setcolor(0);
	line(0,400,i,400);
	line(900,400,x,400);
	}
}

//*******************************************************************************
//********************USER INFORMATION , USER CASH ******************************
//*******************************************************************************
struct user_cash
{
long int cash;
int no;
}ucash;

class user
{
char username[20],pass[20];
public:
	void start()
	{
	char a[2][20]={"REGISTER","LOGIN"};
	int pos[2]={360,550};
	Show("lasvegas.bmp",10,10);
	setcolor(15);
	settextstyle(7,0,3);
	outtextxy(50,50,"THE NIKSON.K GRAND WELCOMES YOU , HOPE YOU ENJOY YOUR STAY");
	getch();
	black();
	abc1:
		ucash.cash=1000;
	Show("logo.bmp",300,300);
			settextstyle(7,0,3);
			outtextxy(352,586,"THE NIKSON.K GRAND ");

			setcolor(RED);
			settextstyle(1,0,4);
			outtextxy(200,80,"DO YOU WANT TO REGISTER OR LOGIN?");

		if(highlighter1(a,2,pos,120)==0)
			{
				setcolor(BLUE);
				settextstyle(1,0,2);
				outtextxy(50,200,"ENTER DESIRED USERNAME :");
				outtextxy(50,250,"ENTER DESIRED PASSWORD :");
				gotoxy(44,14);
				gets(username);
				gotoxy(44,17);
				int i=0,val;
			do
				{
					pass[i]=getch();
					val=pass[i];
					if(val!=13)
					cout<<"*";
					i++;
				}while(val!=13);
		black();
		gotoxy(1,18);
		ofstream f,f1;
		f.open("user_info.txt",ios::app);
		f.seekp(0,ios::end);
		f.write((char*)&users,sizeof(users));
		f.close();
		f1.open("user_cash.txt",ios::app);
		f1<<ucash.cash<<"\n";
		f1.close();
		cout<<"USERNAME          : "<<username;
		cout<<"\nPASSWORD          : "<<pass;
		cout<<"\nSTARTING CASH     : "<<ucash.cash;
		gotoxy(10,23);
		cout<<"REMEMBER YOUR USERNAME AND PASSWORD !!\n\t TO LOGIN LATER WITH THE SAME\n\nEXITING....";
		cout<<"\nPRESS ENTER";
		getch();
		users.save();
		exit(0);
		}
	else	{
		char username1[20],pass1[20];
		int flag=0;
		ifstream f1,f2;
		f1.open("user_info.txt");
		f2.open("user_cash.txt");
		setcolor(BLUE);
		settextstyle(1,0,2);
		outtextxy(200,200,"USERNAME :");
		outtextxy(200,250,"PASSWORD :");
		gotoxy(44,14);
		gets(username1);
		gotoxy(44,17);
		int i=0,val,correctpass=0;
		do
		{
			pass1[i]=getch();
			val=pass1[i];
			if(val!=13)
				cout<<"*";
			i++;
		}while(val!=13);
		val=0;
		ucash.no=0;
		loginloading();
		while(!f1.eof())
			{
			ucash.no++;
			f2>>ucash.cash;
			f1.seekg(val);
			val+=40;
			f1.read((char*)&users,sizeof(users));
			if(i-1==strlen(pass))
			for(int k=0;k<strlen(pass);k++)
				{

				if(pass1[k]!=pass[k])
					{
					break;
					correctpass=0;
					}
				else correctpass=1;
				}
			if(strcmp(username,username1)==0&&correctpass==1)
				{
				viewprofile();
				flag=1;
				break;
				}
			}
		if(flag==0)
			{
			black();
			setcolor(34);
			int option;
			outtextxy(100,50,"USERNAME OR PASSWORD IS INCORRECT OR HAVE YOU NOT REGISTERED ? ");
			outtextxy(150,120,"PRESS ENTER TO LOGIN/REGISTER OR ESC TO EXIT");
			option=getch();
			black();
			if(option!=27)
				goto abc1;
			else if(option==27)
				exit(0);
			}
		}
	}

	void profile()
	{
	setcolor(255);
	line(220,0,220,800);
	setcolor(GREEN);
	settextstyle(4,0,3);
	outtextxy(10,20,"PROFILE INFO.");
	setcolor(RED);
	settextstyle(4,0,4);
	outtextxy(10,150,"NAME : ");
	outtextxy(10,200,"CASH : ");
	setcolor(BLUE);
	settextstyle(7,0,3);
	outtextxy(120,150,username);
	gotoxy(20,15);
	cout<<ucash.cash;
	}

	int viewprofile()
	{
	black();
	setcolor(MAGENTA);
	settextstyle(1,0,4);
	outtextxy(100,100,"PROFILE INFORMATION");
	setcolor(BLUE);
	settextstyle(5,0,4);
	outtextxy(100,250,"USERNAME : ");
	outtextxy(100,300,"PASSWORD : ");
	outtextxy(100,350,"CASH     : ");
	setcolor(RED);
	settextstyle(4,0,4);
	outtextxy(350,248,username);
	outtextxy(350,300,pass);
	gotoxy(44,24);
	cout<<ucash.cash;
	outtextxy(100,500,"PRESS ANY KEY TO GO BACK");
	getch();
	return 1;
	}
	void save()
	{
	Show("logo.bmp",500,200);
	savingloading();
	long int cash,cash1;
	int i=1,j=0;
	ifstream f1;
	ofstream f2;
	f1.open("user_cash.txt");
	f1.seekg(0);
	f2.open("new.txt");
	f2.seekp(0);

	while(!f1.eof())
		{
		j++;
		f1>>cash1;
		}
	f1.close();
	f1.open("user_cash.txt");
	for(int k=1;k<j;k++)
		{
		f1>>cash;
		if(i==ucash.no)
			{f2<<ucash.cash<<"\n";
			cout<<ucash.cash;}
		else f2<<cash<<"\n";

		i++;
		}
	remove("user_cash.txt");
	rename("new.txt","user_cash.txt");
	f1.close();
	f2.close();
	}
}users;

//**************************************************************************
//*******************CLASS TO READ FILES************************************
//**************************************************************************

class readfile
{
public:
char file_info[80];
}obj;

//**************************************************************************
//***********************apartments*****************************************
//**************************************************************************
class apartments
{
int x,ch;
public:

void display()
{
char apart_info[3][20]={"deluxe.txt","premiere.txt","glamour.txt"};
char a[3][20]={"DELUXE SUITS","PREMIERE SUITS","GLAMOUR SUITS"};
x=1;
abc:
settextstyle(7,0,2);
setcolor(1);
do
{
black();
ifstream f;
	f.open(apart_info[x-1]);
	gotoxy(10,5);
	cout<<"\n\n\n";
	while(f)
		{
		 f.read((char*)&obj,sizeof(obj));
		 cout<<obj.file_info;
		}
	f.close();
if(x==1)
	{
	Show("deluxe.bmp",500,100);
	setfillstyle(1,250);
	}
else setfillstyle(1,0);
bar(703,603,902,647);
rectangle(700,600,905,650);
rectangle(703,603,902,647);
outtextxy(710,610,a[0]);
if(x==2)
	{
	Show("premiere.bmp",500,100);
	setfillstyle(1,250);
	}
else	setfillstyle(1,0);
bar(703,658,902,702);
rectangle(700,655,905,705);
rectangle(703,658,902,702);
outtextxy(705,665,a[1]);
if(x==3)
	{
	Show("glamour.bmp",500,100);
	setfillstyle(1,250);
	}
else 	setfillstyle(1,0);
bar(703,718,902,762);
rectangle(700,715,905,765);
rectangle(703,718,902,762);
outtextxy(710,725,a[2]);
ch=getch();
	if(ch==80)
		if(x>2)
			x=1;
		else x++;
	if(ch==72)
		if(x<1)
			x=3;
		else x--;
	if(ch==27)
		mainmenu();
}while(ch!=13);
char ans[2][20]={"YES","NO"};
int px[2]={120,200};
char tamount[3][10]={"110","330","380"};
char amount[3][10]={"90","310","360"};
outtextxy(100,600,"IS THIS TO YOUR LIKING?");
if(highlighter1(ans,2,px,650)==1)
	goto abc;
black();
int flag=0;
if(x==1)
	if(ucash.cash-110<0)
		flag=1;
if(x==2)
	if(ucash.cash-330<0)
		flag=1;
if(x==3)
	if(ucash.cash-=380<0)
		flag=1;
if(flag==1)
	{
	outtextxy(200,100,"YOU DO NOT HAVE ENOUGH MONEY");
	getch();
	goto abc;
	}
setcolor(34);
settextstyle(7,0,2);
outtextxy(100,100,"BASED ON OUR POLICY , A GUEST MUST DEPOSIT A FIXED AMOUNT");
outtextxy(100,130,"FOR A ONE NIGHT STAY AND THEN FOR EACH EXTRA DAY HE WILL HAVE TO");
outtextxy(100,160,"PAY EITHER ON THE PARTICULAR DAY OR ON THE PREVIOUS DAY");
setcolor(67);
outtextxy(100,250,"YOU HAVE CHOOSEN : ");
outtextxy(100,350,"TOTAL AMOUNT :  ");
outtextxy(100,450,"DO YOU WANT TO CONTINUE? ");
setcolor(1);
outtextxy(350,250,a[x-1]);
outtextxy(350,350,tamount[x-1]);
if(highlighter1(ans,2,px,500)==1)
	goto abc;
billloading();
black();
setcolor(255);
setfillstyle(1,255);
rectangle(200,50,750,650);
bar(204,54,746,646);
setcolor(0);
settextstyle(7,0,3);
outtextxy(210,75,"APARTMENT CLASS :");
outtextxy(210,105,"NO. OF NIGHTS     :");
outtextxy(210,135,"RATE               :");
outtextxy(210,165,"SERVICE CHARGE  :");
outtextxy(210,195,"TOTAL AMOUNT     :");
outtextxy(500,75,a[x-1]);
outtextxy(500,105,"1");
outtextxy(500,135,amount[x-1]);
outtextxy(500,165,"20");
outtextxy(500,195,tamount[x-1]);
outtextxy(210,280,"!!HOPE YOU ENJOY YOUR STAY!!");
Show("logo1.bmp",350,330);
if(x==1)
	ucash.cash-=110;
if(x==2)
	ucash.cash-=330;
if(x==3)
	ucash.cash-=380;
getch();
mainmenu();
}
}apart;
//******************************************************************************************
//****************************HORIZONTAL HIGHLIGHTER****************************************
//******************************************************************************************

int highlighter1(char a[][20],int n,int posh[],int posv)  //a=the wrds,n=no of wrds,posh=horizontal pos,posv=vertical pos
{
int i;
int ch,flag;
setcolor(4);
settextstyle(4,0,4);
for(i=0;i<n;i++)
outtextxy(posh[i],posv,a[i]);
setcolor(RED);
flag=0;
	do
	{

	setcolor(YELLOW);
	for(i=0;i<n;i++)
	outtextxy(posh[i],posv,a[i]);
	if(ch==77)
		{
		if(flag==n-1)
			;
		else	flag++;
		setcolor(BLACK);
		for(i=0;i<n;i++)
			{
			if(i==flag)
				continue;
			outtextxy(posh[i],posv,a[i]);
			}
		}
	if(ch==75)
		{
		if(flag==0)
			;
		else	flag--;
		setcolor(BLACK);
		for(i=0;i<n;i++)
			{
			if(i==flag)
				continue;
			outtextxy(posh[i],posv,a[i]);
			}
		}
	ch=getch();
	}while(ch!=13);
return flag;
}

//*******************************************************************************************
//**************************************GAMES************************************************
//*******************************************************************************************
class twentyone
{
long int buyin,stake,winings;
	void values()
	{
	setfillstyle(1,0);
	bar(200,10,500,50);
	gotoxy(35,1);
	cout<<"AMOUNT   : "<<buyin;
	gotoxy(35,2);
	cout<<"STAKE    : "<<stake;
	gotoxy(35,3);
	cout<<"WINNINGS : "<<winings;
	}
	int options(char deal[2][10])
	{
	int j=520,ch;
	do
	{
	for(int i=0,k=520;i<2;i++,k+=100)
		{
		setcolor(0);
		if(k==j)
			setfillstyle(1,67);
		else	setfillstyle(1,255);
		bar(k,500,k+60,530);
		rectangle(k,500,k+60,530);
		outtextxy(k+5,505,deal[i]);

		}
	ch=getch();
	if(ch==77)
		{
		if(j==520)
			{
			j=620;
			i=1;
			}
		else
			{
			j=520;
			i=0;
			}
	       }
	if(ch==75)
		{
		if(j==520)
			{
			j=620;
			i=1;
			}
		else
			{
			j=520;
			i=0;
			}
	       }
	}while(ch!=13);
	return j;
	}

	int evaluatepoint(int p,int point)
	{
	if(p>=0&&p<=3)
	{
	if(point+11>21)
		return 1;
	if(point+11<21||point+11==21)
		return 11;
	}
	if(p>=4&&p<=19)
		return 10;
	if(p>=20&&p<=23)
		return 9;
	if(p>=24&&p<=27)
		return 8;
	if(p>=28&&p<=31)
		return 7;
	if(p>=32&&p<=35)
		return 6;
	if(p>=36&&p<=39)
		return 5;
	if(p>=40&&p<=43)
		return 4;
	if(p>=44&&p<=47)
		return 3;
	if(p>=48&&p<=51)
		return 2;

       }

       int win(int bust,int bustd,int point,int pointd)
       {
       if(bust==1&&bustd==0)
		return 0;
       if(bust==0&&bustd==1)
		return 1;
       if(bust==0&&bustd==0)
	{
	if(point==21)
		return 3;
	if(point>pointd)
		return 1;
	if(pointd==21||pointd>point)
		return 0;
	if(pointd==point)
		return 2;
	}
       }
public:
	void blackjack()
	{
	int i,j,k=0,cont=0;
	char card_pic[54][10]={"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp","11.bmp","12.bmp","13.bmp","14.bmp","15.bmp","16.bmp","17.bmp","18.bmp","19.bmp","20.bmp","21.bmp","22.bmp","23.bmp","24.bmp","25.bmp","26.bmp","27.bmp","28.bmp","29.bmp","30.bmp","31.bmp","32.bmp","33.bmp","34.bmp","35.bmp","36.bmp","37.bmp","38.bmp","39.bmp","40.bmp","41.bmp","42.bmp","43.bmp","44.bmp","45.bmp","46.bmp","47.bmp","48.bmp","49.bmp","50.bmp","51.bmp","52.bmp","53.bmp","54.bmp"};
	abc:
	black();
	setcolor(56);
	settextstyle(7,0,4);
	outtextxy(200,400,"MINIMUM BUYIN : 50");
	outtextxy(200,450,"MAXIMUM BUYIN : 5000");
	setcolor(BLUE);
	settextstyle(7,0,4);
	outtextxy(150,100,"!!!!BUY INTO THE GAME!!!!");
	setcolor(255);
	rectangle(350,150,450,200);
	setcolor(BROWN);
	settextstyle(3,0,4);
	outtextxy(120,150,"Enter Amount :");
	gotoxy(46,12);
	cin>>buyin;            //BUYIN IN
	if(buyin<50||buyin>5000)
		{
		black();
		setcolor(34);
		settextstyle(7,0,4);
		black();
		outtextxy(100,200,"VALUE NOT WITHIN BUYIN LIMIT");
		char decide[2][20]={"BACK TO GAME SELECT","ENTER NEW AMOUNT"};
		int posh[2]={150,650};
		if(highlighter1(decide,2,posh,350)==0)
			if(games()==3)
				mainmenu();
		else goto abc;
		}
	if(ucash.cash<buyin)
		{
		black();
		setcolor(89);
		settextstyle(8,0,2);
		outtextxy(100,300,"YOU DO NOT HAVE ENOUGH MONEY TO BUY IN WITH THIS AMOUNT");
		char decide[2][20]={"BACK TO GAME SELECT","ENTER NEW AMOUNT"};
		int posh[2]={150,650};
		if(highlighter1(decide,2,posh,350)==0)
			if(games()==3)
				mainmenu();
		else goto abc;
	      }
	ucash.cash-=buyin;
	pqr:
	stake=0;
	winings=0;
	black();
	Show("bj2.bmp",240,80);
	values();
	int poschips[5]={396,466,530,593,657};
	char chips[5][5]={"1","5","25","100","1000"};
	int color[5]={2,5,4,1,3};
	int ch,chip=-1,barc=255,flag=0;
	settextstyle(1,0,2);
	outtextxy(300,735,"PRESS ESC TO GO TO GAME SELECT");
	do
	{
	flag=0;
	xyz:
	for(i=400,k=0;i<700;i+=70,k++)
	{
		setcolor(0);
		setfillstyle(1,color[k]);
		for(j=0;j<360;j+=90)
			pieslice(i,650,j,j+90,25);
		if(chip!=k)
		{
			setcolor(255);
			setfillstyle(1,255);
			pieslice(i,650,0,360,20);
		}

	}
	setcolor(0);
	setfillstyle(1,barc);
	settextstyle(1,0,2);
	bar(520,695,600,730);
	outtextxy(535,700,"DONE");
	settextstyle(1,0,1);
	setcolor(0);
	for(i=0;i<5;i++)
	outtextxy(poschips[i],637,chips[i]);
		do
		{
		setcolor(255);
		outtextxy(250,600,"CHOOSE YOUR CHIPS: ");
		ch=getch();
			if(ch==77)
			{
				if(chip>3)
					chip=0;
				else
					chip++;
				barc=255;
				goto xyz;
			}
			if(ch==75)
			{
				if(chip<=0)
					chip=4;
				else
					chip--;
				barc=255;
				goto xyz;
			}
			if(ch==80)
			{
				chip=20;
				barc=90;
				goto xyz;
			}
			if(ch==27)
			{
			if(games()==3)
				mainmenu();
			chip=-5;

			}
		}while(ch!=13);


	switch(chip)
	{
	case 0:{
		if(buyin-1<0)
			flag=1;
		else
			{
			buyin-=1;
			stake+=1;
			}
		break;
		}
	case 1:{
		if(buyin-5<0)
			flag=1;
		else
			{
			buyin-=5;
			stake+=5;
			}
		break;
		}
	case 2:{
		if(buyin-25<0)
			flag=1;
		else
			{
			buyin-=25;
			stake+=25;
			}
		break;
		}
	case 3:{
		if(buyin-100<0)
			flag=1;
		else
			{
			buyin-=100;
			stake+=100;
			}
		break;
		}
	case 4:{

		if(buyin-1000<0)
			flag=1;
		else
			{
			buyin-=1000;
			stake+=1000;
			}
		break;
		}
	case -5:{
		exit(0);
		}

	}
	if(stake==0)
		{
		setcolor(3);
		settextstyle(4,0,4);
		outtextxy(500,20,"YOU HAVE TO PLACE A BET");
		delay(2000);
		setcolor(0);
		outtextxy(500,20,"YOU HAVE TO PLACE A BET");
		goto xyz;
		}
	values();
	if(flag==1)
		{
		setcolor(3);
		outtextxy(300,670,"YOU DO NOT HAVE ENOUGH MONEY");
		delay(2000);
		setcolor(0);
		outtextxy(300,670,"YOU DO NOT HAVE ENOUGH MONEY");
		}
	else    if(chip!=20)
		{
		setcolor(0);
		setfillstyle(1,color[chip]);
		srand(chip+5);
		int x=random(100);
		for(j=0;j<360;j+=90)
			sector(560+x,440,j,j+90,20,15);
			setcolor(color[chip]);
			setfillstyle(2,color[chip]);
			sector(560+x,440,0,360,15,10);
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(j=0;j<360;j+=90)
			sector(580+x,280,j,j+90,20,15);
			setcolor(color[chip]);
			setfillstyle(2,color[chip]);
			sector(580+x,280,0,360,15,10);
		}
	}while(chip!=20);
	char deal[2][10]={"CLEAR","DEAL"};
	char deal1[2][10]={"HIT","STAND"};

	if(options(deal)==520)
		{
		buyin+=stake;
		stake=0;
		goto pqr;
		}
	int point=0,p,pointd=0,bust=0,bustd=0;
	i=600;
	j=0;
		randomize();
	p=random(52);
	point+=evaluatepoint(p,point);
	Show(card_pic[p],i,380);
	delay(200);
	p=random(52);
	pointd+=evaluatepoint(p,pointd);
	Show(card_pic[p],500,150);
	delay(200);
	j=rand();
	do
	{
	i+=30;
	srand(j);
	p=random(52);
	point+=evaluatepoint(p,point);
	Show(card_pic[p],i,380);
		delay(100);
	Show("01.bmp",530,150);
	if(point==21)
		{
		settextstyle(4,0,4);
		setcolor(0);
		gotoxy(70,25);
		cout<<point;
		break;
		}
	if(point>21)
		{
		settextstyle(4,0,4);
		setcolor(RED);
		gotoxy(70,25);
		cout<<point;
		bust=1;
		break;
		}
	gotoxy(70,25);
	cout<<point;
	while(!kbhit())
		j++;
	}while(options(deal1)==520);

	i=530;
	do
	{
	delay(300);
	p=random(52);
	pointd+=evaluatepoint(p,pointd);
	Show(card_pic[p],i,150);
	if(pointd==21)
		{
		settextstyle(4,0,4);
		setcolor(0);
		gotoxy(55,12);
		cout<<pointd;
		break;
		}
	if(pointd>21)
		{
		settextstyle(4,0,4);
		setcolor(RED);
		gotoxy(55,12);
		cout<<point;
		bustd=1;
		break;
		}
	i+=30;
	}while(pointd<=16);
	gotoxy(55,12);
	cout<<pointd;
	p=win(bust,bustd,point,pointd);
	setcolor(0);
	setfillstyle(1,RED);
	settextstyle(7,0,3);
	if(p==0)
		{
		outtextxy(550,380,"YOU LOST");
		winings=0;
		stake=0;
		}
	if(p==1)
		{
		outtextxy(550,150,"BUSTED");
		outtextxy(550,380,"YOU WON");
		winings=2*stake;
		stake=0;
		}
	if(p==2)
		{
		outtextxy(550,380,"GAME TIED");
		winings=stake;
		stake=0;
		}
	if(p==3)
		{
		outtextxy(550,380,"BLACK JACK");
		outtextxy(550,380,"!!YOU WIN!!");
		winings=3*stake;
		stake=0;
		}
	buyin+=winings;
	values();
	getch();
	char a[2][20]={"YES","NO"};
	int posx[2]={550,650};
	setfillstyle(1,0);
	bar(280,150,900,500);
	setcolor(255);
	settextstyle(4,0,4);
	outtextxy(300,250,"DO YOU WANT TO PLAY AGAIN ??");
	if(highlighter1(a,2,posx,400)==0)
		{
		if(buyin>50)
			goto pqr;
		else
			{
			ucash.cash+=buyin;
			buyin=0;
			stake=0;
			winings=0;
			goto abc;
			}
		}
	else {
		ucash.cash+=buyin;
		if(games()==3)
			mainmenu();
			exit(0);
		}
	 }
}casino;
//-----------------------------------------------------------------------------------
//--ROULETTE--------------------------------------------------------------------------
//----------------------------------------------------------------------------------

class roulette_game
{
long int buyin,stake,winings;
	void values()
	{
	setfillstyle(1,0);
	bar(220,0,800,60);
	gotoxy(35,1);
	cout<<"AMOUNT   : "<<buyin;
	gotoxy(35,2);
	cout<<"STAKE    : "<<stake;
	gotoxy(35,3);
	cout<<"WINNINGS : "<<winings;
	gotoxy(1,1);
	}
	void win(int no[100],int chipno[100],int num,int n)
	{
	int flag=0;
	for(int i=0;i<num;i++)
		if(no[i]==n)
			    switch(chipno[i])
				{
				case 0:{
					winings+=37*1;
					break;
					}
				case 1:{
					winings+=37*5;
					break;
					}
				case 2:{
					winings+=37*25;
					break;
					}
				case 3:{
					winings+=37*100;
					break;
					}
				case 4:{
					winings+=37*1000;
					break;
					}
				}
	for(i=0;i<num;i++)
		if(no[i]==37&&n%2!=0||no[i]==38&&n%2==0||no[i]==39&&n%2!=0||no[i]==40&&n%2==0)
			switch(chipno[i])
				{
				case 0:{
					winings+=3;
					break;
					}
				case 1:{
					winings+=3*5;
					break;
					}
				case 2:{
					winings+=3*25;
					break;
					}
				case 3:{
					winings+=3*100;
					break;
					}
				case 4:{
					winings+=3*1000;
					break;
					}
				}
		     }
public:
	void display()
	{
	int i,j,k,l,m,x,t,flag=1;
	abc:
	Show("nothing.bmp",0,0);
	black();
	users.profile();
	buyin=ucash.cash;
	winings=0;
	stake=0;
	values();
	int fposx[36]={430,410,386,366,350,334,320,312,305,300,302,304,315,324
	,334,350,368,388,412,430,450,472,490,505,520,530,535,538,540,538,530,520,505
	,490,470,450};

	int fposy[36]={128,128,136,140,156,168,180,198,220,240,260,280,300,318
	,335,345,356,364,370,370,364,358,348,335,320,300,280,260,240,220,198,178,165
	,150,140,130};
	int bposx[26]={270,296,364,420,480,570,556,520,480,420,360,300,285,278,288,320,360,440,490,550,560,535,480,510};
	int bposy[26]={200,350,400,408,396,300,170,126,104,92,110,180,220,250,300,350,380,390,370,300,250,170,130,125};
	char rno[36][5]= {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36"};
	int posx[36]= {424,400,375,350,330,313,298,285,275,270,272,276,284,294,312,330,353,375,400,424,448,472,492,512,528,540,548,552,552,548,540,528,512,494,472,450};
	int posy[36]= {98,98,102,112,124,138,160,180,205,230,255,278,300,320,340,355,367,375,380,380,376,368,355,340,320,300,278,252,228,203,180,158,140,124,112,104};

	setcolor(10);
	setfillstyle(1,10);
	pieslice(420,250,0,360,180);
	setfillstyle(0,10);
	pieslice(420,250,0,360,182);
	setfillstyle(1,3);
	pieslice(420,250,0,360,165);
	setcolor(10);
	for(i=0,k=1;i<360;i+=10,k++)
		{
		setfillstyle(1,k%2);
		pieslice(420,250,i,i+10,152);
		}
	setcolor(0);
	setfillstyle(1,255);
	for(i=0;i<360;i+=10)
		pieslice(420,250,i,i+10,130);
	setcolor(255);
	setfillstyle(1,255);
	pieslice(420,250,0,360,110);
	setcolor(30);
	setfillstyle(1,30);
	pieslice(420,250,0,360,110);
	setcolor(0);
	setfillstyle(1,0);
	for(i=30;i<360;i+=120)
		pieslice(420,250,i,i+30,50);
	setcolor(0);
	setfillstyle(1,0);
	pieslice(420,250,0,360,10);
	setcolor(255);
	settextstyle(2,0,6);
	for(i=0;i<36;i++,l++)
		outtextxy(posx[i],posy[i],rno[i]);
	setcolor(251);
	setfillstyle(1,251);
	pieslice(bposx[0],bposy[0],0,360,4);
	setcolor(0);
	setfillstyle(1,GREEN);
	k=0;
		for(j=100,k=0;j<700;j+=50)
		for(i=800;i<950;i+=50,k++)
		{

		bar(i,j,i+50,j+50);
		rectangle(i,j,i+50,j+50);
		outtextxy(i+20,j+20,rno[k]);
		}

		setfillstyle(1,BLUE);
		bar(750,100,800,250);
		setfillstyle(1,0);
		rectangle(750,100,800,250);
		bar(750,250,800,400);
		setfillstyle(1,GREEN);
		rectangle(750,250,800,400);
		bar(750,400,800,550);
		rectangle(750,400,800,550);
		bar(750,550,800,700);
		rectangle(750,550,800,700);
		setcolor(RED);
		rectangle(745,95,955,705);
		setcolor(0);
		settextstyle(1,1,4);
		outtextxy(755,450,"ODD");
		outtextxy(755,590,"EVEN");

	int poschips[5]={396,466,530,593,657};
	char chips[5][5]={"1","5","25","100","1000"};
	int color[5]={2,5,4,1,3};
	char betplace[5][10]={"NUMBER","ODD","EVEN","RED","BLACK"};
	int betpos[5]={270,370,420,500,550};
	int pos=0,end=0,no[100],num=-1,num1=-1,chipno[100];
	int ch,chip=-1,barc=255;
	int chiptabx[4]={820,870,920,770};
	int chiptaby[16]={120,170,220,270,320,370,420,470,520,570,620,670,120,270,420,570};
	settextstyle(1,0,2);
	outtextxy(300,735,"PRESS ESC TO GO TO GAME SELECT");
	do
	{
	flag=0;
	xyz:
	values();
	for(i=400,k=0;i<700;i+=70,k++)
	{
		setcolor(0);
		setfillstyle(1,color[k]);
		for(j=0;j<360;j+=90)
			pieslice(i,650,j,j+90,25);
		if(chip!=k)
		{
			setcolor(255);
			setfillstyle(1,255);
			pieslice(i,650,0,360,20);
		}

	}
	setcolor(0);
	setfillstyle(1,barc);
	settextstyle(1,0,2);
	bar(520,695,600,730);
	outtextxy(535,700,"DONE");
	settextstyle(1,0,1);
	setcolor(0);
	for(i=0;i<5;i++)
	outtextxy(poschips[i],637,chips[i]);
		do
		{
		setcolor(255);
		outtextxy(250,600,"CHOOSE YOUR CHIP: ");
		ch=getch();
			if(ch==77)
			{
				if(chip>3)
					chip=0;
				else
					chip++;
				barc=255;
				goto xyz;
			}
			if(ch==75)
			{
				if(chip<=0)
					chip=4;
				else
					chip--;
				barc=255;
				goto xyz;
			}
			if(ch==80)
			{
				chip=20;
				barc=90;
				goto xyz;
			}
			if(ch==27)
			{
			if(games()==3)
				mainmenu();
			chip=-5;

			}
		}while(ch!=13);

	switch(chip)
	{
	case 0:{
		if(buyin-1<0)
			flag=1;
		else
			{
			buyin-=1;
			stake+=1;
			}
		break;
		}
	case 1:{
		if(buyin-5<0)
			flag=1;
		else
			{
			buyin-=5;
			stake+=5;
			}
		break;
		}
	case 2:{
		if(buyin-25<0)
			flag=1;
		else
			{
			buyin-=25;
			stake+=25;
			}
		break;
		}
	case 3:{
		if(buyin-100<0)
			flag=1;
		else
			{
			buyin-=100;
			stake+=100;
			}
		break;
		}
	case 4:{
		if(buyin-1000<0)
			flag=1;
		else
			{
			buyin-=1000;
			stake+=1000;
			}
		break;
		}
	case -5:{
		exit(0);
		}

	}
	if(stake==0)
		if(flag==1)
		{
		setcolor(3);
		outtextxy(300,670,"YOU DO NOT HAVE ENOUGH MONEY");
		delay(2000);
		setcolor(0);
		outtextxy(300,670,"YOU DO NOT HAVE ENOUGH MONEY");
		goto xyz;
		}
	setfillstyle(1,0);
	bar(250,500,750,800);
	setcolor(255);
	outtextxy(250,600,"PLACE YOUR BET ON:  ");
	if(chip!=20)
	{
	num1++;
	chipno[num1]=chip;
		do
		 {
			for(i=0;i<5;i++)
				if(i==pos)
					{
					setcolor(255);
					outtextxy(betpos[i],650,betplace[i]);
					}
				else    	{
					setcolor(RED);
					outtextxy(betpos[i],650,betplace[i]);
					}

			ch=getch();
				if(ch==77)
					if(pos==4)
						pos=0;
					else	pos++;
				if(ch==75)
					if(pos==0)
						pos=4;
					else	pos--;
				if(ch==13)
					end=1;
		  }while(end==0);
	if(pos==0)
		{
		num++;
		outtextxy(250,700,"(ENTER NO.<BETWEEN 1 & 36> FOLLOWED BY ENTER)");
		cin>>no[num];
		for(i=1,j=-1,k=0;i<37;i++)
			{
			if(j==2)
				{
				j=0;
				k++;
				}
			else j++;
			if(i==no[num])
				break;
			}
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(x=0;x<360;x+=90)
			pieslice(chiptabx[j],chiptaby[k],x,x+90,10);
			setcolor(255);
			setfillstyle(1,255);
			pieslice(chiptabx[j],chiptaby[k],0,360,5);
		}
	if(pos==1)
		{
		num++;
		no[num]=37;
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(x=0;x<360;x+=90)
			pieslice(chiptabx[3],chiptaby[14],x,x+90,10);
			setcolor(255);
			setfillstyle(1,255);
			pieslice(chiptabx[3],chiptaby[14],0,360,5);
		}
	if(pos==2)
		{
		num++;
		no[num]=38;
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(x=0;x<360;x+=90)
			pieslice(chiptabx[3],chiptaby[15],x,x+90,10);
			setcolor(255);
			setfillstyle(1,255);
			pieslice(chiptabx[3],chiptaby[15],0,360,5);
		}
	if(pos==3)
		{
		num++;
		no[num]=39;
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(x=0;x<360;x+=90)
			pieslice(chiptabx[3],chiptaby[12],x,x+90,10);
			setcolor(255);
			setfillstyle(1,255);
			pieslice(chiptabx[3],chiptaby[12],0,360,5);
		}
	if(pos==4)
		{
		num++;
		no[num]=40;
		setcolor(0);
		setfillstyle(1,color[chip]);
		for(x=0;x<360;x+=90)
			pieslice(chiptabx[3],chiptaby[13],x,x+90,10);
			setcolor(255);
			setfillstyle(1,255);
			pieslice(chiptabx[3],chiptaby[13],0,360,5);
		}
	}
	setfillstyle(1,0);
	bar(250,500,730,800);
	end=0;
	}while(chip!=20);
	values();

	j=1;
	m=0;
	x=0;
	t=20;

	while(t<148)
	{
	t+=2;
	delay(t);
	setcolor(3);
	setfillstyle(1,3);
	pieslice(bposx[x],bposy[x],0,360,4);
	if(j>3)
		j=1;
	j++;

	setcolor(10);
	for(i=0,k=j;i<360;i+=10,k++)
		{
		setfillstyle(1,k%2);
		pieslice(420,250,i,i+10,152);
		}
	setcolor(0);
	setfillstyle(1,255);
	for(i=0;i<360;i+=10)
		pieslice(420,250,i,i+10,130);
	setcolor(255);
	setfillstyle(1,255);
	pieslice(420,250,0,360,110);
	setcolor(30);
	setfillstyle(1,30);
	pieslice(420,250,0,360,110);
	setcolor(0);
	setfillstyle(1,0);
	if(j==2)
		i=30;
	if(j==3)
		i=60;
	if(j==4)
		i=90;
	for(;i<360;i+=120)
		pieslice(420,250,i,i+30,50);
	setcolor(0);
	setfillstyle(1,0);
	pieslice(420,250,0,360,10);
	setcolor(255);
	settextstyle(2,0,6);
	for(i=0,l=m;i<36;i++,l++)
		if(l>35)
			{
			i--;
			l=-1;
			}
		else
			outtextxy(posx[i],posy[i],rno[l]);
	if(m>34)
		m=-1;
	m++;
	x++;
	if(x==10&&m<15)
		x=0;
	if(x==23)
		x=11;
	setcolor(251);
	setfillstyle(1,251);
	if(t!=150)
	if(t+4>150)
		{
		srand(stake+chip);
		x=random(36);
		pieslice(fposx[x],fposy[x],0,360,4);
		}
	else	pieslice(bposx[x],bposy[x],0,360,4);
	}
	if(x>7)
	x-=8;
	else x+=28;
	win(no,chipno,num+1,x);
	buyin+=winings;
	values();
	ucash.cash=buyin;
	int pos1[2]={320,470};
	char ans[2][20]={"YES","NO"};
	outtextxy(300,500,"DO YOU WANT TO PLAY AGAIN?");
	if(highlighter1(ans,2,pos1,550)==0)
		goto abc;
	if(games()==3)
		mainmenu();

	}
}roulette;

//---------------------------------------------------------------------------
//--SLOT MACHINE--------------------------------------------------------------
//------------------------------------------------------------------------------

class slot_frenzy
{
int a,b,c;
	void slotstop()
		{
		setcolor(GREEN);
		rectangle(579,669,768,724);
		setfillstyle(1,10);
		bar(580,670,770,725);
		setfillstyle(1,254);
		bar(582,672,770,725);
		settextstyle(0,0,2);
		setcolor(2);
		outtextxy(625,689,"STOP");
		delay(150);
		setcolor(GREEN);
		rectangle(581,671,771,726);
		setfillstyle(1,10);
		bar(580,670,770,725);
		setfillstyle(1,255);
		bar(580,670,768,723);
		settextstyle(0,0,2);
		setcolor(0);
		outtextxy(623,687,"STOP");
		}

		void win(int x,int y,int z)
		{
		setcolor(87);
		outtextxy(450,550,"CASH WON: ");
		switch(x)
			{
			case 0:if(x==y&&x==z)
				      {
				       ucash.cash+=300;
				       outtextxy(600,550,"300");
				       break;
				       }
			case 1:{
				if(x==y&&x==z)
				      {
				       ucash.cash+=600;
				       outtextxy(600,550,"600");
				       break;
				       }
				if(y==2&&z==3)
					{
					ucash.cash+=10000;
					outtextxy(600,550,"10000");
					break;
					}
				}
			case 2:if(x==y&&x==z)
				      {
				       ucash.cash+=900;
				       outtextxy(600,550,"900");
				       break;
				       }
			case 3:if(x==y&&x==z)
				      {
				       ucash.cash+=1200;
				       outtextxy(600,550,"1200");
				       break;
				       }
			case 4:if(x==y&&x==z)
				      {
				       ucash.cash+=5000;
				       outtextxy(600,550,"5000");
				       break;
				       }
			default : outtextxy(600,550,"0");
			}
		}

public:
	void slot_machine()
	{
	abc:
	black();
	if(ucash.cash<50)
		{
		setcolor(56);
		outtextxy(100,100,"YOU DO NOT HAVE ENOUGH MONEY");
		getch();
		mainmenu();
		}
	ucash.cash-=50;
	char slots[5][20]={"a.bmp","k.bmp","q.bmp","j.bmp","bonus.bmp"};
	char slots1[5][20]={"a1.bmp","k1.bmp","q1.bmp","j1.bmp","bonus1.bmp"};
	setcolor(BLUE);
	setfillstyle(1,GREEN);
	bar(310,10,809,750);
	rectangle(310,10,809,750);
	setfillstyle(0,0);
	bar(315,15,804,745);
	rectangle(315,15,804,745);
	rectangle(315,100,478,300);
	rectangle(478,100,641,300);
	rectangle(641,100,804,300);
	Show(slots[0],320,120);
	Show(slots[0],483,120);
	Show(slots[0],646,120);
	settextstyle(1,0,2);
	setcolor(255);
	Show(slots1[0],325,330);
	outtextxy(375,332,"X 3 = 300");
	Show(slots1[1],550,330);
	outtextxy(634,332,"X 3 = 600");
	Show(slots1[2],325,400);
	outtextxy(375,400,"X 3 = 900");
	Show(slots1[3],550,400);
	outtextxy(634,400,"X 3 = 1200");
	Show(slots1[4],325,470);
	outtextxy(375,472,"X 3 = 5000");
	Show(slots1[1],550,470);
	Show(slots1[2],590,470);
	Show(slots1[3],530,470);
	outtextxy(680,472,"= 10000");

	settextstyle(4,0,6);
	setcolor(200);
	outtextxy(360,35,"SLOT FRENZY");
	slotstop();
	setcolor(GREEN);
	rectangle(381,671,571,726);
	setfillstyle(1,10);
	bar(380,670,570,725);
	setfillstyle(1,255);
	bar(380,670,568,723);
	settextstyle(0,0,2);
	setcolor(0);
	outtextxy(430,687,"START");
	getch();
	setcolor(GREEN);
	rectangle(379,669,568,724);
	setfillstyle(1,10);
	bar(380,670,570,725);
	setfillstyle(1,254);
	bar(382,672,570,725);
	settextstyle(0,0,2);
	setcolor(2);
	outtextxy(432,689,"START");
	int j=-1,time=300;
	while(!kbhit())
	{
	     j++;
		if(time!=0)
			time-=10;
		if(j==5)
			j=0;
		Show(slots[j],320,120);
			delay(time);
		Show(slots[j],483,120);
			delay(time);
		Show(slots[j],646,120);
		settextstyle(4,0,6);
		setcolor(random(256));
		outtextxy(360,35,"SLOT FRENZY");

	}
	getch();
	slotstop();
	a=j;
	Show(slots[j],320,120);
	while(!kbhit())
	{
		j++;
		if(time!=0)
			time-=10;
		if(j==5)
			j=0;
		Show(slots[j],483,120);
			delay(time);
		Show(slots[j],646,120);
		settextstyle(4,0,6);
		setcolor(random(256));
		outtextxy(360,35,"SLOT FRENZY");
	}
	getch();
	slotstop();
	j++;
		if(j==5)
			j=0;
	b=j;
	Show(slots[j],483,120);
	while(!kbhit())
	{
		j++;
		if(time!=0)
			time-=10;
		if(j==5)
			j=0;
		delay(time);
		Show(slots[j],646,120);
		settextstyle(4,0,6);
		setcolor(random(256));
		outtextxy(360,35,"SLOT FRENZY");
	}
	getch();
	slotstop();
	j++;
		if(j==5)
			j=0;
	c=j;
	Show(slots[j],646,120);
	win(a,b,c);
	users.profile();
	int pos1[2]={500,650};
	char ans[2][20]={"YES","NO"};
	outtextxy(450,600,"DO YOU WANT TO PLAY AGAIN?");
	if(highlighter1(ans,2,pos1,630)==0)
		goto abc;
	if(games()==3)
		mainmenu();
	}
}slot;
//---------------------------------------------------------------------------------
//------GAMES------------------------------------------------------------------
//-----------------------------------------------------------------------------
int games()
{
black();
int x=1,ch;
settextstyle(7,0,3);
setcolor(2);
do
{
black();
outtextxy(200,700,"PRESS ESC TO GO BACK TO MAINMENU");
if(x==1)
	{
	setfillstyle(0,255);
	Show("sf.bmp",10,10);
	}
else 	setfillstyle(1,255);
rectangle(150,650,350,700);
bar(154,654,346,696);
rectangle(154,654,346,696);
outtextxy(160,660,"SLOT FRENZY");
if(x==2)
	{
	setfillstyle(0,255);
	Show("bj2.bmp",0,50);
	}
else 	setfillstyle(1,255);
rectangle(400,650,600,700);
bar(404,654,596,696);
rectangle(404,654,596,696);
outtextxy(420,660,"BLACKJACK");
if(x==3)
	{
	setfillstyle(0,255);
	Show("rt.bmp",10,-10);
	}
else 	setfillstyle(1,255);
rectangle(650,650,850,700);
bar(654,654,846,696);
rectangle(654,654,846,696);
outtextxy(680,660,"ROULETTE");
ch=getch();
	if(ch==77)
		if(x>2)
			x=1;
		else 	x++;
	if(ch==75)
		if(x<2)
			x=3;
		else 	x--;
	if(ch==27)
		return 3;
}while(ch!=13);
gameloading();
if(x==1)
	slot.slot_machine();
if(x==2)
	casino.blackjack();
if(x==3)
	roulette.display();
}
//----------------------------------------------------------------------------------
//-------------MAIN MENU-----------------------------------------------------
//---------------------------------------------------------------------------------

void mainmenu()
{
black();
int i,j,ch,x=1;
for(i=-100;i<-65;i++)
	{
	setcolor(BROWN);
	circle(i,400,530);
	setcolor(1);
	circle(i,400,510);
	delay(10);
	}
setcolor(67);
circle(-100,400,500);
setcolor(RED);

do
{
if(x==1)
	setcolor(255);
else    setcolor(RED);
line(50,100,270,100);           //APARTMENTS
line(50,100,50,300);
line(50,300,380,300);
line(270,100,380,300);
settextstyle(7,0,4);
outtextxy(60,150,"BOOKING");
outtextxy(80,200,"APARTMENTS");

if(x==2)
	setcolor(255);
else    setcolor(GREEN);		 //CASINO GAMES
rectangle(100,320,380,520);
outtextxy(220,380,"CASINO");
outtextxy(240,430,"GAMES");

if(x==4)
	setcolor(255);
else    setcolor(BROWN);
circle(100,420,100);
outtextxy(10,390,"SAVE");
if(x==5)
	setcolor(255);
else    setcolor(BROWN);
outtextxy(110,390,"EXIT");	   //SAVE OR EXIT

if(x==3)
	setcolor(255);
else    setcolor(BLUE);
line(50,540,370,540);            //PROFILE INFO
line(50,740,250,740);
line(50,540,50,740);
line(370,540,250,740);
outtextxy(80,560,"PROFILE");
outtextxy(60,610,"INFORMATION");

ch=getch();                     //taking options
	if(ch==80)
		if(x>2)
			x=1;
		else x++;
	if(ch==72)
		if(x<2)
			x=3;
		else x--;
	if(ch==75)
		x=4;
	if(ch==77)
		x=5;
}while(ch!=13);
if(x!=4)
for(i=-65;i>-501;i--)
	{
	setcolor(0);
	circle(i,400,530);
	delay(1);
	}

switch(x)
{
case 1 :{
	apart.display();
	break;
	}
case 2 :{
	if(games()==3)
		mainmenu();
	break;
	}
case 3 :{
	if(users.viewprofile()==1)
		mainmenu();
	break;
	}
case 5 :{
	ending();
	exit(0);
	}
case 4:{
	users.save();
	mainmenu();
	break;
	}
}}
//-------------------------------------------------------------------------
//MAIN---------------------------------------------------------------------
//-------------------------------------------------------------------------
void main()
{
int gd = DETECT, md, a;
installuserdriver("SVGA256",&DetectSvga);
initgraph(&gd,&md,"c:\\tc\\bgi");	//graphics initials
users.start();
mainmenu();
}



