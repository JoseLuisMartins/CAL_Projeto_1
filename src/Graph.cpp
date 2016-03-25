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



list<Vertex*> Graph::findWay(Vertex *start,Vertex *finish, int(*cost)(Edge*, Vertex* )){
	massiveReset();

	list<Vertex*> res;

	list<VertexHandler> listVH;
	VertexHandler vh;
	vh.v=start;
	listVH.push_front(vh);
	start->setCost(0);

	while(!listVH.empty()){

		listVH.sort();

		vh= listVH.front();
		listVH.pop_front();
		Vertex *v=vh.v;
		vector<Edge*>& edges=v->getEdges();

		for (unsigned int i = 0; i < edges.size(); ++i) {

			unsigned int weight=cost(edges[i],v);
			Vertex *v2=edges[i]->GetDest(v);

			if(v->getCost() + weight < v2->getCost()){

				v2->setCost(v->getCost()+weight);
				v2->setLastVertex(v);
				vh.v=v2;
				list<VertexHandler>::iterator itr =find(listVH.begin(),listVH.end(),vh);

				if(itr == listVH.end()){
					vh.v=v2;
					listVH.push_back(vh);
				}
			}
		}
	}

	if(finish->getLastVertex()==NULL)
		return res;

	Vertex* vaux=finish;

	while(vaux != NULL){
		res.push_front(vaux);
		vaux=vaux->getLastVertex();
	}


	return res;


}


