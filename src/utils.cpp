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


void setcolor(unsigned int color)		//define a cor da letra
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void setcolor(unsigned int color, unsigned int background_color)	//define a cor da letra e a cor do fundo
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color + 16*background_color);
}
