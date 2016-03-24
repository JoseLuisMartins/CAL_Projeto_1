/*
 * Graph.h
 *
 *  Created on: 24/03/2016
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "VertexAndEdge.h"
#include <vector>
#include "utils.h"
#include <list>

class Graph {

	vector<Vertex*> verts;

public:
	Graph();

	void addVertex(Vertex* vert);

	vector<Vertex*> findWay(Vertex *start,Vertex *finish, int(*f)(Edge*,  Vertex* ));

	void massiveReset();
	virtual ~Graph();

	void imprime();
};

#endif /* GRAPH_H_ */
