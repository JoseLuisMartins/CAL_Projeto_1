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
#include <algorithm>
#include <iterator>


using namespace std;

class Graph {

	vector<Vertex*> verts;

public:
	Graph();

	void addVertex(Vertex* vert);

	list<Vertex*>  findWay(Vertex *start,Vertex *finish, int(*cost)(Edge*,  Vertex* ));

	void massiveReset();
	virtual ~Graph();

	void imprime();
};

#endif /* GRAPH_H_ */
