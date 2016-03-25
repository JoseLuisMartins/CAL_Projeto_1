#ifndef UTILS_H
#define UTILS_H


#include "VertexAndEdge.h"


int distCost(Edge *e,Vertex *v);

int priceCost(Edge *e,Vertex *v);

int durationCost(Edge *e,Vertex *v);

int changeStationCost(Edge *e,Vertex *v);


struct VertexHandler{
	Vertex *v;
};



inline bool operator<(VertexHandler& v1,VertexHandler& v2){
		return v1.v->getCost() < v2.v->getCost();
}

inline bool operator==(const VertexHandler& v1,const VertexHandler& v2){
		return (v1.v == v2.v);
}

#endif
