#include "utils.h"


template<class A,class B>
int distCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getDistance();
}

template<class A,class B>
int priceCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getPrice();
}

template<class A,class B>
int durationCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getDuration();
}

template<class A,class B>
int changeStationCost(Edge<A,B> *e,Vertex<A,B> *v){
	if(e->GetDest(v)->getType() == v->getType())
		return 0;
	else
		return 1;
}
