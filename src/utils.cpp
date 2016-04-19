#include "utils.h"


int distCost(Edge<Node,Way> *e,Vertex<Node,Way> *v){
	return e->getWeights().getDistance();
}

int priceCost(Edge<Node,Way> *e,Vertex<Node,Way> *v){
	return e->getWeights().getPrice();
}

int durationCost(Edge<Node,Way> *e,Vertex<Node,Way> *v){
	return e->getWeights().getTime();
}

int changeStationCost(Edge<Node,Way> *e,Vertex<Node,Way> *v){
	Vertex<Node,Way>* lastVertex = v->getLastVertex();
	Transport::Type tipo;

	if(lastVertex==NULL){
		return 0;
	}

	for(unsigned int i = 0; i < lastVertex->getEdges().size(); i++){
			if(lastVertex->getEdges()[i].getDest() == v)
				tipo = lastVertex->getEdges()[i].getWeights().getType();
		}

	if(e->getWeights().getType() == tipo)
		return 0;
	else
		return 1;
}
