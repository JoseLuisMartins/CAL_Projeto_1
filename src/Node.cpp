/*
 * Intersecao.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Lol
 */

#include "Node.h"


Node::Node(int id, double latitude, double longitude) {
	this->id = id;
	this->lat = latitude;
	this->longe = longitude;
}


int Node::getID() const{
	return id;
}

double Node::getLatitude() const{
	return lat;
}

double Node::getLongitude() const{
	return longe;
}

bool operator==(const Node& n1, const Node& n2){
	return n1.getID() == n2.getID();
}
