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

void Graph::massiveReset(){
	for (int i = 0; i < verts.size(); ++i) {
		verts[i]->reset();
	}
}



vector<Vertex*> Graph::findWay(Vertex *start,Vertex *finish, int(*cost)(Edge*, Vertex* )){
	massiveReset();

	list<VertexHandler> list;
	VertexHandler vh;
	vh.v=start;
	list.push_front(vh);

	while(!list.empty()){
		list.sort();
		Vertex v=list.pop_front();




	}





}











