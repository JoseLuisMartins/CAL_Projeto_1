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

double Node::calcDist(Node n){

	double _x = n.getLatitude() - lat;
	double _y = n.getLongitude() - longe;

	return sqrt( _x*_x + _y*_y );

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

std::ostream & operator<<(std::ostream &o , const Node& n1){
	o << n1.getID();
	if(n1.getID() < 10)
		o << " ";
	return o;
}
