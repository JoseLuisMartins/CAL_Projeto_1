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

/*PARTE 2*/

/*Auxiliar ao algoritmo de Knuth-Morris-Pratt*/
int * computePrefixFunction(string toSearch){
	int* ids = (int*)malloc(sizeof(int)*toSearch.size());
	ids[0] = -1;

	int k = -1;
	for(int i = 1 ; i < toSearch.size(); i ++){
		while(k > -1 && toSearch[k+1] != toSearch[i]){
			k = ids[k];
		}
		if(toSearch[k+1] == toSearch[i]){
			k += 1;
		}
		ids[i] = k;
	}
	return ids;
}

bool findByNameExat(string searchArea, string toSearch){
	int *id = computePrefixFunction(toSearch);

	int q = -1;

	for(int i = 0; i < searchArea.size() ; i++){
		while(q > -1 && toSearch[q+1] != searchArea[i])
			q = id[q];
		if(toSearch[q+1] == searchArea[i])
			q +=1;
		if(q == toSearch.size()-1){
			q = id[q];
			return true;
		}
	}
	return false;
}

int findByNameAprox(string searchArea, string toSearch){

	int pSize = toSearch.size() + 1;
	int tSize = searchArea.size() + 1;

	int dist[pSize][tSize];

	for(unsigned int i = 0; i <= toSearch.size(); i ++) dist[i][0] = i;
	for(unsigned int i = 0; i <= searchArea.size(); i ++) dist[0][i] = i;

	for(unsigned int i = 1; i <= toSearch.size(); i++){
		for(unsigned int j = 1; j <= searchArea.size() ; j++){

			if(toSearch[i-1] == searchArea[j-1])
				dist[i][j] = dist[i-1][j-1];
			else
				dist[i][j] = 1 + min(min(dist[i-1][j-1], dist[i-1][j]), dist[i][j-1]);

		}
	}

	return dist[toSearch.size()][ searchArea.size()];

}

