#include <iostream>
#include <cmath>
#include <conio.h>
#include <iomanip>

#include "Graph.h"
#include "VertexAndEdge.h"
using namespace std;

void MiniSlave(Vertex& v1, Vertex& v2, Edge&e){
	v1.addEdge(&e);
	v2.addEdge(&e);
}

int main() {
	//IntraLigacoes

	Graph grafo;

	Vertex p1 ("P1",NONE);
	grafo.addVertex(&p1);

	Vertex p1a ("P1A",BUS);
	grafo.addVertex(&p1a);

	Vertex p1b ("P1B",SUBWAY);
	grafo.addVertex(&p1b);

	Vertex p1c ("P1C",TRAIN);
	grafo.addVertex(&p1c);

	Vertex p2 ("P2",NONE);
	grafo.addVertex(&p2);

	Vertex p2a("P2A",BUS);
	grafo.addVertex(&p2a);

	Vertex p2b("P2B",SUBWAY);
	grafo.addVertex(&p2b);

	Vertex p3("P3",NONE);
	grafo.addVertex(&p3);

	Vertex p3a("P3A",BUS);
	grafo.addVertex(&p3a);

	Vertex p4("P4",NONE);
	grafo.addVertex(&p4);

	Vertex p4b("P4B",SUBWAY);
	grafo.addVertex(&p4b);

	Vertex p4c("P4C",TRAIN);
	grafo.addVertex(&p4c);

	Vertex p5("P5",NONE);
	grafo.addVertex(&p5);

	Vertex p5c("P5C",TRAIN);
	grafo.addVertex(&p5c);


	//P1
	Edge e1(&p1,&p1a,	180,	5,	3);
	MiniSlave(p1,p1a,e1);

	Edge e2(&p1,&p1b,	180,	5,	1);
	MiniSlave(p1,p1b,e2);

	Edge e3(&p1,&p1c,	180,	5,	2);
	MiniSlave(p1,p1c,e3);

	//P2
	Edge e4(&p2,&p2a, 180,	6,	3);
	MiniSlave(p2,p2a,e4);

	Edge e5(&p2,&p2b, 185,	6,	2);
	MiniSlave(p2,p2b,e5);

	//P4
	Edge e6(&p4,&p4b, 180,	7,	1);
	MiniSlave(p4,p4b,e6);

	Edge e7(&p4,&p4c, 185,	6,	2);
	MiniSlave(p4,p4c,e7);

	//P3
	Edge e8(&p3,&p3a, 50,	7,	2);
	MiniSlave(p3,p3a,e8);

	//P5
	Edge e9(&p5,&p5c, 55,	9,	2);
	MiniSlave(p5,p5c,e9);


	//Inter Ligacoes
	Edge e10(&p1a,&p2a, 300,	40,	10);
	MiniSlave(p1a,p2a,e10);

	Edge e11(&p1b,&p2b, 370,	35,	7);
	MiniSlave(p1b,p2b,e11);

	Edge e12(&p1b,&p4b, 420,	45,	9);
	MiniSlave(p1b,p4b,e12);

	Edge e13(&p1c,&p4c, 420,	55,	7);
	MiniSlave(p1c,p4c,e13);

	Edge e14(&p2b,&p4b, 420,	30,	7);
	MiniSlave(p2b,p4b,e14);

	Edge e15(&p2a,&p3a, 100,	90,	11);
	MiniSlave(p2a,p3a,e15);

	Edge e16(&p4c,&p5c, 100,	80,	11);
	MiniSlave(p4c,p5c,e16);

	grafo.imprime();



	return 0;
}

