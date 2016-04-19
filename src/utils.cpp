#include "utils.h"


template<class A,class B>
int distCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getWeights().getDistance();
}

template<class A,class B>
int priceCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getWeights().getPrice();
}

template<class A,class B>
int durationCost(Edge<A,B> *e,Vertex<A,B> *v){
	return e->getWeights().getTime();
}

template<class A,class B>
int changeStationCost(Edge<A,B> *e,Vertex<A,B> *v){
	if(v->getType == NULL)
		return 0;

	if(e->getWeights()->getType() == v->getType())
		return 0;
	else
		return 1;
}
