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

template <class A,class B>
class Graph {

	vector<Vertex<A,B>*> verts;

public:
	Graph();

	bool addVertex(A inf);
	bool removeVertex(A inf);
	bool addEdge(A source, A dest, B w);
	bool removeEdge(A source,A dest);


	list<Vertex<A,B>*>  findWay(Vertex<A,B> *start,Vertex<A,B> *finish, int(*cost)(Edge<A,B>*,  Vertex<A,B>* ));

	void massiveReset();
	virtual ~Graph();

	void imprime();
};

#endif /* GRAPH_H_ */
