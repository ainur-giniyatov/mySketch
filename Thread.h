#pragma once
#include "utils/ofThread.h"
#include "Obj.h"
#include "Spring.h"
#include "barrier.h"


class Thread : public ofThread
{
public:
	Thread(const std::vector<Obj*> &objects, const std::vector<Spring*> &springs, int o1, int o2, int s1, int s2);
	void threadedFunction();
	void setBarriers(Barrier& b1, Barrier& b2, Barrier& b3);

private:
	const std::vector<Obj*>& objects;
	const std::vector<Spring*>& springs;
	int o1;
	int o2;
	int s1;
	int s2;

	Barrier* b1, * b2, * b3;
};

