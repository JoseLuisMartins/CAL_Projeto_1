#ifndef UTILS_H
#define UTILS_H

enum Transport {

	NONE,
	TRAIN,
	BUS,
	SUBWAY

};

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

struct VertexHandler{
	Vertex *v;
};

inline bool operator<(const VertexHandler& v1,const VertexHandler& v2){
		return v1.v->getCost() < v2.v->getCost();
}

#endif
