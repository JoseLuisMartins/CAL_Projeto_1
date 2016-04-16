


#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

#include "Way.h"
#include "Transport.h"
#include "Node.h"
#include "Graph.h"
#include "VertexAndEdge.h"

using namespace std;

void MiniSlave(Node n1, Node n2,Way w, Graph<Node,Way>& g){
	g.addEdge(n1,n2,w);
	g.addEdge(n2,n1,w);
}

int main(){

	cout<< "Batata\n";

	Way caminho(0,"Bla", 20, 10,Transport::BUS );
	Graph<Node, Way> graph;

	Node nA(0, 21 , 33);
	Node nB(1, 22, 22);
	Node nC(2, 21 , 33);
	Node nD(3, 22, 22);
	Node nE(4, 21 , 33);
	Node nF(5, 22, 22);
	Node nG(6, 21 , 33);

	graph.addVertex(nA);
	graph.addVertex(nB);
	graph.addVertex(nC);
	graph.addVertex(nD);
	graph.addVertex(nE);
	graph.addVertex(nF);
	graph.addVertex(nG);

	MiniSlave(nA,nB,caminho,graph);
	MiniSlave(nA,nD,caminho,graph);

	MiniSlave(nB,nC,caminho,graph);

	MiniSlave(nC,nD,caminho,graph);
	MiniSlave(nC,nG,caminho,graph);

	MiniSlave(nD,nE,caminho,graph);
	MiniSlave(nD,nF,caminho,graph);
	MiniSlave(nE,nF,caminho,graph);

	vector<Vertex<Node,Way>*> info;
	graph.massiveReset();
	info = graph.findArt();
	cout <<"PAssou\n";
	for(int i = 0; i < info.size(); i++){
		cout << info[i]->getInfo().getID() << " | ";
	}


	cout<< "\nMussalhau";


	getch();

	return 0;

}
