/*
 * Intersecao.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#include "Node.h"


Node::Node(int id, int latitude, int longitude) {
	this->id = id;
	this->lat = latitude;
	this->longe = longitude;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

int Node::getID() const{
	return id;
}

int Node::getLatitude() const{
	return lat;
}

int Node::getLongitude() const{
	return longe;
}

bool operator==(const Node& n1, const Node& n2){
	return n1.getID() == n2.getID();
}
