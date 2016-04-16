/*
 * Graph.cpp
 *
 *  Created on: 24/03/2016
 *      Author: Joao
 */

#include "Graph.h"

template <class A, class B>
Graph<A,B>::Graph() {
}

template <class A, class B>
Graph<A,B>::~Graph() {
}


template <class A, class B>
bool Graph<A,B>::addVertex(A inf){
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->getInfo() == inf)
			return false;
	}
	Vertex<A,B>* a = new Vertex<A,B>(inf);
	verts.push_back(a);
	return true;
}

template <class A, class B>
bool Graph<A,B>::removeVertex(A inf){
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->getInfo() == inf){
			Vertex<A,B>* v = verts[i];
			verts.erase(verts.begin() + i--);
			for(unsigned int j = 0; j < verts.size(); j++){
				verts[i]->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class A,class B>
bool Graph<A,B>::addEdge(A source, A dest,B w){
	Vertex<A,B> *vS, *vD;
	vS = NULL;
	vD = NULL;
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->getInfo() == source)
			vS = verts[i];
		if(verts[i]->getInfo() == dest)
			vD = verts[i];
	}
	if(vS == NULL || vD == NULL)
		return false;
	Edge<A,B> e(vD,w);
	vS->addEdge(e);
	return true;
}

template <class A, class B>
bool Graph<A,B>::removeEdge(A source,A dest){
	Vertex<A,B> *vS, *vD;
	vS = NULL;
	vD = NULL;
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->getInfo() == source)
			vS = verts[i];
		if(verts[i]->getInfo() == dest)
			vD = verts[i];
	}
	if(vS == NULL || vD == NULL)
		return false;
	return vS->removeEdgeTo(vD);
}


template <class A,class B>
void Graph<A,B>::massiveReset(){
	for (unsigned int i = 0; i < verts.size(); ++i) {
		verts[i]->reset();
	}
}


template<class A,class B>
list<Vertex<A,B>*> Graph<A,B>::findWay(Vertex<A,B> *start,Vertex<A,B> *finish, int(*cost)(Edge<A,B>*, Vertex<A,B>* )){
	massiveReset();

	list<Vertex<A,B>*> res;

	list<VertexHandler<A,B> > listVH;
	VertexHandler<A,B> vh;
	vh.v=start;
	listVH.push_front(vh);
	start->setCost(0);

	while(!listVH.empty()){

		listVH.sort();

		vh= listVH.front();
		listVH.pop_front();
		Vertex<A,B> *v=vh.v;
		vector<Edge<A,B>*>& edges=v->getEdges();

		for (unsigned int i = 0; i < edges.size(); ++i) {

			unsigned int weight=cost(edges[i],v);
			Vertex<A,B> *v2=edges[i]->getDest(v);

			if(v->getCost() + weight < v2->getCost()){

				v2->setCost(v->getCost()+weight);
				v2->setLastVertex(v);
				vh.v=v2;
				typename list<VertexHandler<A,B> >::iterator itr = find(listVH.begin(),listVH.end(),vh);

				if(itr == listVH.end()){
					vh.v=v2;
					listVH.push_back(vh);
				}
			}
		}
	}

	if(finish->getLastVertex()==NULL)
		return res;

	Vertex<A,B>* vaux=finish;

	while(vaux != NULL){
		res.push_front(vaux);
		vaux=vaux->getLastVertex();
	}


	return res;

}


template <class A,class B>
vector<Vertex<A,B> *> Graph<A,B>::bfs(Vertex<A,B> *v){
	massiveReset();
	vector<Vertex<A,B> *> res;

	queue<Vertex<A,B> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<A,B> *v1 = q.front();
		q.pop();
		res.push_back(v1);
		typename vector<Edge<A,B> >::iterator it=v1->edges.begin();
		typename vector<Edge<A,B> >::iterator ite=v1->edges.end();
		for (; it!=ite; it++) {
			Vertex<A,B> *d = it->getDest();
			if (!d->visited) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}


template <class A,class B>
bool Graph<A,B>::isConex(){
	for (int i = 0; i < verts.size(); ++i) {
		if(bfs(verts[i]).size() != verts.size())
			return false;
	}
	return true;
}



