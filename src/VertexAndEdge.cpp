/*
 * VertexAndEdge.cpp
 *
 *  Created on: 24/03/2016
 *      Author:
 */

#include "VertexAndEdge.h"

using namespace std;

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
	cout << info;
}

template<class A, class B>
vector<Edge<A,B>> Vertex<A,B>::getEdges(){
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
int Edge<A,B>::getWeights() const{
	return weights;
}

template<class A, class B>
Vertex<A,B>* Edge<A,B>::GetDest(){
	return dest;
}

template<class A, class B>
void Vertex<A,B>::reset(){
	cost=-1;
	lastVertex=NULL;
}

template<class A, class B>
int Vertex<A,B>::getCost(){
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
A Vertex<A,B>::getInfo() const{
	return info;
}

template<class A, class B>
Vertex<A,B>* Vertex<A,B>::getLastVertex(){
	return lastVertex;
}


