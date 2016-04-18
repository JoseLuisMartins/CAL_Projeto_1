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
#include "graphviewer.h"


using namespace std;

void MiniSlave(Node n1, Node n2,Way w, Graph<Node,Way>& g){
	g.addEdge(n1,n2,w);
	g.addEdge(n2,n1,w);
}

typedef struct WayInfo{
	Way w;
	bool bothWays;
}WayInfo;


void welcomeMenu();
void clearScreen();

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str);
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

Graph<Node, Way> loadTxt(){
	map<int,Node> nodes;
	map<int,WayInfo> ways;

	//config graph viewer
	GraphViewer *gv = new GraphViewer(1000,1000, true);
	gv->createWindow(800, 800);
	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");



	string line;
	ifstream file;
	Graph<Node, Way> g;
	char lixo;

	file.open("vertex_info.txt");
	if(!file.good())
		cout << "\nErro!!!\n";
	while(getline(file,line)){
		stringstream ss(line);
		int id;
		long lat, lon;
		ss >> id >> lixo >> lat >> lixo >> lon;
		Node n(id,lat,lon);
		nodes[id] = n;
		g.addVertex(n);
		gv->addNode(id);
	}
	file.close();

	file.open("edge_info.txt");
	while(getline(file,line)){
		stringstream ss(line);
		int id;
		vector<string> res = split(line, ';');
		string n = res[1];
		bool isTwoWay = true;
		Transport::Type t;
		stringstream(res[0]) >> id;

		if(res[2] == "False")
			isTwoWay=false;

		t = Transport::BUS;

		Way w(id, n, 20, 20, t);

		WayInfo wI;
		wI.bothWays=isTwoWay;
		wI.w = w;

		ways[id] = wI;

	}
	file.close();
	int count = 0;
	file.open("connection_info.txt");
	while(getline(file,line)){
		stringstream ss(line);
		cout << ss.str() << endl;
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

		gv->addEdge(count,node1,node2,!wI.bothWays);
		gv->setEdgeLabel(count,w.getName());
		count ++;
	}
	file.close();
	gv->rearrange();

	return g;
}
/**/

int main(){

	welcomeMenu();

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
	cout << endl;
	graph = loadTxt();
	cout <<"Calculando Cenas\n";
	info = graph.findArt();

	clearScreen();
	cout <<"PAssou\n";
	graph.imprime();
	for(unsigned int i = 0; i < info.size(); i++){
		cout << "\n |" << info[i]->getInfo()<< " | ";
	}

	getch();

	return 0;
}

//Menu

void welcomeMenu(){

	cout << "*********| CAL - TripPlanner |*********" << endl;

}

void clearScreen(){
	system("cls");
}
