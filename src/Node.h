/*
 * Intersecao.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef NODE_H_
#define NODE_H_

#define Earth_Ratius 6371000

#include <iostream>
#include <cmath>

class Node {

	int id;
	double lat;
	double longe;

public:
	Node(){}
	Node(int id, double latitude, double longitude);

	double calcDist(Node n);
	int getID() const;
	double getLatitude() const;
	double getLongitude() const;
};

bool operator==(const Node& n1, const Node& n2);

std::ostream & operator<<(std::ostream &o , const Node& n1);

#endif /* INTERSECAO_H_ */
