#ifndef 2L
#define 2L


 class List_2  : public Abstract
{
private:
	Elem2L *head;
	Elem2L *tail;
public:
	List_2();
	void AddToHead();
	void AddToTail();
	void DelFromTail();
	void DelFromHead();
	bool DelFromInd(int);
	void PrintNext();
	void PrintBack();
	void Clear();
};

#endif