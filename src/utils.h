#ifndef UTILS_H
#define UTILS_H


#include "VertexAndEdge.h"
#include "Node.h"
#include "Way.h"

template<class A,class B>
int distCost(Edge<A,B> *e,Vertex<A,B> *v);

template<class A,class B>
int priceCost(Edge<A,B> *e,Vertex<A,B> *v);

template<class A,class B>
int durationCost(Edge<A,B> *e,Vertex<A,B> *v);

template<class A,class B>
int changeStationCost(Edge<A,B> *e,Vertex<A,B> *v);

template<class A,class B>
struct VertexHandler{
	Vertex<A,B> *v;
};

template<class A,class B>
inline bool operator<(VertexHandler<A,B>& v1,VertexHandler<A,B>& v2){
		return v1.v->getCost() < v2.v->getCost();
}

template<class A,class B>
inline bool operator==(const VertexHandler<A,B>& v1,const VertexHandler<A,B>& v2){
		return (v1.v == v2.v);
}

#endif
