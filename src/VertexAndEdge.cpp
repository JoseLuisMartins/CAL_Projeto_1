/*
 * VertexAndEdge.cpp
 *
 *  Created on: 24/03/2016
 *      Author:
 */

#include "VertexAndEdge.h"

using namespace std;


Vertex::Vertex(string name,enum Transport type) {
	this->name = name;
	this->type = type;

}

Vertex::~Vertex() {
}

void Vertex::addEdge(Edge* edge){
	edges.push_back(edge);
}

string Vertex::getName() const{
	return name;
}
Transport Vertex::getType() const{
	return type;
}

void Vertex::imprime(){
	cout << name << " : " << type << endl;
}

inline bool operator!=(const Vertex& v1, const Vertex& v2){
	return (v1.getName() == v2.getName() && v1.getType() == v2.getType());

}


Edge::Edge(Vertex* p1, Vertex* p2,int price, int distance, int duration) {
	this->p1 = p1;
	this->p2 = p2;
	this->price = price;
	this->distance = distance;
	this->duration = duration;
}

int Edge::getPrice() const{
	return price;
}
int Edge::getDistance() const{
	return distance;
}
int Edge::getDuration() const{
	return duration;
}

Vertex* Edge::GetDest(Vertex* p){
	if(p1 != p )
		return p1;
	return p2;
}

Edge::~Edge() {
}


void Vertex::reset(){
	cost=-1;
	lastVertex=NULL;
}

int Vertex::getCost(){
	return cost;
}

void Vertex::setCost(int newCost){
	cost=newCost;
}


