#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

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

typedef struct WayInfo{
	Way w;
	bool bothWays;
}WayInfo;


Graph<Node, Way> loadTxt(){
	map<int,Node> nodes;
	map<int,WayInfo> ways;

	stringstream ss;
	string line;
	ifstream file;
	Graph<Node, Way> g;
	string lixo;

	file.open("vertex_info.txt");
	if(!file.good())
		cout << "\nErro!!!\n";
	while(getline(file,line)){
		ss.clear();
		ss.str(line);
		int id;
		double lat, lon;
		ss >> id >> lixo >> lat >> lixo >> lon;
		Node n(id,lat,lon);
		nodes[id] = n;
		g.addVertex(n);
	}
	file.close();

	file.open("edge_info.txt");
	while(getline(file,line)){
		ss.clear();
		ss.str(line);
		int id;
		string n;
		bool isTwoWay = true;
		Transport::Type t;
		ss >> id >> lixo >> n;
		if(n != ";"){
			string tmp;
			ss >> tmp;
			if(tmp == "False")
				isTwoWay=false;

			t = Transport::SUBWAY;//Metro ou Comboio
		} else {
			string tmp;
			ss >> tmp;
			if(tmp == "False")
				isTwoWay=false;

			t = Transport::BUS;//Onibus
		}

		Way w(id, "Bla", 20, 20, t);

		WayInfo wI;
		wI.bothWays=isTwoWay;
		wI.w = w;

		ways[id] = wI;

	}
	file.close();

	file.open("connection_info.txt");
	while(getline(file,line)){
		ss.clear();
		ss.str(line);
		int wayID, node1, node2;
		ss >> wayID >> lixo >> node1 >> lixo >> node2;

		WayInfo wI = ways.find(wayID)->second;
		Way w = wI.w;
		Node n1 = nodes.find(node1)->second;
		Node n2 = nodes.find(node2)->second;

		g.addEdge(n1,n2,w);
		if(wI.bothWays){
			g.addEdge(n2,n1,w);
		}/**/



	}
	file.close();
	return g;
}
/**/

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
	for(unsigned int i = 0; i < info.size(); i++){
		cout << info[i]->getInfo() << " | ";
	}

	graph = loadTxt();
	cout <<"Calculando Cenas\n";
	info = graph.findArt();
	cout <<"PAssou\n";
	graph.imprime();
	for(unsigned int i = 0; i < info.size(); i++){
		cout << info[i]->getInfo()<< " | ";
	}



	cout<< "\nMussalhau";


	getch();

	return 0;

}
