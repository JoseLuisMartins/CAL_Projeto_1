/*
 * Way.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef WAY_H_
#define WAY_H_

#include<string>
#include "Transport.h"


using namespace std;

class Way {

	unsigned int id;
	string name;
	unsigned int capacity;
	unsigned int distance;
	Transport::Type type;


public:
	Way(){}
	Way(int id, string name, unsigned int capacity, unsigned int distance , Transport::Type type);
	virtual ~Way();

	unsigned int getID() const;
	string getName() const;
	unsigned int getCapacity() const;
	double getPricePerMeter() const;
	unsigned int getDistance() const;
	double getTime() const;
	double getPrice() const;
};

#endif /* WAY_H_ */
