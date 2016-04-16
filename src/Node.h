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
	int lat;
	int longe;

public:

	Node(int id, int latitude, int longitude);
	virtual ~Node();

	int getID() const;
	int getLatitude() const;
	int getLongitude() const;
};

bool operator==(const Node& n1, const Node& n2);

#endif /* INTERSECAO_H_ */
