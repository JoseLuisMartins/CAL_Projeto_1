#ifndef VERTEXANDEDGE_H_
#define VERTEXANDEDGE_H_

#include <string>
#include <vector>
#include <iostream>
#include "Transport.h"

using namespace std;

template <class A,class B>
class Graph;

template<class A, class B>
class Vertex;

template<class A, class B>
class Edge {

	Vertex<A,B>* dest;
	B weights;

public:
	Edge(Vertex<A,B>* dest,B weights);

	Vertex<A,B>* getDest();

	B getWeights() const;

};

template<class A, class B>
class Vertex{

	unsigned int id;
	bool visited;

	//conectivity things
	int num;
	int low;


	A info;

	vector<Edge<A,B> > edges;
	unsigned int cost;

	Vertex<A,B> *lastVertex;

public:

	friend class Graph<A,B>;

	Vertex(A info, unsigned int id);
	Vertex(A info);
	unsigned int getCost();

	void setCost(int newCost);
	virtual ~Vertex();
	void reset();
	void addEdge(Edge<A,B> edge);
	A getInfo();
	vector<Edge<A,B> > getEdges();
	void setLastVertex(Vertex<A,B> *v);
	Vertex<A,B>* getLastVertex();
	void imprime();
	bool removeEdgeTo(Vertex<A,B> *dest);
	void addEdge(Edge<A,B>* d,B w);
	unsigned int getID();

};

template<class A, class B>
unsigned int Vertex<A,B>::getID(){
	return id;
}

template<class A, class B>
Vertex<A,B>::Vertex(A info, unsigned int id) {
	this->info = info;
	this->id = id;
	this->cost=-1;
	this->lastVertex=NULL;
}

template<class A, class B>
Vertex<A,B>::Vertex(A info) {
	this->info = info;
	this->id = 0;
	this->cost=-1;
	this->lastVertex=NULL;
}

template<class A, class B>
Vertex<A,B>::~Vertex() {
}

template<class A, class B>
void Vertex<A,B>::addEdge(Edge<A,B> edge){
	edges.push_back(edge);
}

template<class A, class B>
void Vertex<A,B>::imprime(){
	cout << " | " << info << " | ";
}

template<class A, class B>
vector<Edge<A,B> > Vertex<A,B>::getEdges(){
	return edges;
}

template<class A, class B>
inline bool operator==(const Vertex<A,B>& v1, const Vertex<A,B>& v2){

	return (v1.getInfo() == v2.getInfo());

}


template<class A, class B>
Edge<A,B>::Edge(Vertex<A,B>* dest,B weights) {
	this->dest = dest;
	this->weights = weights;
}

template<class A, class B>
B Edge<A,B>::getWeights() const{
	return weights;
}

template<class A, class B>
Vertex<A,B>* Edge<A,B>::getDest(){
	return dest;
}

template<class A, class B>
void Vertex<A,B>::reset(){
	cost=-1;
	lastVertex=NULL;
	visited=false;
}

template<class A, class B>
unsigned int Vertex<A,B>::getCost(){
	return cost;
}

template<class A, class B>
void Vertex<A,B>::setCost(int newCost){
	cost=newCost;
}

template<class A, class B>
void Vertex<A,B>::setLastVertex(Vertex<A,B> *v){
	lastVertex=v;
}

template<class A, class B>
A Vertex<A,B>::getInfo(){
	return info;
}

template<class A, class B>
Vertex<A,B>* Vertex<A,B>::getLastVertex(){
	return lastVertex;
}

template<class A, class B>
bool Vertex<A,B>::removeEdgeTo(Vertex<A,B> *dest){
	for(unsigned int i = 0; i < edges.size(); i++){
		if(edges[i].GeDest() == dest){
			edges.erase(edges.begin() + i);
			return true;
		}
	}
	return false;
}

#endif
