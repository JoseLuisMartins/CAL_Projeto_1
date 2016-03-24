/*
 * Vertex.h
 *
 *  Created on: 24/03/2016
 *
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>
#include <vector>
#include "Edge.h"
#include "utils.h"
using namespace std;

class Vertex {

	string name;
	Transport type;
	vector<Edge&> edges;

public:

	Vertex(string name, Transport type);

	virtual ~Vertex();

	string getName() const;
	Transport getType() const;
	void addEdge(Edge& edge);
};

inline bool operator!=(const Vertex& v1, const Vertex& v2);

#endif /* VERTEX_H_ */
