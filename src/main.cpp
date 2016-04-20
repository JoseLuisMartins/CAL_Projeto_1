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

Graph<Node, Way> graph;
Vertex<Node,Way>* inicio = NULL;
Vertex<Node,Way>* fim = NULL;
int (*funcao)(Edge<Node,Way>* e, Vertex<Node,Way>* v);

GraphViewer *gv = new GraphViewer(1000,1000, false);


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
void menuConetividade();
void menuViajarBegin();
void menuViajarEnd();
void menuViajarModo();
void menuDisplayViagem();
void menuSelection();
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
		//cout << ss.str() << endl;
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

		gv->addEdge(w.getID(),node1,node2,!wI.bothWays);
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

//Menu
void menuSelection(){
	welcomeMenu();
	char userChoice = 0;
	cout << endl;
	cout << "Escolha uma opcao selecionando o numero que a antecede." << endl << endl;
	cout << "1. Viajar;" << endl;
	cout << "2. Avaliar Conectividade;" << endl;
	cout << "3. Cenas de BiFeS;" << endl;
	cout << "4. Sair." << endl;
	cin >> userChoice;
	//userChoice = getch();

	while(!(userChoice == '1' || userChoice == '2' || userChoice == '3' || userChoice == '4')){
		cout << "Opcao errada, por favor tente novamente!" << endl;
		cin >> userChoice;
		//userChoice = getch();
	}

	switch(userChoice){
	case '1':
		menuViajarBegin();
		menuViajarEnd();
		menuViajarModo();
		menuDisplayViagem();
		inicio = NULL;
		fim = NULL;
		break;
	case '2':
		menuConetividade();
		break;
	case '3':
		//Chamar menu de bfs
		break;
	case '4':
		return;
		break;
	}
	menuSelection();
}

void menuConetividade(){
	welcomeMenu();
	cout << "-> Conetividade da rede de transportes <-" << endl;
	cout << "Lista de pontos de articulacao: " << endl;
	setcolor(12);
	cout << endl << endl << endl;
	//calcular os pontos e imprimir
	setcolor(15);
	cout << "Estes sao pontos criticos da rede que, na eventualidade de um" << endl;
	cout <<	"corte na via duas partes da rede ficarao inacessiveis entre si." << endl;
	setcolor(12);
	cout << "Prima qualquer tecla para voltar ao inicio.";
	setcolor(15);
	getch();
	return;
}

void menuDisplayViagem(){
	welcomeMenu();
	list<Vertex<Node,Way>*> path = graph.findWay(inicio,fim,funcao);
	cout << "Ponto de Partida: ";
	inicio->imprime();
	cout << endl;
	cout << "Ponto de Chegada: ";
	fim->imprime();
	cout << endl;

	list<Vertex<Node,Way>*>::const_iterator it = path.begin();
	Vertex<Node,Way>* temp = NULL;

	for(it = path.begin(); it != path.end(); it++){

		if(temp != NULL){
			for(unsigned int i = 0; i < temp->getEdges().size() ; i ++){
				if(temp->getEdges()[i].getDest() == (*it)){
					gv->setEdgeColor(temp->getEdges()[i].getWeights().getID(), "black");
					break;
				}
			}
		}
		temp = *it;

		(*it)->imprime();
	}
	gv->rearrange();

	cout << endl << endl;
	setcolor(12);
	cout << "Prima qualquer tecla para voltar ao inicio.";
	setcolor(15);
	getch();
	return;
}

void menuViajarModo(){
	welcomeMenu();
	cout << "Ponto de Partida: ";
	inicio->imprime();
	cout << endl;
	cout << "Ponto de Chegada: ";
	fim->imprime();
	cout << endl;
	unsigned int userChoice;
	cout << "1. Menor distancia" << endl;
	cout << "2. Menor preco" << endl;
	cout << "3. Menor duracao" << endl;
	cout << "4. Menor numero de transbordos" << endl;
	cin >> userChoice;
	while(userChoice > 4 || userChoice < 1){
		setcolor(12);
		cout << "Opcao invalida! Volte a escolher: ";
		setcolor(15);
		cin >> userChoice;
	}
	switch(userChoice){
	case 1:
		funcao = distCost;
		break;
	case 2:
		funcao = priceCost;
		break;
	case 3:
		funcao = durationCost;
		break;
	case 4:
		funcao = changeStationCost;
		break;
	}
	return;
}

void menuViajarEnd(){
	welcomeMenu();
	cout << "Ponto de Partida: ";
	inicio->imprime();
	cout << endl;
	unsigned int userChoice;
	cout << "Escolha o seu ponto de destino:" << endl;
	for(unsigned int i = 0; i < graph.getVerts().size() ; i++){
		cout << i + 1 << ". " << graph.getVerts()[i]->getID() << endl;
	}
	cin >> userChoice;
	while(userChoice > graph.getVerts().size() || userChoice <= 0 || inicio == graph.getVerts()[userChoice - 1]){
		setcolor(12);
		cout << "O ponto que escolheu nao existe ou e invalido." << endl;
		setcolor(15);
		cout << "Por favor volte a escolher:";
		cin >> userChoice;
	}
	fim = graph.getVerts()[userChoice - 1];
	return;
}

void menuViajarBegin(){
	welcomeMenu();
	unsigned int userChoice;
	cout << "Escolha o seu ponto de partida:" << endl;
	for(unsigned int i = 0; i < graph.getVerts().size() ; i++){
		cout << i + 1 << ". " << graph.getVerts()[i]->getID() << endl;
	}
	cin >> userChoice;
	while(userChoice > graph.getVerts().size() || userChoice <= 0){
		setcolor(12);
		cout << "O ponto que escolheu nao existe." << endl;
		setcolor(15);
		cout << "Por favor volte a escolher:";
		cin >> userChoice;
	}
	inicio = graph.getVerts()[userChoice - 1];
	return;
}


void welcomeMenu(){
	system("cls");
	setcolor(9);
	cout << " ___      _        ___  _                          " << endl;
	cout << "|_ _|_ _ <_> ___  | . \\| | ___ ._ _ ._ _  ___  _ _ " << endl;
	cout << " | || '_>| || . \\ |  _/| |<_> || ' || ' |/ ._>| '_>" << endl;
	cout << " |_||_|  |_||  _/ |_|  |_|<___||_|_||_|_|\\___.|_|  " << endl;
	cout << "            |_|                                    " << endl << endl;
	setcolor(15);
}
//!Menu

int main(){

	graph = loadTxt();
	menuSelection();

	return 0;
}
