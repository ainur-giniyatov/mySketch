#include "Thread.h"

Thread::Thread(const std::vector<Obj *> &objects, const std::vector<Spring *> &springs, int o1, int o2, int s1, int s2):objects(objects), springs(springs)
{
	this->o1 = o1;
	this->o2 = o2;
	this->s1 = s1;
	this->s2 = s2;
}

void Thread::threadedFunction()
{
	while (isThreadRunning()) {
		for (int i = o1; i < o2; i++)
			objects[i]->resetForce();

		b1->Wait();

		for (int i = s1; i < s2; i++)
			springs[i]->step();

		b2->Wait();

		for (int i = o1; i < o2; i++)
			objects[i]->step();

		b3->Wait();
	}
}

void Thread::setBarriers(Barrier& b1, Barrier& b2, Barrier& b3)
{
	this->b1 = &b1;
	this->b2 = &b2;
	this->b3 = &b3;

}
