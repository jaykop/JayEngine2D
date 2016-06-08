#include <iostream>

class Observer
{
public:
	virtual void update(double stl, double st2, int st3) = 0;

};

class Subject
{
public:
	virtual void attach(Observer * o) = 0;
	virtual void detach(Observer * o) = 0; 
	virtual void notify() = 0;

};

class ConcreteSubject : public Subject
{
private:
	double st1, st2;
	int st3, index;
	Observer *objs[100];

public:
	ConcreteSubject(){ index = 0; }
	virtual void attach(Observer *o) { objs[index++] = o; }
	virtual void detach(void) {
		for (int i = 0; i < index; ++i)
		{
			if (objs[i] == 0)
				memmove(objs + i, objs + i + 1, sizeof(Observer)*(100 - i));
		}
	}

	virtual void notify(){
		for (int i = 0; i < index; ++i)
			objs[i]->update(st1, st2, st3);
	}

	void SetStatus(double st1, double st2, int st3)
	{
		this->st1 = st1;
		this->st2 = st2;
		this->st3 = st3;
	}
};

class ConcreteObserverA : public Observer
{
public:
	ConcreteObserverA(Subject *info){
		this->info = info;
		info->attach(this);
	}

	virtual void update(double st1, double st2, int st3) {
		this->st1 = st1;
		this->st2 = st2;
		this->st3 = st3;
		std::cout << st1 << " & " << st2 << "\n";
	}

private:
	double st1, st2;
	int st3;
	Subject* info;
};

class ConcreteObserverB : public Observer
{
public:
	ConcreteObserverB(Subject *info){
		this->info = info;
		info->attach(this);
	}

	virtual void update(double st1, double st2, int st3) {
		this->st1 = st1;
		this->st2 = st2;
		this->st3 = st3;
		std::cout << st2 << " & " << st3 << "\n";
	}

private:
	double st1, st2;
	int st3;
	Subject* info;
};