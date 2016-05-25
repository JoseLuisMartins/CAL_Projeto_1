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
#include <vector>


using namespace std;

template <class A,class B>

/**
 * Classe responsável pela representacao do grafo
 */
class Graph {
	/**
	 * vector que armazena os vertices contidos no grafo
	 */
	vector<Vertex<A,B>*> verts;

	void findArt(Vertex<A,B>* v, vector<Vertex<A,B>*>& vect, int& counter,Vertex<A,B>* root);

	void dfs(Vertex<A,B>* v, vector<Vertex<A,B> *>& res);

public:

	/**
	 * construtor default do grafo
	 */
	Graph(){}

	/**
	 \return  devolve um vetor com todos os vertices do grafo
	 */
	vector<Vertex<A,B>*> getVerts();
	/**
	 * Adiciona um vertice ao grafo
	 \param inf informação do vertice adicionado
	 \return  devolve um booleano indicando o sucesso da operação
	 */
	bool addVertex(A inf);
	/**
	 * Adiciona um vertice ao grafo
	\param inf informação do vertice adicionado
	\param indice do vertice
	\return  devolve um booleano indicando o sucesso da operação
	 */
	bool addVertex(A inf,unsigned int indice);
	/**
	 * Remove um vertice do grafo
	\param inf informação do vertice adicionado
	\param indice do vertice
	\return  devolve um booleano indicando o sucesso da operação
	 */
	bool removeVertex(A inf);
	/**
	 * Adiciona uma aresta ao grafo
	\param source informacao do vertice de onde parte a aresta
	\param dest informacao do vertice onde termina a aresta
	\param w informacao da aresta que vai ser adicionada ao grafo
	\return  devolve um booleano indicando o sucesso da operação
	 */
	bool addEdge(A source, A dest, B w);
	/**
	 * Remove uma aresta ao grafo
	\param source informacao do vertice de onde parte a aresta
	\param dest informacao do vertice onde termina a aresta
	\return  devolve um booleano indicando o sucesso da operação
	 */
	bool removeEdge(A source,A dest);

	/**
	 * Algoritmo de pesquisa em largura (Breadth first search)
	\param v Vertice onde inicia a pesquisa
	\return  devolve um vetor com os vertices do grafo que foram encontrados na pesquisa
	 */
	vector<Vertex<A,B> *> bfs(Vertex<A,B> *v);
	/**
	 * Algoritmo de pesquisa em profundidade (Depth first search)
	\return  devolve um vetor com os vertices do grafo que foram encontrados na pesquisa
	 */
	vector<Vertex<A,B> *> dfs();
	/**
	 * Metodo responsavel por avaliar a conectividade do grafo
	\return  devolve um boolean indicando a conectividade(true) ou a não conectividade(false) do grafo
	 */
	bool isConex();
	/**
	\param indice indice do vertice que se pretende obter
	\return  devolve um vertice com o indice passado por argumento ou NULL se não existir nenhum vertice com esse indice
	 */
	Vertex<A,B>* getVertex(int indice);
	/**
	 *Metodo que procura os pontos de articulacao do grafo
	\return devolve um vetor com os vertices que são pontos de articulacao do grafo
	 */
	vector<Vertex<A,B> *> findArt();
	/**
	 *Consiste na implementacao do algoritmo de Djisktra para encontrar o caminho mais curto
	\param start ponto de partida
	\param finish ponto de chegada
	\param cost apontador para funcao que permite determinar o custo de cada movimentacao
	\return retorna uma lista de vertices que representa o caminho mais curto entre o vertice start e o vertice finish
	 */
	list<Vertex<A,B>*>  findWay(Vertex<A,B> *start,Vertex<A,B> *finish, int(*cost)(Edge<A,B>*,  Vertex<A,B>* ));
	/**
	 *Metodo responsavel por fazer reset a todos os vertices
	 */
	void massiveReset();

	/**
	 * destrutor do grafo
	 */
	virtual ~Graph(){}

	/**
	 * imprime todos os vertices do grafo
	 */
	void imprime();

	/*
	 *	Algoritmo de Knuth-Morris-Pratt para pesquisa exata
	 */
	vector<Vertex<A,B>*> findStationExat(string toSearch);

	vector<Vertex<A,B>*> findStationAprox(string toSearch);

	vector<Edge<A,B>*> findLineExat(string toSearch);

	vector<Edge<A,B>*> findLineAprox(string toSearch);

	vector<Edge<A,B>*> getWays();
};

template<class A, class B>
vector<Vertex<A,B>*> Graph<A,B>::getVerts(){
	return verts;
}

template<class A, class B>
bool Graph<A,B>::addVertex(A inf,unsigned int indice){
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->info == inf)
			return false;
	}
	Vertex<A,B>* a = new Vertex<A,B>(inf,indice);
	verts.push_back(a);
	return true;
}

template<class A,class B>
Vertex<A,B>* Graph<A,B>::getVertex(int indice){
	for(unsigned int i = 0; i < verts.size(); i++){
		if(verts[i]->getID() == indice)
			return verts[i];
	}
	return NULL;
}

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

	vector<VertexHandler<A,B> > listVH;
	VertexHandler<A,B> vh;
	vh.v=start;
	listVH.push_back(vh);
	start->setCost(0);

	while(!listVH.empty()){


		vh= listVH.front();
		listVH.erase(listVH.begin());
		vh.v->setInsideQueue(false);

		Vertex<A,B> *v=vh.v;
		vector<Edge<A,B> > edges = v->getEdges();
		for (unsigned int i = 0; i < edges.size(); ++i) {
			unsigned int weight= cost(&edges[i],v);
			Vertex<A,B> *v2 = edges[i].getDest();

			if(v->getCost() + weight < v2->getCost()){
				v2->setCost(v->getCost()+weight);
				v2->setLastVertex(v);
				vh.v=v2;

				typename vector<VertexHandler<A,B> >::iterator itr = listVH.end();

				if(v2->isInsideQueue())
					itr = find(listVH.begin(),listVH.end(),vh);

				if(itr == listVH.end()){

					listVH.push_back(vh);
					v2->setInsideQueue(true);
					push_heap(listVH.begin(), listVH.end());

				}else
					make_heap(listVH.begin(), itr);

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
vector<Vertex<A,B> *> Graph<A,B>::dfs(){
	typename vector<Vertex<A,B>*>::const_iterator it= verts.begin();
	typename vector<Vertex<A,B>*>::const_iterator ite= verts.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<Vertex<A,B>* > res;
	it=verts.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class A, class B>
void Graph<A,B>::dfs(Vertex<A,B> *v,vector< Vertex<A,B> *> &res){
	v->visited = true;
	res.push_back(v);
	typename vector<Edge<A,B> >::iterator it= (v->edges).begin();
	typename vector<Edge<A,B> >::iterator ite= (v->edges).end();
	for (; it !=ite; it++)
		if ( it->getDest()->visited == false )
			dfs(it->getDest(), res);
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
	int t = 0;

	for(int i = 0; i < v->edges.size(); i++){
		Vertex<A,B>* w = v->edges[i].getDest();
		if(!w->visited){
			if(v == root){
				t++;
			}
			w->setLastVertex(v);
			findArt(w , vect, counter, root);

			if(w->low >= v->num){
				if(v!=root || t > 1)
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

template <class A, class B>
vector<Edge<A,B>*> Graph<A,B>::getWays(){
	vector<Edge<A,B>*> res;
	bool rep = false;
	for(unsigned int i = 0; i < verts.size(); i++){
		for(unsigned int j = 0; j < verts[i].getEdges().size(); j++){
			for(unsigned int k = 0; k < res.size(); k++)
				if(res[k] == verts[i].getEdges()[j]){
					rep = true;
					break;
				}
			if(rep){
				rep = false;
				continue;
			}
			res.push_back(&(verts[i].getEdges()[j]));
		}
	}
	return res;
}

/*Pesquisa Exata | Knuth-Morris-Pratt*/
template <class A, class B>
vector<Vertex<A,B>*> Graph<A,B>::findStationExat(string toSearch){

	vector<Vertex<A,B>*> res;

	for(unsigned int i = 0; i < verts.size(); i++){
		if(findByNameExat(verts[i]->getInfo().getParagem(),toSearch)){
			res.push_back(verts[i]);
		}
	}

	return res;
}

template <class A, class B>
vector<Vertex<A,B>*> Graph<A,B>::findStationAprox(string toSearch) {
	vector<Vertex<A,B>*> res;

	if(verts.size() == 0)
		return res;

	int tmp;
	int min = findByNameAprox(verts[0]->getInfo().getParagem(),toSearch);
	res.push_back(verts[0]);
	for(unsigned int i = 0; i < verts.size(); i++){
		tmp = findByNameAprox(verts[i]->getInfo().getParagem(),toSearch);
		if(tmp < min){
			min = tmp;
			res.erase(res.begin(),res.end());
			res.push_back(verts[i]);
		} else if (tmp == min){
			res.push_back(verts[i]);
		}
	}

	return res;
}

template <class A, class B>
vector<Edge<A,B>*> Graph<A,B>::findLineExat(string toSearch){

	vector<Edge<A,B>*> ways = getWays();
	vector<Edge<A,B>*> res;

	for(unsigned int i = 0; i < ways.size(); i++){
		if(findByNameExat(ways[i]->getWeights().getLinha(),toSearch)){
			res.push_back(ways[i]);
		}
	}

	return res;
}

template <class A, class B>
vector<Edge<A,B>*> Graph<A,B>::findLineAprox(string toSearch) {
	vector<Edge<A,B>*> res;
	vector<Edge<A,B>*> ways = getWays();

	if(ways.size() == 0)
		return res;

	int tmp;
	int min = findByNameAprox(ways[0]->getWeights().getLinha(),toSearch);
	res.push_back(ways[0]);
	for(unsigned int i = 0; i < ways.size(); i++){
		tmp = findByNameAprox(ways[i]->getWeights().getLinha(),toSearch);
		if(tmp < min){
			min = tmp;
			res.erase(res.begin(),res.end());
			res.push_back(ways[i]);
		} else if (tmp == min){
			res.push_back(ways[i]);
		}
	}

	return res;
}

#endif /* GRAPH_H_ */
