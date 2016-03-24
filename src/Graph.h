/*
 * Graph.h
 *
 *  Created on: 24/03/2016
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.h"
#include <vector>

class Graph {

	vector<Vertex&> verts;
public:
	Graph();

	void addVertex(Vertex& vert);

	virtual ~Graph();
};

#endif /* GRAPH_H_ */
