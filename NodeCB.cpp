#include "NodeCB.h"

NodeCB::NodeCB(){
	next = NULL;
}
NodeCB::NodeCB(ChuyenBay& newCB){
	this->cb = newCB;
	next = NULL;
}

NodeCB::NodeCB(ChuyenBay &newCB, NodeCB* next){
	cb = newCB;
	this->next = next;
}

