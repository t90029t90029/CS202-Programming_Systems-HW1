//Shang-Chun, Lin CS202 assignment#1
#include "node.h"

//This class interface is a subset of assignment 1 on OOP.
//This file will include the declaration of the base class and 3 derived classes from it.
class work;
class game;
class socialize;

class time
{
	public:
		time();
		time(const time & source);
		~time();	//like a wrapper function of ~node()

	protected:
		void copy(const node * source_head,node * & head,node * tail);		//recursion for the copy constructor
		//wrapper function = retrieve
		int compare(const int * try_from,const int * try_to,const int * day) const;
		//recursion ( also a wrappe funtion of data::compare())
		int compare(const int * try_from,const int * try_to,const node * head) const;

		int insert(const int * try_from,const int * try_to,const int * day);
		int remove(const int * try_from,const int * try_to,const int * day);		//wrapper function
		int remove(const int * try_from,const int * try_to,node * & head,node * tail);	//recursion ( also a wrapper function of data::compare())
		int display();			//wrapper function
		int display(const node * head);	//recursion ( also a wrapper function of data::display() )
		void remove_all();
		int period(const node * head);	//recursion ( also a wrapper function of data::period() )
		int period(int * min,int * max);//wrapper function ( also a inner function of work::check() )

		node ** head;
		node ** tail;
};

class work : public time
{
	public:
		work();
		work(const work & source);
		~work();

		int insert(const int * try_from,const int * try_to,const int * day,game & game_source,socialize & socialize_source);
		int remove(const int * try_from,const int * try_to,const int * day);
		int display();
		int retrieve(const int * try_from,const int * try_to,const int * day)const;
		void remove_all();
		void check();					//check the working time in each day is between MAX and MIN

		//interacting one by the request from the teacher : serving for the insert function in this class
		//if the time clash with the others activities, then it should cancel the schedule of the activity(gaming or socializing)
		int if_clash(const int * try_from,const int * try_to,const int * day,game & game_source,socialize & socialize_source);

		void set_limit();
	protected:
		int * max;
		int * min;

};

class game : public time
{
	public:
		game();
		game(const game & source);
		~game();

		int insert(const int * try_from,const int * try_to,const int * day,const work & work_source,const socialize & socialize_source);
		int remove(const int * try_from,const int * try_to,const int * day);
		int display();
		int retrieve(const int * try_from,const int * try_to,const int * day)const;
		void remove_all();

		void set_name();
	protected:
		char * name;
};

class socialize : public time
{
	public:
		socialize();
		socialize(const socialize & source);
		~socialize();

		int insert(const int * try_from,const int * try_to,const int * day,const work & work_source,const game & game_source);
		int remove(const int * try_from,const int * try_to,const int * day);
		int display();
		int retrieve(const int * try_from,const int * try_to,const int * day)const;
		void remove_all();

		void set_place();
	protected:
		char * place;
};
