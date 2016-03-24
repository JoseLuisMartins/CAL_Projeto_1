/*
 * Vertex.cpp
 *
 *  Created on: 24/03/2016
 *      Author: Joao
 */

#include "Vertex.h"
Vertex::Vertex(string name, Transport type) {
	this->name = name;
	this->type = type;
	// TODO Auto-generated constructor stub

}

Vertex::~Vertex() {
	// TODO Auto-generated destructor stub
}

void Vertex::addEdge(Edge& edge){
	edges.push_back(edge);
}

string Vertex::getName() const{
	return name;
}
Transport Vertex::getType() const{
	return type;
}

inline bool operator!=(const Vertex& v1, const Vertex& v2){
	return (v1.getName() == v2.getName() && v1.getType() == v2.getType());

}
