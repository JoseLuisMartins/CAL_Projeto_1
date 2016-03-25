#include "utils.h"



int distCost(Edge *e,Vertex *v){
	return e->getDistance();
}

int priceCost(Edge *e,Vertex *v){
	return e->getPrice();
}

int durationCost(Edge *e,Vertex *v){
	return e->getDuration();
}

int changeStationCost(Edge *e,Vertex *v){
	if(e->GetDest(v)->getType() == v->getType())
		return 0;
	else
		return 1;
}
