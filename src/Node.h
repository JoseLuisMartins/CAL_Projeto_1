/*
 * Intersecao.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef NODE_H_
#define NODE_H_

#define Earth_Ratius 6371000

class Node {

	int id;
	double lat;
	double longe;

public:
	Node(){}
	Node(int id, double latitude, double longitude);


	int getID() const;
	double getLatitude() const;
	double getLongitude() const;
};

bool operator==(const Node& n1, const Node& n2);

#endif /* INTERSECAO_H_ */
