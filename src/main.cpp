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
#include "utils.h"

using namespace std;

void MiniSlave(Node n1, Node n2,Way w, Graph<Node,Way>& g){
	w.setDistance(n1.calcDist(n2));
	g.addEdge(n1,n2,w);
	g.addEdge(n2,n1,w);
}

typedef struct WayInfo{
	Way w;
	bool bothWays;
}WayInfo;


void welcomeMenu();
void clearScreen();
unsigned int calcDist(Node n);

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
	GraphViewer *gv = new GraphViewer(1000,1000, false);
	gv->createWindow(1000, 1000);
	gv->defineEdgeDashed(false);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("red");
	gv->defineEdgeCurved(false);


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
		g.addVertex(n, id);
		gv->addNode(id, lat*1.5, lon*1.5);
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

		Way w(id, n, t);//calcular distancia...

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


		w.setDistance(n1.calcDist(n2));

		g.addEdge(n1,n2,w);
		if(wI.bothWays){
			g.addEdge(n2,n1,w);
		}/**/

		gv->addEdge(count,node1,node2,!wI.bothWays);
		gv->setEdgeThickness(count,25);

		stringstream s;
		s << "dist-> " << w.getDistance() << " n: "<< w.getName() <<" p: " << w.getPrice() <<" id: " << w.getID();
		gv->setEdgeLabel(count,s.str());
		count ++;
	}
	file.close();
	gv->rearrange();

	return g;
}
/**/

int main(){

	welcomeMenu();

	Way caminho(0,"Bla", Transport::BUS );
	Graph<Node, Way> graph;

	Node nA(0, 21 , 33);
	Node nB(1, 22, 22);
	Node nC(2, 21 , 33);
	Node nD(3, 22, 22);
	Node nE(4, 21 , 33);
	Node nF(5, 22, 22);
	Node nG(6, 21 , 33);

	graph.addVertex(nA,0);
	graph.addVertex(nB,1);
	graph.addVertex(nC,2);
	graph.addVertex(nD,3);
	graph.addVertex(nE,4);
	graph.addVertex(nF,5);
	graph.addVertex(nG,6);

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
	clearScreen();
	cout << "Vou procurar os vertices!" << endl;
	Vertex<Node,Way>* inicio = graph.getVertex(22);
	Vertex<Node,Way>* fim = graph.getVertex(43);
	cout << "Encontrei os vertices!" << endl;

	list<Vertex<Node,Way>*> path = graph.findWay(inicio,fim,distCost);
	cout << "Encontrei o caminho!" << endl;
	list<Vertex<Node,Way>*>::const_iterator it;
	for(it = path.begin(); it != path.end(); it++){
		(*it)->imprime();
	}
	cout << endl;
	cout << "PASSEI!" << endl;
	getch();

	return 0;
}

//Menu


void welcomeMenu(){
	setcolor(9);
	cout << " ___      _        ___  _                          " << endl;
	cout << "|_ _|_ _ <_> ___  | . \\| | ___ ._ _ ._ _  ___  _ _ " << endl;
	cout << " | || '_>| || . \\ |  _/| |<_> || ' || ' |/ ._>| '_>" << endl;
	cout << " |_||_|  |_||  _/ |_|  |_|<___||_|_||_|_|\\___.|_|  " << endl;
	cout << "            |_|                                    " << endl;

	setcolor(15);
}

void clearScreen(){
	//system("cls");
}
