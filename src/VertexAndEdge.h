#ifndef VERTEXANDEDGE_H_
#define VERTEXANDEDGE_H_

#include <string>
#include <vector>
#include <iostream>

enum Transport {

	NONE,
	TRAIN,
	BUS,
	SUBWAY

};

using namespace std;

template<class A, class B>
class Vertex;

template<class A, class B>
class Edge {

	Vertex<A,B>* dest;
	B weights;

public:
	Edge(Vertex<A,B>* dest,B weights);

	Vertex<A,B>* GetDest();

	int getWeights() const;

};

template<class A, class B>
class Vertex{

	unsigned int id;

	A info;

	vector<Edge<A,B> > edges;
	unsigned int cost;
	Vertex<A,B> *lastVertex;

public:

	Vertex(A info, unsigned int id);
	Vertex(A info);
	unsigned int getCost();
	void setCost(int newCost);
	virtual ~Vertex();
	void reset();
	void addEdge(Edge<A,B> edge);
	A getInfo() const;
	vector<Edge<A,B> > getEdges();
	void setLastVertex(Vertex<A,B> *v);
	Vertex<A,B>* getLastVertex();
	void imprime();
	bool removeEdgeTo(Vertex<A,B> *dest);
	void addEdge(Edge<A,B>* d,B w);
};

template <class A, class B>
inline bool operator==(const Vertex<A,B>& v1, const Vertex<A,B>& v2);

#endif
