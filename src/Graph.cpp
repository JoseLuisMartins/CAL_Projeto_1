/*
 * Graph.cpp
 *
 *  Created on: 24/03/2016
 *      Author: Joao
 */

#include "Graph.h"

Graph::Graph() {

}

void Graph::addVertex(Vertex* vert){
	verts.push_back(vert);
}


void Graph::imprime(){
	for (unsigned int var = 0; var < verts.size(); ++var) {
		verts[var]->imprime();
	}
}

Graph::~Graph() {
}

