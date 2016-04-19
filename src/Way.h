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
	double distance;
	Transport::Type type;


public:
	Way(){}
	Way(int id, string name, Transport::Type type);
	virtual ~Way();

	unsigned int getID() const;
	string getName() const;
	double getPricePerMeter() const;
	double getDistance() const;
	void setDistance(double dist);
	double getTime() const;
	double getPrice() const;
	Transport::Type getType() const;
};

#endif /* WAY_H_ */
