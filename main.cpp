//Shang-Chun, Lin CS202 assignment#1
#include "time.h"
using namespace std;

//This file is to test out the hierarchy of the classes created
int main()
{
	work working;
	working.set_limit();

	game gaming;
	gaming.set_name();

	socialize socializing;
	socializing.set_place();

	char * answer = NULL;
	int * choose = NULL;
	int * type = NULL;
	int * day = NULL;
	int * from = NULL;
	int * to = NULL;
	// ---------------------------------------------------------//
	cout<<"Hi, this is a schedule program to help you build your schedule for working, gaming, and socializing among this week."<<endl;	

	cout<<"Now, please choose a kind of services you would like to use. You have to enter a number."<<endl
	<<"Enter 1 for adding a new schedule, 2 for removing a schedule, 3 for displaying all data in the schedule, "<<endl
	<<"4 for removing all data in the schedule, 5 for checking if the working time is between the limit you have set, "<<endl
	<<"6 for quiting the program."<<endl;

	choose = new int;
	cin>>*choose;
	cin.ignore(100,'\n');
		
	while(*choose < 1 || *choose > 6)
	{
		cout<<"out of range! try again."<<endl;
		cin>>*choose;
		cin.ignore(100,'\n');
	}
	
	// ---------------------------------------------------------//
	cout<<"Which day you would like to manage your schedule in this week?"<<endl
	<<"(entering from sunday to saturday in the lowercase)"<<endl;
	answer = new char[11];
	cin.get(answer,10,'\n');
	cin.ignore(100,'\n');

	day = new int;
	*day = 7;
	while(*day >= 7 || *day < 0)
	{
		if(strcmp(answer,"sunday") == 0)
		{
			*day = 0;
		}
		else if(strcmp(answer,"monday") == 0)
		{
			*day = 1;
		}
		else if(strcmp(answer,"tuesday") == 0)
		{
			*day = 2;
		}
		else if(strcmp(answer,"wednesday") == 0)
		{
			*day = 3;
		}
		else if(strcmp(answer,"thursday") == 0)
		{
			*day = 4;
		}
		else if(strcmp(answer,"friday") == 0)
		{
			*day = 5;
		}
		else if(strcmp(answer,"saturday") == 0)
		{
			*day = 6;
		}
		else
		{
			cout<<"out of range! try again."<<endl;
			cout<<"Which day you would like to manage your schedule in this week?"<<endl
			<<"(entering from Sunday to Saturday)"<<endl;
			*day = 7;
			delete answer;
			answer = NULL;
			answer = new char[11];
			cin.get(answer,10,'\n');
			cin.ignore(100,'\n');
		}
	}

	// ---------------------------------------------------------//
	cout<<"Now, please enter which schedule you would like to manage. "<<endl
	<<"Enter 1 for working, 2 for gaming, 3 for socializing, "<<endl
	<<"4 for working + gaming, 5 for gaming + socializing, 6 for working + socializing, "<<endl
	<<"7 for all of them."<<endl;
	type = new int;
	cin>>*type;
	cin.ignore(100,'\n');
	while(*type < 1 || *type > 7)
	{
		cout<<"out of range! try again."<<endl;
		cin>>*choose;
		cin.ignore(100,'\n');
	}

	// ---------------------------------------------------------//
	cout<<"Now, please enter the time period you want to set (no matter inserting, removing, or displaying...)."<<endl;
	cout<<"When does the setting start? (24-hour system,enter 0~24)"<<endl;
	from = new int;
	cin>>*from;
	cin.ignore(100,'\n');
	while(*from < 0 || *from > 24)
	{
		cout<<"out of range! try again."<<endl;
		cin>>*from;
		cin.ignore(100,'\n');
	}
	cout<<"When does the setting end? (24-hour system,enter 0~24)"<<endl;
	to = new int;
	cin>>*to;
	cin.ignore(100,'\n');
	while(*to < 0 || *to > 24)
	{
		cout<<"out of range! try again."<<endl;
		cin>>*to;
		cin.ignore(100,'\n');
	}

	//-----------------starting running the main part---------------------//
	while(*choose != 6)
	{	

		if(*choose == 1)
		{
			if(*type == 1)
			{
				if(working.insert(from,to,day,gaming,socializing))
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 2)
			{
				if(gaming.insert(from,to,day,working,socializing))
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 3)
			{
				if(socializing.insert(from,to,day,working,gaming))
				{
					cout<<"Done."<<endl;
				}
			}
			else
			{
				cout<<"We only provide adding a new schedule for just ONE activity, or the time clash happens."<<endl;
			}
		}
		if(*choose == 2)
		{
			if(*type == 1)
			{
				if(working.remove(from,to,day))
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 2)
			{
				if(gaming.remove(from,to,day))
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 3)
			{
				if(socializing.remove(from,to,day))
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 4)
			{
				if(working.remove(from,to,day) && gaming.remove(from,to,day))
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 5)
			{
				if(gaming.remove(from,to,day) && socializing.remove(from,to,day))
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 6)
			{
				if(working.remove(from,to,day) && socializing.remove(from,to,day))
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 7)
			{
				if(working.remove(from,to,day) && gaming.remove(from,to,day) && socializing.remove(from,to,day))
				{
					cout<<"Done for all."<<endl;
				}
			}
		}
		if(*choose == 3)
		{
			if(*type == 1)
			{
				if(working.display())
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 2)
			{
				if(gaming.display())
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 3)
			{
				if(socializing.display())
				{
					cout<<"Done."<<endl;
				}
			}
			if(*type == 4)
			{
				if(working.display() && gaming.display())
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 5)
			{
				if(gaming.display() && socializing.display())
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 6)
			{
				if(working.display() && socializing.display())
				{
					cout<<"Done for both."<<endl;
				}
			}
			if(*type == 7)
			{
				if(working.display() && gaming.display() && socializing.display())
				{
					cout<<"Done for all."<<endl;
				}
			}
		}
		if(*choose == 4)
		{
			if(*type == 1)
			{
				working.remove_all();
				cout<<"Done."<<endl;
			}
			if(*type == 2)
			{
				gaming.remove_all();
				cout<<"Done."<<endl;
			}
			if(*type == 3)
			{
				socializing.remove_all();
				cout<<"Done."<<endl;
			}
			if(*type == 4)
			{
				working.remove_all();
				gaming.remove_all();
				cout<<"Done for both."<<endl;
			}
			if(*type == 5)
			{
				gaming.remove_all();
				socializing.remove_all();
				cout<<"Done for both."<<endl;
			}
			if(*type == 6)
			{
				working.remove_all();
				socializing.remove_all();
				cout<<"Done for both."<<endl;
			}
			if(*type == 7)
			{
				working.remove_all();
				gaming.remove_all();
				socializing.remove_all();
				cout<<"Done for all."<<endl;
			}
		}
		if(*choose == 5)
		{
			working.check();
		}

		// ---------------------------------------------------------//
		cout<<"Now, please choose a kind of services you would like to use at the next step. "<<endl
		<<"Enter 1 for adding a new schedule, 2 for removing a schedule, 3 for displaying all data in the schedule, "<<endl
		<<"4 for removing all data in the schedule, 5 for checking if the working time is between the limit you have set, "<<endl
		<<"6 for quiting the program."<<endl;

		cin>>*choose;
		cin.ignore(100,'\n');

		while(*choose < 1 || *choose > 6)
		{
			cout<<"out of range! try again."<<endl;
			cin>>*choose;
			cin.ignore(100,'\n');
		}

		// ---------------------------------------------------------//
		if(*choose != 6)	//will not quit
		{
			cout<<"Which day you would like to manage your schedule in this week?"<<endl
			<<"(entering from sunday to saturday in the lowercase)"<<endl;
			answer = new char[11];
			cin.get(answer,10,'\n');
			cin.ignore(100,'\n');

			day = new int;
			*day = 7;
			while(*day >= 7 || *day < 0)
			{
				if(strcmp(answer,"sunday") == 0)
				{
					*day = 0;
				}
				else if(strcmp(answer,"monday") == 0)
				{
					*day = 1;
				}
				else if(strcmp(answer,"tuesday") == 0)
				{
					*day = 2;
				}
				else if(strcmp(answer,"wednesday") == 0)
				{
					*day = 3;
				}
				else if(strcmp(answer,"thursday") == 0)
				{
					*day = 4;
				}
				else if(strcmp(answer,"friday") == 0)
				{
					*day = 5;
				}
				else if(strcmp(answer,"saturday") == 0)
				{
					*day = 6;
				}
				else
				{
					cout<<"out of range! try again."<<endl;
					cout<<"Which day you would like to manage your schedule in this week?"<<endl
					<<"(entering from Sunday to Saturday)"<<endl;
					*day = 7;
					delete answer;
					answer = NULL;
					answer = new char[11];
					cin.get(answer,10,'\n');
					cin.ignore(100,'\n');
				}
			}
	
			// ---------------------------------------------------------//
			cout<<"Now, please enter which schedule you would like to manage. "<<endl
			<<"Enter 1 for working, 2 for gaming, 3 for socializing, "<<endl
			<<"4 for working + gaming, 5 for gaming + socializing, 6 for working + socializing, "<<endl
			<<"7 for all of them."<<endl;
			cin>>*type;
			cin.ignore(100,'\n');
			while(*type < 1 || *type > 7)
			{
				cout<<"out of range! try again."<<endl;
				cin>>*choose;
				cin.ignore(100,'\n');
			}

			// ---------------------------------------------------------//
			cout<<"Now, please enter the time period you want to set (no matter inserting, removing, or displaying...)."<<endl;
			cout<<"When does the setting start? (24-hour system,enter 0~24)"<<endl;
			from = new int;
			cin>>*from;
			cin.ignore(100,'\n');
			while(*from < 0 || *from > 24)
			{
				cout<<"out of range! try again."<<endl;
				cin>>*from;
				cin.ignore(100,'\n');
			}
			cout<<"When does the setting end? (24-hour system,enter 0~24)"<<endl;
			to = new int;
			cin>>*to;
			cin.ignore(100,'\n');
			while(*to < 0 || *to > 24)
			{
				cout<<"out of range! try again."<<endl;
				cin>>*to;
				cin.ignore(100,'\n');
			}
		}
	}

	if(answer)
	{
		delete answer;
	}
	answer = NULL;

	if(choose)
	{
		delete choose;
	}
	choose = NULL;

	if(type)
	{
		delete type;
	}
	type = NULL;

	if(day)
	{
		delete day;
	}
	day = NULL;

	if(from)
	{
		delete from;
	}
	from = NULL;

	if(to)
	{
		delete to;
	}
	to = NULL;


	return 0;
}
