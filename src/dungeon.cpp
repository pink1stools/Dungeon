/*
 Dungeon, in C++, http://rudih.info
 This game is a text-based RPG which has:
 A random dungeon, hit points, an inventory,
 merchants, enemies, money.
*/

void combat();
void shop();
void makedun();
void drawmap();
void getcoord();
void normal();
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "misc.h"
#include "dungeon.h"
//#include <conio.h>

using namespace std;
c_dungeon* dungeon;

short room[100];
int column, row, y, scratch, ct, GP, HP, enemyhp;
string user, mode;
char enemyname[256] = " ";;
short armour, knife;
char mp[256] = " ";
char hd[256] = " ";
char tx[256] = " ";
char tx2[256] = " ";

void DlgCallbackFunction(int buttonType, void */*userData*/)
{
    switch( buttonType ) 
	{
		case CELL_MSGDIALOG_BUTTON_YES:
		case CELL_MSGDIALOG_BUTTON_NO:		
		case CELL_MSGDIALOG_BUTTON_ESCAPE:
		case CELL_MSGDIALOG_BUTTON_NONE:
			break;

		default:
			break;
    }
}

c_dungeon::c_dungeon()
{
	nSelectedPKG	= 0;
	nPKGListTop		= 0;
	nTotalPKG		= 0;
	bDeleting		= false;
	nStatus			= 0;
	nPKGID			= 10000002;
}

void c_dungeon::Frame()
{
	DisplayFrame();
	InputFrame();
	DlgDisplayFrame();
}

void c_dungeon::DisplayFrame()
{   
	float xPos		= 0.05f;
	float yPos		= 0.05f;
	float yPosDiff	= 0.03f;	
	float nFontSize = 0.6f;

	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, "-----------------------------------------------------------------------" );
	yPos += yPosDiff;	
	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, "--------------------------------DUNGEON--------------------------------");
	yPos += yPosDiff;
	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, "-----------------------------------------------------------------------" );
	yPos += yPosDiff;
	::cellDbgFontPuts(xPos, yPos, 1.2f, 0xffffffff, mp);
	yPos += yPosDiff*13;
	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, "-----------------------------------------------------------------------" );
	//yPos += yPosDiff;
	//::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, hd);
	yPos += yPosDiff;
	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, tx);
	yPos += yPosDiff;
	yPos += yPosDiff;
	::cellDbgFontPuts(xPos, yPos, nFontSize, 0xffffffff, tx2);
	yPos += yPosDiff;
}

void c_dungeon::InputFrame()
{
    
	
	if (HP<1){
	                 sprintf(tx, "You have been killed. Game over\n-(O)-Quit");// -(/\\)-Restart");   
                     //cout<<"You have been killed. Game over." <<endl;
                     //getch();
                     mode="end";
                    } 
	if (mode!="end")
	{				
	if (room[y]==1||room[y]==8||room[y]==2) mode="normal";
	if(room[y]==4||room[y]==5||room[y]==6) mode="combat";
	if(room[y]==7) {
	                mode="shop";
					sprintf(tx, "There is a prisoner here. \nHe asks you if you want to buy something?");
                    sprintf(tx2, "-(X)-armour - 5GP -(/\\)-knife - 10GP -([])-potion - 3GP -(O)-Quit");
					}
	if (room[y]==3) {
	                sprintf(tx2, "You find 2 gold peices on the floor.");
                    //cout<<"You find 2 gold peices on the floor."<<endl;
                    GP=GP+2;
                    room[y]=1;
                    }
	if (room[y]==9) {
	                sprintf(tx, "You have found the way out! -THE END- \n-(O)-Quit");// -(/\\)-Restart");
                    //cout<<"You have found the way out! -THE END- enter quits"
                       // <<endl;
                    //getch();
                    mode="end";
                    } 
	}
	
    if(!app.mIsUpPressed && app.upPressedNow && HP>0)
	{   
	     if(mode == "normal")
	     {
		  user= "N";
		  normal();
		 }
		 
		 if(mode == "shop")
	     {
		  //shop();
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
	}
	
    if(!app.mIsDownPressed && app.downPressedNow && HP>0)
	{    
	     if(mode == "normal")
	     {
		  user= "S";
		  normal();
		 }
		 
		 if(mode == "shop")
	     {
		  
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
	}
	
    if(!app.mIsLeftPressed && app.leftPressedNow && HP>0)
	{
	     if(mode == "normal")
	     {
		  user= "W";
          normal();		  
		 }

         if(mode == "shop")
	     {
		  //shop();
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }		 
	}
	
    if(!app.mIsRightPressed && app.rightPressedNow && HP>0)
	{
	     if(mode == "normal")
	     {
		  user= "E";
		  normal();
		 }
		 
		 if(mode == "shop")
	     {
		   //shop();
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
	}
	
    if(!app.mIsSquarePressed && app.squarePressedNow)
	{
	     if(mode == "normal")
	     {
		   
		 }
		 
		 if(mode == "shop")
	     {
		   
         if(GP>2) {
		          sprintf(tx2, "You buy the potion & drink it (+6HP). \nThe prisoner disappears.");
				  room[y]=1;
                  GP=GP-3;
                  HP=HP+6;
                  }
		  
		  if(GP<3){
		         sprintf(tx2, "Not enough GP.");
				 
                 }
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
	}
	
    if(!app.mIsCrossPressed && app.crossPressedNow)
	{
	     if(mode == "normal")
	     {
		  //drawmap();
		 }
		 
		 if(mode == "shop")
	     {
		  if(GP>4){
		          sprintf(tx2, "You buy the armour. \nThe prisoner disappears.");
                  room[y]=1;
                  GP=GP-5;
                  armour=1;
                  }
		  
		  if(GP<5){
		         sprintf(tx2, "Not enough GP.");
				 
                 }
         
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
	}
	
    if(!app.mIsCirclePressed && app.circlePressedNow)
	{
	    
		if(mode == "normal")
	     {
		 user= "Q";
		 app.onShutdown();
		 exit(0);
		 }
		 
		 if(mode == "shop")
	     {
		  
         sprintf(tx2, "The prisoner disappears.");
         room[y]=1;
		 }
		 
		 if(mode == "combat")
	     {
		 user= "Q";
		 app.onShutdown();
		 exit(0);
		 }
		 
		 if(mode == "end")
	     {
		 user= "Q";
		 app.onShutdown();
		 exit(0);
		 }
	}
	
    if(!app.mIsTrianglePressed && app.trianglePressedNow)
	{
	     if(mode == "normal")
	     {
		  user= "I";
		  normal();
		 }
		 
		 if(mode == "shop")
	     {
		  if(GP>9){
		         sprintf(tx2, "You buy the knife. \nThe prisoner disappears.");
				 room[y]=1;
                 GP=GP-10;
                 knife=1;
                 }
		  
		  if(GP<10){
		         sprintf(tx2, "Not enough GP.");
				 
                 }		 
		 }
		 
		 if(mode == "combat")
	     {
		  combat();
		 }
		 
		 if(mode == "end")
	     {app.onShutdown();
		exitspawn("/dev_hdd0/game/GPKG00123/USRDIR/RELOAD.SELF", NULL, NULL, NULL, NULL, 64, SYS_PROCESS_PARAM_STACK_SIZE_MAX);
	
		 }
	}
	
	// ------------------------------------------------------
	// [SELECT]

	if(!app.mIsSelectPressed && app.selectPressedNow)
	{
		app.onShutdown();
		exitspawn("/dev_hdd0/game/BLES80608/USRDIR/RELOAD.SELF", NULL, NULL, NULL, NULL, 64, SYS_PROCESS_PARAM_STACK_SIZE_MAX);
	}
}

void c_dungeon::DlgDisplayFrame()
{
if(nStatus == STATUS_START) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"You are attacked by a %s with %d HP." , enemyname, enemyhp 
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
	
	if(nStatus == STATUS_DEF) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"The %s attacks. \nYou lose %d HP." , enemyname, scratch
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
	
	if(nStatus == STATUS_ATT) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"You attack the %s. \nThe %s loses %d HP." , enemyname, enemyname, scratch
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
	
	if(nStatus == STATUS_END) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"You killed the %s. \nThe enemy drops 1GP." , enemyname
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
	
	if(nStatus == STATUS_WIN) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"You attack the %s . \nThe %s loses %d HP." , enemyname, enemyname, scratch
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
	
	if(nStatus == STATUS_GAME_OVER) 
	{
		cellMsgDialogAbort();

		char szMsg[256] = "";
		sprintf(
			szMsg, 
			"You attack the %s . \nThe %s loses %d HP." , enemyname, enemyname, scratch
		);

		::cellMsgDialogOpen2(
			CELL_MSGDIALOG_DIALOG_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON, 
			szMsg, 
			DlgCallbackFunction, NULL, NULL
		);
	}
}

void c_dungeon::startgame()
{
    HP = 16;
    GP=0;
    armour=0;
    knife=0;
	mode="normal";
    makedun();
    drawmap();
	//start();
	getcoord();
	//if (room[y]==1||room[y]==8||room[y]==2) normal();
	//if(room[y]==4||room[y]==5||room[y]==6) combat();
	//if(room[y]==7) shop();
	//normal();
}

int c_dungeon::start()
{
    /*HP=0;
	
    //cout << "---DUNGEON---" << endl
    //<< "[E]asy or [H]ard game> ";
    cin >> user;
    //if (user=="E" || user=="e") HP = 16;
    //if (user=="H" || user=="h") HP = 12;
	HP = 16;
    if (HP==0) return 0;
    GP=0;
    armour=0;
    knife=0;
    makedun();
    drawmap();*/
    while(user!="Q" || user!="q"){
           user="";
           getcoord();
           //cout << "column="<<column<<" row="<<row<<endl;
           if (room[y]==1||room[y]==8||room[y]==2) normal();
           if (user=="q"||user=="Q") return 0;
           if (user=="m" || user=="M") drawmap();
           if (room[y]==3) {
                    //cout<<"You find 2 gold peices on the floor."<<endl;
                    GP=GP+2;
                    room[y]=1;
                    }
           if(room[y]==4||room[y]==5||room[y]==6) combat();
           if (HP<1){
                     //cout<<"You have been killed. Game over." <<endl;
                     //getch();
                     return 0;
                    } 
           if(room[y]==7) shop();
           if (room[y]==9) {
                    //cout<<"You have found the way out! -THE END- enter quits"
                       // <<endl;
                    //getch();
                    return 0;
                    }    
    } 
return 0;
	}

void c_dungeon::makedun()
{
    srand( (unsigned)time( NULL ) );
    scratch=0;
    for (ct=1;ct<100;ct++) {
        scratch=rand()%8;
        room[ct]=scratch;
    }
    room[100]=room[0];
    scratch=rand()%100;
    room[scratch]=8;
    y=scratch;
    scratch=rand()%100;
    room[scratch]=9;
};

void c_dungeon::shop()
{
  mode = "shop";
  sprintf(tx, "There is a prisoner here. \nHe asks you if you want to buy something?");
  sprintf(tx2, "-(X)-armour - 5GP -(/\\)-knife - 10GP -([])-potion - 3GP -(O)-Quit");
  //cout<<"There is a prisoner here."<<endl;
  //cout<<"He asks you if you want to buy something [Y/N]?"<<endl<<"> ";   
  //cin>>user;
  if(user=="y"||user=="Y") {
         cout << "Which item:"<< endl
              << "-(X)-armour - 5GP -(/\\)-knife - 10GP -([])-potion - 3GP -(O)-Quit" << endl;
         cin >> scratch;
         if(scratch==1&&GP>4){
                              cout << "You buy the armour."<<endl;
                              GP=GP-5;
                              armour=1;
                              }
         if(scratch==2&&GP>9){
                             cout<<"You buy the knife"<<endl;
                             GP=GP-10;
                             knife=1;
                             }
         if(scratch==3&&GP>2) {
                             cout<<"You buy the potion & drink it (+6HP)."
                                 << endl;
                             GP=GP-3;
                             HP=HP+6;
                             }
  }
  cout<<"The prisoner disappears."<<endl;
  room[y]=1;
}  
                          
void c_dungeon::drawmap()
{
    sprintf(mp, " ");
     for (ct=1;ct<101;ct++) {
	 	
	
	
	if (ct==y){sprintf(mp, "%s* ", mp);}
	else {sprintf(mp, "%s. ", mp);}
	if (ct%10==0) {sprintf(mp, "%s\n ", mp);}
         //if (ct==y){cout<<"* ";} else {cout<<". ";}
         //if (ct%10==0) cout << endl;
		 
         }
}
              
void c_dungeon::combat()
{
if(room[y]==4){
              sprintf(enemyname, "snake");
              //enemyname="snake";
              enemyhp=1;
              }
if(room[y]==5){
              sprintf(enemyname, "guard");
              //enemyname="guard";
              enemyhp=2;
              }
if(room[y]==6){
              sprintf(enemyname, "skeleton");
              //enemyname="skeleton"; 
              enemyhp=6;
              }
			  //dungeon->nStatus = STATUS_START;
			  sprintf(tx, "You are attacked by a %s with %d HP." , enemyname, enemyhp);
              sprintf(tx2, " ");
	
//cout << "You are attacked by a "<<enemyname<<" with "
//<<enemyhp<<" HP."<<endl;
//wait(7);
while(enemyhp>0) {
         //wait(1);
         scratch=rand()%2;
         if(scratch==1){
		        
			    sprintf(tx2, "You attack the %s." , enemyname);
                //cout << "You attack the "<<enemyname<<"."<<endl;
                scratch=rand()%3+1;
                if (knife==1) scratch=scratch+3;
				sprintf(tx2, "%s\nThe %s loses %d HP." , tx2, enemyname, scratch);
                //cout<<"The "<<enemyname<<" loses "<<scratch<<" HP."<<endl; 
                //dungeon->nStatus = STATUS_ATT;				
                enemyhp=enemyhp-scratch; }
         else {
		      sprintf(tx2, "The %s attacks." , enemyname);
              //cout<<"The "<<enemyname<<" attacks.";
              scratch=rand()%3+1;
              if(armour==1&&scratch>1) scratch=scratch-2;
			  sprintf(tx2, "%s\nYou lose %d HP." , tx2, scratch);
              //cout<<" You lose "<<scratch<<" HP."<<endl;
			  //dungeon->nStatus = STATUS_DEF;
              HP=HP-scratch;
              if (HP<1) return;
         }
         if(enemyhp<1) {
		      sprintf(tx2, "You killed the %s." , enemyname);
		      //cout << "You killed the "<<enemyname<<"." <<endl
			  sprintf(tx2, "%s\nThe enemy drops 1GP." , tx2);
              //<< "The enemy drops 1GP. Press any key..." << endl;
              //getch();     
			  //dungeon->nStatus = STATUS_END;
              GP=GP+1;
              room[y]=1;                          
         }
   }
   
}

void c_dungeon::wait ( int seconds ) 
{ 
  clock_t endwait; 
  endwait = clock () + seconds * CLOCKS_PER_SEC ; 
  while (clock() < endwait) {} 
} 

void c_dungeon::getcoord()
{
     if (y<10) row=0;
     scratch=0;
     while (scratch<10){
           if (y>=scratch*10) row=scratch;
           scratch++;
           }
     column=(y%10)-1;
     if (column==-1) column=9;
}

void c_dungeon::normal()
{
    mode = "normal";
	sprintf(hd, "column=%d row=%d" , column, row);
    sprintf(tx, "You are in a dungeon room. HP=%d \n-(O)-Quit -(/\\)-Inventory -(D-pad)-Move " , HP);
    sprintf(tx2, " ");
	getcoord();
	//drawmap();
     //cout<<"You are in a dungeon room. HP="<<HP<<endl
        // <<"[Q]uit - [I]nventory - [M]ap - Move[N],[S],[E],[W]"<<endl
         //<<"> ";
     //cin >> user;
     if (user=="i" || user=="I") {
	               sprintf(tx2, "Inventory: GP=%d" , GP);
     
                   //cout<<"Inventory: GP="<<GP;
                   if (armour==1) sprintf(tx2, "%s -armour" , tx2);//cout << " -armour";
                   if (knife==1) sprintf(tx2, "%s -knife" , tx2);//cout << " -knife";
                   //cout << endl;
                   }
     if (user=="n" || user=="N"){
                   scratch=y-10;
                   if (row==0 || room[scratch]==0) {
				   sprintf(tx2, "North is blocked.");
				   }
                   else {
				   y=y-10;
				   }  
	                //getcoord();
	                drawmap();
                   }    
     if (user=="s" || user=="S"){
                   scratch=y+10;
                   if (row==9 || room[scratch]==0) {
				   sprintf(tx2, "South is blocked.");
				   }
                   else {
				   y=y+10;
				   }     
	                //getcoord();
	                drawmap();
                   }  
     if (user=="e" || user=="E"){
                   scratch=y+1;
                   if (column==9 || room[scratch]==0) {
				   sprintf(tx2, "East is blocked.");
				   }
                   else {
				   y=y+1;
				   }     
	                //getcoord();
	                drawmap();
                   }      
     if (user=="w" || user=="W"){
                   scratch=y-1;
                   if (column==0 || room[scratch]==0) {
				   sprintf(tx2, "West is blocked.");
				   }
                   else {
				   y=y-1;
				   }     
	                //getcoord();
	                drawmap();
                   }                                   
}
