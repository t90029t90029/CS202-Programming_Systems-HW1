//Shang-Chun, Lin CS202 assignment#1
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

//This file has the classes for managing an schedule for times of the 3 activities, implemented using an array of DLL.

//A node "is a" data plus the pointers to manage the next and the previous.

class data
{
	public:
		data();
		data(const data & source);
		~data();
	
		//check if the time(try_from ~ try_to) is scheduled(even a part of the period)
		int compare(const int * try_from,const int * try_to) const;
		int insert(const int *try_from,const int * try_to);
		int display()const;
		void remove_all();

		int period()const;	//return the sum of the time period of the node for work::check
	protected:
		int * time_from;
		int * time_to;
		char * descrip;		//description
};

class node : public data
{
	public:
		node();
		node(const node & source);
		~node();

		node *& go_next();
		node *& go_previous();
		node * get_next()const;
		node * get_previous()const;
		void connect_next(node * connection);
		void connect_previous(node * connection);
	protected:
		node * next;
		node * previous;
};
