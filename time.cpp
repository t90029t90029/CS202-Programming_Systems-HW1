//Shang-Chun, Lin CS202 assignment#1
#include "time.h"

using namespace std;

//The purpose of this file is to implement each function in the time.h file

data::data()
{
	time_from = NULL;
	time_to = NULL;
	descrip = NULL;
}
	
data::data(const data & source)
{
	if(source.time_from)
	{
		time_from = new int;
		*time_from = *source.time_from;
	}
	else
	{
		time_from = NULL;
	}
	if(source.time_to)
	{
		time_to = new int;
		*time_to = *source.time_to;
	}
	else
	{
		time_to = NULL;
	}
	if(source.descrip)
	{
		descrip = new char[strlen(source.descrip)+1];
		strcpy(descrip,source.descrip);
	}
	else
	{
		descrip = NULL;
	}
}

data::~data()
{
	remove_all();
}

int data::compare(const int * try_from,const int * try_to) const		//match1 = beginning  match2 = ending
{
	if(!try_from || !try_to)
	{
		cout<<"Please enter the time period"<<endl;
		return 0;
	}
	if(*try_to <= *time_from || *try_from >= *time_to)	//not overlapped = we are free at the time = not scheduled
	{
		return 0;
	}
	
	return 1;
}

int data::insert(const int *try_from,const int * try_to)
{
	if(!try_from || !try_to)
	{
		cout<<"Please enter the time period"<<endl;
		return 0;
	}
	time_from = new int;
	time_to = new int;
	*time_from = *try_from;
	*time_to = *try_to;
	
	char * temp = NULL;
	temp = new char[301];
	cout<<"Please enter the description within 300 characters of the schedule."<<endl;
	cin.get(temp,300,'\n');
	cin.ignore(300,'\n');
	
	descrip = new char[strlen(temp) + 1];
	strcpy(descrip,temp);

	return 1;
}

int data::display()const
{
	if(!time_from || !time_to || !descrip)
	{
		return 0;
	}
	cout<<"Starts at "<<*time_from<<" o'clock."<<endl;
	cout<<"Ends at "<<*time_to<<" o'clock."<<endl;
	cout<<"Description : "<<descrip<<endl;
	return 1;
}

void data::remove_all()
{
	if(time_from)
	{
		delete time_from;
	}
	time_from = NULL;

	if(time_to)
	{
		delete time_to;
	}
	time_to = NULL;

	if(descrip)
	{
		delete descrip;
	}
	descrip = NULL;
}

int data::period()const		//return the sum of the time period of the node for work::check
{
	if(!time_from || !time_to)
	{
		return 0;
	}
	return (*time_to - *time_from);
}

node::node()
{
	next = NULL;
	previous = NULL;
}

node::node(const node & source):data(source),next(0),previous(0)
{
}

node::~node()
{
	if(next)
	{
		next = NULL;
	}
	if(previous)
	{
		previous = NULL;
	}
}

node *& node::go_next()
{
	return next;
}
		
node *& node::go_previous()
{
	return previous;
}

node * node::get_next()const
{
	return next;
}

node * node::get_previous()const
{
	return previous;
}

void node::connect_next(node * connection)
{
	if(!connection)
	{
		return;
	}
	next = connection;
	return;
}

void node::connect_previous(node * connection)
{
	if(!connection)
	{
		return;
	}
	previous = connection;
	return;
}

time::time()
{
	head = NULL;
	tail = NULL;
	head = new node*[7];
	tail = new node*[7];
	for(int i=0;i<7;++i)
	{
		head[i] = NULL;
		tail[i] = NULL;
	}		
}

void time::copy(const node * source_head,node * & head,node * tail)	//recursion for the copy constructor
{
	if(!source_head->get_next())
	{
		head = 	new node(*source_head);
		tail = head;
		return;
	}
	head = 	new node(*source_head);

	copy(source_head->get_next(),head->go_next(),tail);
	
	head->go_next()->connect_previous(head);
	
	return;
}

time::time(const time & source)
{
	if(source.head)
	{
		head = new node*[7];
		tail = new node*[7];
		for(int i=0;i<7;++i)
		{
			copy(source.head[i],head[i],tail[i]);
		}		
	}
	
}

time::~time()		//a wrpper function of remove_all()
{
	remove_all();
}

int time::compare(const int * try_from,const int * try_to,const node * head) const	//recursion
{
	if(!head)
	{
		return 0;
	}
	if(head->data::compare(try_from,try_to))
	{
		return 1;
	}
	return compare(try_from,try_to,head->get_next());
}

int time::compare(const int * try_from,const int * try_to,const int * day) const	//wrapper function
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	if(!head[*day])
	{
		return 0;
	}

	return compare(try_from,try_to,head[*day]);
}

int time::insert(const int * try_from,const int * try_to,const int * day)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	node * current = new node;
	if(!current->data::insert(try_from,try_to))	//if fail to insert
	{
		delete current;
		current = NULL;
		return 0;
	}
		
	if(!head)
	{
		head = new node*[7];
		tail = new node*[7];
		for(int i=0;i<7;++i)
		{
			head[i] = NULL;
			tail[i] = NULL;
		}		
	}
	if(!head[*day])					//if it was empty before we insert
	{
		head[*day] = current;
		tail[*day] = current;
		return 1;
	}

	tail[*day]->connect_next(current);
	tail[*day]->go_next()->connect_previous(tail[*day]);
	tail[*day] = tail[*day]->go_next();
	return 1;
}
		
int time::remove(const int * try_from,const int * try_to,node * & head,node * tail)	//recursion (also a wrapper function of data::compare()
{
	if(!head)
	{
		return 0;
	}
	if(head->data::compare(try_from,try_to))		//compare the time period
	{
		cout<<"it is overlapped with the schedule from "<<try_from<<" o'clock to "<<try_to<<" o'clock."<<endl;	
		
		node * hold = head->go_next();		//hold the rest of data
		if(hold)				//not the last one
		{
			hold->go_previous() = head->go_previous();
			head->data::remove_all();
			head->go_next() = NULL;
			head->go_previous() = NULL;
			delete head;
			head = hold;

			return 1;
		}

		else					//the node is the last one in the DLL
		{
			tail = head->go_previous();
			head->data::remove_all();
			head->go_next() = NULL;
			head->go_previous() = NULL;
			delete head;
			head = NULL;

			return 1;
		}	
	}
	return remove(try_from,try_to,head->go_next(),tail);
}
int time::remove(const int * try_from,const int * try_to,const int * day)	//wrapper function
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	
	if(!head || !head[*day])
	{
		cout<<"The schedule of the day is empty now, you can not remove any schedule."<<endl;
		return 0;
	}

	if(remove(try_from,try_to,head[*day],tail[*day]))
	{
		return 1;
	}
	return 0;
}

int time::display(const node * head)	//recursion (also a wrapper function of data::display() )
{
	if(!head)
	{
		return 0;
	}
	int count = 0;
	if(head->data::display())
	{
		++count;
	}
	count += display(head->get_next());
	return count;
}

int time::display()	//wrapper function
{
	int day = 0;
	for(int i = 0;i<7;++i)
	{
		if(head[i])
		{
			if(display(head[i]))
			{
				++day;
			}
		}
	}
	return day;
}

void time::remove_all()
{
	if(head)
	{
		for(int i=0;i<7;++i)
		{
			while(head[i])
			{
				if(tail[i])
				{
					tail[i] = NULL;
				}
				node * temp = head[i]->go_next();
				if(temp)
				{
					temp->go_previous() = NULL;
				}
				
				head[i]->data::remove_all();
				head[i]->go_next() = NULL;
				head[i]->go_previous() = NULL;
				delete head[i];
				head[i] = temp;
			}
		}
		delete head;
	}
	head = NULL;

	if(tail)
	{
		delete tail;
	}
	tail = NULL;
}

int time::period(const node * head)	//recursion ( also a wrapper function of data::period() )
{
	if(!head)
	{
		return 0;
	}
	int count = 0;
	count = head->data::period();
	count += period(head->get_next());

	return count;			//the sum of how many hours does the user work for the day
}

int time::period(int * min,int * max)	//wrapper function ( also a inner function of work::check() )
{
	int success = 0;
	int count = 0;
	for(int i = 0;i<7;++i)
	{
		if(head[i])
		{
			count = period(head[i]);
			if(*min <= count && count <= *max)
			{
				++success;
			}
		}
		else
		{
			++success;
		}
	}

	return success;			//how many days the working time period is between the max and min working time limit in the week
}

work::work()
{
	max = NULL;
	min = NULL;
}

work::work(const work & source):time(source)
{
	*max = *source.max;
	*min = *source.min;
}

work::~work()
{
	remove_all();
}

//if the time clash with the others activities
int work::if_clash(const int * try_from,const int * try_to,const int * day,game & game_source,socialize & socialize_source)
{
	int success = 0;
	char * answer = new char[2];
	if(game_source.retrieve(try_from,try_to,day))
	{
		++success;
		cout<<"The time clash happens. Do you want to cancel the schedule of the gaming?"<<endl
		<<"Y for yes, N for no."<<endl;
		cin>>*answer;
		cin.ignore(100,'\n');

		if(toupper(*answer) == 'Y')
		{
			if(game_source.remove(try_from,try_to,day))
			{
				cout<<"We have cancelled the schedule of the gaming for you."<<endl;
			}
		}
	}
	
	//reset
	*answer = '\0';


	if(socialize_source.retrieve(try_from,try_to,day))
	{
		++success;
		cout<<"The time clash happens. Do you want to cancel the schedule of the socializing?"<<endl
		<<"Y for yes, N for no."<<endl;
		cin>>*answer;
		cin.ignore(100,'\n');
		
		if(toupper(*answer) == 'Y')
		{
			if(socialize_source.remove(try_from,try_to,day))
			{
				cout<<"We have cancelled the schedule of the socializing for you."<<endl;
			}
		}
	}

	delete answer;
	answer = NULL;
	
	return success;
}

int work::retrieve(const int * try_from,const int * try_to,const int * day)const
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	if(time::compare(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int work::insert(const int * try_from,const int * try_to,const int * day,game & game_source,socialize & socialize_source)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	if(!retrieve(try_from,try_to,day))
	{
		cout<<"There is no time clash on the working schedule."<<endl;

		if(!if_clash(try_from,try_to,day,game_source,socialize_source))
		{
			if(time::insert(try_from,try_to,day))
			{
				cout<<"You have added a new schedule from "<<try_from<<" o'clock to "<<try_to<<" o'clock."<<endl;
				return 1;
			}
		}
		cout<<"If you have cancelled the time clash schedule at the last step, "<<endl
		<<"you are able to insert successfully next time."<<endl;
	}
	
	cout<<"Fail to add a new schedule this time."<<endl;	
	return 0;
}

int work::remove(const int * try_from,const int * try_to,const int * day)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	if(time::remove(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int work::display()
{
	int num = 0;
	num = time::display();
	cout<<"We have displayed the schedule of "<<num<<" days in this week for you."<<endl;
	return num;
}

void work::remove_all()
{
	if(max)
	{
		delete max;
	}
	max = NULL;

	if(min)
	{
		delete min;
	}
	min = NULL;

	time::remove_all();
}

void work::check()
{
	if(time::period(min,max) == 7)
	{
		cout<<"The sum of the working time in each day this week is between the max and the min working limit you have set."<<endl;
	}
	else
	{
		cout<<"There is at least one working day this week is NOT between the max and the min working limit you have set."<<endl;
	}
	return;
}

void work::set_limit()
{
	if(min)
	{
		delete min;
		min = NULL;
	}
	if(max)
	{
		delete max;
		max = NULL;
	}
	min = new int;
	max = new int;
	
	cout<<"Please set up the MIN working time in each day this week. (24-hour system = entering an integer from 0 to 24)"<<endl;
	cin>>*min;
	cin.ignore(50,'\n');
	cout<<"Please set up the MAX working time in each day this week. (24-hour system = entering an integer from 0 to 24)"<<endl;
	cin>>*max;
	cin.ignore(50,'\n');
	
	return;
}

game::game()
{
	name = NULL;
}

game::game(const game & source):time(source)
{
	name = new char[strlen(source.name)+1];
	strcpy(name,source.name);
}

game::~game()
{
	remove_all();
}

int game::retrieve(const int * try_from,const int * try_to,const int * day)const
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	if(time::compare(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int game::insert(const int * try_from,const int * try_to,const int * day,const work & work_source,const socialize & socialize_source)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	int count = 0;

	if(!retrieve(try_from,try_to,day))
	{
		cout<<"There is no time clash on the gaming schedule."<<endl;

		if(work_source.retrieve(try_from,try_to,day))
		{
			cout<<"There is a time clash with the working schedule. Please remove it first."<<endl;
			++count;
		}
		if(socialize_source.retrieve(try_from,try_to,day))
		{
			cout<<"There is a time clash with the socializing schedule. Please remove it first."<<endl;
			++count;
		}
		if(count == 0)
		{
			if(time::insert(try_from,try_to,day))
			{
				cout<<"You have added a new schedule from "<<try_from<<" o'clock to "<<try_to<<" o'clock."<<endl;
			}
		}
		else
		{
			cout<<"fail to insert because of the time clash."<<endl;
		}
	}
	else
	{
		cout<<"There is a time clash on the gaming schedule. Please remove it first."<<endl;
	}

	if(count == 0)
	{	
		return 1;
	}
	else
	{
		return 0;
	}
}

int game::remove(const int * try_from,const int * try_to,const int * day)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	if(time::remove(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int game::display()
{
	int num = 0;
	num = time::display();
	cout<<"We have displayed the schedule of "<<num<<" days in this week for you."<<endl;
	return num;
}

void game::remove_all()
{
	if(name)
	{
		delete name;
	}
	name = NULL;

	time::remove_all();
}

void game::set_name()
{
	if(name)
	{
		delete name;
		name = NULL;
	}
	char * temp = NULL;
	temp = new char[101];
	cout<<"Please set up the names of people who will play the game (including yourself) this week."<<endl;
	cin.get(temp,100,'\n');
	cin.ignore(100,'\n');

	name = new char[strlen(temp)+1];
	strcpy(name,temp);

	delete temp;
	temp = NULL;

	return;
}

socialize::socialize()
{
	place = NULL;
}
		
socialize::socialize(const socialize & source):time(source)
{
	place = new char[strlen(source.place)+1];
	strcpy(place,source.place);
}

socialize::~socialize()
{
	remove_all();
}

int socialize::retrieve(const int * try_from,const int * try_to,const int * day)const
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	if(time::compare(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int socialize::insert(const int * try_from,const int * try_to,const int * day,const work & work_source,const game & game_source)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}
	int count = 0;

	if(!retrieve(try_from,try_to,day))
	{
		cout<<"There is no time clash on the socializing schedule."<<endl;

		if(work_source.retrieve(try_from,try_to,day))
		{
			cout<<"There is a time clash with the working schedule. Please remove it first."<<endl;
			++count;
		}
		if(game_source.retrieve(try_from,try_to,day))
		{
			cout<<"There is a time clash with the gaming schedule. Please remove it first."<<endl;
			++count;
		}
		if(count == 0)
		{
			if(time::insert(try_from,try_to,day))
			{
				cout<<"You have added a new schedule from "<<try_from<<" o'clock to "<<try_to<<" o'clock."<<endl;
			}
		}
		else
		{
			cout<<"fail to insert because of the time clash."<<endl;
		}
	}
	else
	{
		cout<<"There is a time clash on the socializing schedule. Please remove it first."<<endl;
	}

	if(count == 0)
	{	
		return 1;
	}
	else
	{
		return 0;
	}
}
		
int socialize::remove(const int * try_from,const int * try_to,const int * day)
{
	if(!try_from || !try_to || !day)
	{
		return 0;
	}

	if(time::remove(try_from,try_to,day))
	{
		return 1;
	}
	return 0;
}

int socialize::display()
{
	int num = 0;
	num = time::display();
	cout<<"We have displayed the schedule of "<<num<<" days in this week for you."<<endl;
	return num;
}

void socialize::remove_all()
{
	if(place)
	{
		delete place;
	}
	place = NULL;

	time::remove_all();
}

void socialize::set_place()
{
	if(place)
	{
		delete place;
		place = NULL;
	}
	char * temp = NULL;
	temp = new char[101];
	cout<<"Please set up the names of places where you will socialize with others people this week."<<endl;
	cin.get(temp,100,'\n');
	cin.ignore(100,'\n');

	place = new char[strlen(temp)+1];
	strcpy(place,temp);

	delete temp;
	temp = NULL;

	return;
}

