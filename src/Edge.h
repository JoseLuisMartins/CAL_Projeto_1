/*
 * Edge.h
 *
 *  Created on: 24/03/2016
 *
 */
#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"

class Edge {

	Vertex& p1;
	Vertex& p2;
	int price;
	int distance;
	int duration;

public:
	Edge(Vertex& p1, Vertex& p2,int price, int distance, int duration);

	Vertex& GetDest(Vertex& p);

	int getPrice() const;
	int getDistance() const;
	int getDuration() const;


	virtual ~Edge();
};


#endif /* EDGE_H_ */
