#ifndef VERTEXANDEDGE_H_
#define VERTEXANDEDGE_H_

#include <string>
#include <vector>
#include <iostream>
#include "utils.h"

using namespace std;

class Vertex;

class Edge {

	Vertex* p1;
	Vertex* p2;
	int price;
	int distance;
	int duration;

public:
	Edge(Vertex* p1, Vertex* p2,int price, int distance, int duration);

	Vertex* GetDest(Vertex* p);

	int getPrice() const;
	int getDistance() const;
	int getDuration() const;


	virtual ~Edge();
};
class Vertex {

	string name;
	Transport type;
	vector<Edge*> edges;

public:

	Vertex(string name,enum Transport type);

	virtual ~Vertex();

	string getName() const;
	Transport getType() const;
	void addEdge(Edge* edge);
	void imprime();
};

inline bool operator!=(const Vertex& v1, const Vertex& v2);

#endif
