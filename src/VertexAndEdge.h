#ifndef VERTEXANDEDGE_H_
#define VERTEXANDEDGE_H_

#include <string>
#include <vector>
#include <iostream>
#include "Transport.h"

using namespace std;

template <class A,class B>
class Graph;

template<class A, class B>
class Vertex;

	/**
	 * Classe Edge
	*
	*	Classe que contém todas as informações relativas a uma Edge
	*/

template<class A, class B>
class Edge {

	Vertex<A,B>* dest;
	B weights;

public:

	/**
	 * Construtor Edge()
	*	\param dest Vertex de destino
	*	\param weights Peso associado
	*/
	Edge(Vertex<A,B>* dest,B weights);

	/**
	* getDest()
	* \return devolve o Vertex de destino
	*/
	Vertex<A,B>* getDest();

	/**
	 * getWeights()
	*	\return devolve o Peso associado
	*/
	B getWeights() const;

};

	/**
	 * Classe Vertex
	*
	*	Classe que contém todas as informacoes relativas a um Vertex
	*/
template<class A, class B>
class Vertex{

	unsigned int id;
	bool visited;
	bool insideQueue;
	//conectivity things
	int num;
	int low;


	A info;

	vector<Edge<A,B> > edges;
	unsigned int cost;

	Vertex<A,B> *lastVertex;

public:

	friend class Graph<A,B>;

	/**
	 * Construtor Vertex()
	*	\param info informacao associada ao Vertex
	*	\param id id do vertice atual
	*/
	Vertex(A info, unsigned int id);
	/**
	 * Construtor Vertex()
	*	\param info informacao associada ao Vertex
	*/
	Vertex(A info);
	/**
	* getCost()
	*	\return custo acumulado
	*/
	unsigned int getCost();
	/**
	*  setCost()
	*	\param newCost novo custo a defenir
	*/
	void setCost(unsigned int newCost);
	virtual ~Vertex();
	/**
	*  reset()
	*	Coloca os membros-dado com valor por defeito
	*/
	void reset();
	/**
	*  addEdge()
	*	\param edge Edge a ser adicionada ao Vertex
	*/
	void addEdge(Edge<A,B> edge);
	/**
	*  getInfo()
	*	\return informacao associada ao Vertex
	*/

	A getInfo();
	/**
	*  getEdges()
	*	\return Edges associadas ao Vertex
	*/
	vector<Edge<A,B> > getEdges();
	/**
	 * setLastVertex()
	 * \param v novo vertice a ser defenido
	 */
	void setLastVertex(Vertex<A,B> *v);
	/**
	* getLastVertex()
	* \return ultimo Vertex
	 */
	Vertex<A,B>* getLastVertex();
	/**
	 * imprime()
	 *
	 */
	void imprime();
	/**
	 * removeEdgeTo()
	 * \param dest Vertex de Destino ao qual o Vertex atual esta conectado
	 * \return true se removido com sucesso, falso caso contrario
	 */
	bool removeEdgeTo(Vertex<A,B> *dest);

	/**
	* getID()
	* \return id do Vertex
	*/
	unsigned int getID();
	/**
	* isInsideQueue()
	* \return true se esta dento da lista
	*/
	bool isInsideQueue() const;
	/**
	* setInsideQueue()
	* \param newValue novo valor a ser atualizado
	*/

	void setInsideQueue(bool newValue);
};

template<class A, class B>
unsigned int Vertex<A,B>::getID(){
	return id;
}

template<class A, class B>
Vertex<A,B>::Vertex(A info, unsigned int id) {
	this->info = info;
	this->id = id;
	this->cost=-1;
	this->lastVertex=NULL;
}

template<class A, class B>
Vertex<A,B>::Vertex(A info) {
	this->info = info;
	this->id = 0;
	this->cost=-1;
	this->lastVertex=NULL;
}

template<class A, class B>
Vertex<A,B>::~Vertex() {
}

template<class A, class B>
void Vertex<A,B>::addEdge(Edge<A,B> edge){
	edges.push_back(edge);
}

template<class A, class B>
void Vertex<A,B>::imprime(){
	cout << " | " << info << " | ";
}

template<class A, class B>
vector<Edge<A,B> > Vertex<A,B>::getEdges(){
	return edges;
}

template<class A, class B>
inline bool operator==(const Vertex<A,B>& v1, const Vertex<A,B>& v2){

	return (v1.getInfo() == v2.getInfo());

}


template<class A, class B>
Edge<A,B>::Edge(Vertex<A,B>* dest,B weights) {
	this->dest = dest;
	this->weights = weights;
}

template<class A, class B>
B Edge<A,B>::getWeights() const{
	return weights;
}

template<class A, class B>
Vertex<A,B>* Edge<A,B>::getDest(){
	return dest;
}

template<class A, class B>
void Vertex<A,B>::reset(){
	cost=-1;
	lastVertex=NULL;
	visited=false;
	insideQueue=false;
}

template<class A, class B>
bool Vertex<A,B>::isInsideQueue() const{
	return insideQueue;
}

template<class A, class B>
void Vertex<A,B>::setInsideQueue(bool newValue){
	insideQueue = newValue;
}



template<class A, class B>
unsigned int Vertex<A,B>::getCost(){
	return cost;
}

template<class A, class B>
void Vertex<A,B>::setCost(unsigned int newCost){
	cost=newCost;
}

template<class A, class B>
void Vertex<A,B>::setLastVertex(Vertex<A,B> *v){
	lastVertex=v;
}

template<class A, class B>
A Vertex<A,B>::getInfo(){
	return info;
}

template<class A, class B>
Vertex<A,B>* Vertex<A,B>::getLastVertex(){
	return lastVertex;
}

template<class A, class B>
bool Vertex<A,B>::removeEdgeTo(Vertex<A,B> *dest){
	for(unsigned int i = 0; i < edges.size(); i++){
		if(edges[i].GeDest() == dest){
			edges.erase(edges.begin() + i);
			return true;
		}
	}
	return false;
}

#endif
