/*
 * Way.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#include "Way.h"




Way::Way(int id, string name, Transport::Type type, string l){

	this->id = id;
	this->name = name;
	this->type = type;
	this->distance = distance;
	this->linha = l;
}

Way::~Way() {

}

unsigned int Way::getID() const{
	return id;
}

string Way::getName() const{
	return name;
}



double Way::getDistance() const{
	return distance;
}

double Way::getPrice() const{
	return Transport::PricePerMeter(type)*distance;
}

double Way::getTime() const{
	return distance / Transport::VelocityPerMeter(type);
}

double Way::getPricePerMeter() const{
	return Transport::PricePerMeter(type);
}

Transport::Type Way::getType() const{
	return type;
}


void Way::setDistance(double dist){
	distance=dist;
}

string Way::getLinha() const {
	return linha;
}

void Way::setLinha(string l){
	this->linha = l;
}
