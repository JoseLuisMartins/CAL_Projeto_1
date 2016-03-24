/*
 * Edge.cpp
 *
 *  Created on: 24/03/2016
 *      Author: Joao
 */

#include "Edge.h"

Edge::Edge(Vertex& p1, Vertex& p2,int price, int distance, int duration) {
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

Vertex& Edge::GetDest(Vertex& p){
	if(p1 != p )
		return p1;
	return p2;
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

