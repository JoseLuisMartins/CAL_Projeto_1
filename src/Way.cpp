/*
 * Way.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#include "Way.h"




Way::Way(int id, string name, unsigned int capacity, unsigned int distance, Transport::Type type){

	this->id = id;
	this->name = name;
	this->capacity = capacity;
	this->type = type;
	this->distance = distance;
}

Way::~Way() {

}

unsigned int Way::getID() const{
	return id;
}

string Way::getName() const{
	return name;
}

unsigned int Way::getCapacity() const{
	return capacity;
}

unsigned int Way::getDistance() const{
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
