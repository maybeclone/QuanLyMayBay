#ifndef NODECB_H
#define NODECB_H

#include "ChuyenBay.h"

class NodeCB
{
	public:
		ChuyenBay cb;
		NodeCB* next = NULL;
		
		NodeCB();
		NodeCB(ChuyenBay&);
		NodeCB(ChuyenBay&, NodeCB*);
};

#endif

