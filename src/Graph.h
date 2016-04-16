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
#include <queue>

using namespace std;

template <class A,class B>
class Graph {

	vector<Vertex<A,B>*> verts;
	void findArt(Vertex<A,B>* v, vector<Vertex<A,B>*>& vect, int& counter,Vertex<A,B>* root);

public:
	Graph(){}

	bool addVertex(A inf);
	bool removeVertex(A inf);
	bool addEdge(A source, A dest, B w);
	bool removeEdge(A source,A dest);
	vector<Vertex<A,B> *> bfs(Vertex<A,B> *v);
	bool isConex();

	vector<Vertex<A,B> *> findArt();



	list<Vertex<A,B>*>  findWay(Vertex<A,B> *start,Vertex<A,B> *finish, int(*cost)(Edge<A,B>*,  Vertex<A,B>* ));

	void massiveReset();
	virtual ~Graph(){}

	void imprime();
};

template<class A, class B>
void Graph<A,B>::imprime(){
	cout << "Info:" << verts.size() << endl;

	for(int i =0 ; i <verts.size(); i++){
		cout << verts[i]->info << " ";
	}
}

template <class A, class B>
bool Graph<A,B>::addVertex(A inf){
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->info == inf)
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

template<class A, class B>
vector<Vertex<A,B> *> Graph<A,B>::findArt(){
	massiveReset();
	vector<Vertex<A,B>* > res;
	int counter = 0;

	for(int i =0 ; i < verts.size(); i++){
		if(verts[i]->edges.size() > 1){
			findArt(verts[i], res, counter, verts[i]);
			break;
		}
	}

	return res;
}

template<class A, class B>
void Graph<A,B>::findArt(Vertex<A,B>* v, vector<Vertex<A,B>*>& vect, int& counter, Vertex<A,B>* root){
	v->visited = true;
	v->low = v->num = ++counter;

	for(int i = 0; i < v->edges.size(); i++){
		Vertex<A,B>* w = v->edges[i].getDest();
		if(!w->visited){
			w->setLastVertex(v);
			findArt(w , vect, counter, root);

			if(w->low >= v->num){
				if(v!=root)
					vect.push_back(v);
			}

			v->low = min(v->low, w->low);
		}
		else
		{
			if(v->getLastVertex() != NULL){
				if( !(v->getLastVertex()->info == w->info))
					v->low = min (v->low, w->num);
			}
		}
	}

}


template <class A,class B>
bool Graph<A,B>::isConex(){
	for (int i = 0; i < verts.size(); ++i) {
		if(bfs(verts[i]).size() != verts.size())
			return false;
	}
	return true;
}

#endif /* GRAPH_H_ */
