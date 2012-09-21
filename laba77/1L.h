#ifndef list1
#define list1
#include "Interface.h"

class List_1 : public Abstract
{
private:
	Elem1L *head;
public:
	List_1();
	~List_1();
	void AddToHead();
	void Clear();
	void PrintNext();
	bool DelFromInd(int);
};

#endif