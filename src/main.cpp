#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

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


typedef struct WayInfo{
	Way w;
	bool bothWays;
}WayInfo;


void welcomeMenu();
void menuConetividade();
void menuDFS();
void menuViajarBegin();
void menuViajarEnd();
void menuViajarModo();
void menuDisplayViagem();
void menuSelection();

void MiniSlave(Node n1, Node n2,Way w, Graph<Node,Way>& g){
	w.setDistance(n1.calcDist(n2));
	g.addEdge(n1,n2,w);
	g.addEdge(n2,n1,w);
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

void repaint(){
	for (unsigned int i = 0; i < graph.getVerts().size(); ++i) {
		for (unsigned int j = 0; j < graph.getVerts()[i]->getEdges().size(); ++j) {
			Transport::Type t= graph.getVerts()[i]->getEdges()[j].getWeights().getType();
			string color ="yellow";

			switch (t) {
			case Transport::TRAIN:
				color="red";
				break;
			case Transport::SUBWAY:
				color= "cyan";
				break;
			case Transport::BUS:
				color = "green";
				break;
			}

			gv->setEdgeColor(graph.getVerts()[i]->getEdges()[j].getWeights().getID(),color);graph.getVerts()[i]->getEdges()[j].getWeights().getName();
		}
	}
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

		switch (n[0]) {
		case 'T':
			t=Transport::TRAIN;
			break;
		case 'S':
			t=Transport::SUBWAY;
			break;
		case 'B':
			t=Transport::BUS;
			break;
		default:
			t=Transport::WALKING;
			break;
		}

		stringstream(res[0]) >> id;

		if(res[2] == "False")
			isTwoWay=false;



		Way w(id, n, t);//calcular distancia...

		WayInfo wI;
		wI.bothWays=isTwoWay;
		wI.w = w;

		ways[id] = wI;

	}
	file.close();

	file.open("connection_info.txt");
	while(getline(file,line)){
		stringstream ss(line);
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
		}

		gv->addEdge(w.getID(),node1,node2,!wI.bothWays);
		gv->setEdgeThickness(w.getID(),25);

		stringstream s;
		s << w.getID() << "|" << w.getName() <<" | " << w.getDistance() << " m |" << w.getPrice() << " €|" << w.getTime() << " s" ;
		gv->setEdgeLabel(w.getID(),s.str());
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
	setcolor(11);
	cout << "Escolha uma opcao selecionando o numero que a antecede." << endl;
	setcolor(15);
	if(!graph.isConex()){
		setcolor(12);
		cout << "ATENCAO! A rede nao se encontra 100% conectada!" << endl;
		setcolor(15);
	}
	cout << "1. Viajar;" << endl;
	cout << "2. Avaliar Conectividade;" << endl;
	cout << "3. Pesquisa em profundidade;" << endl;
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
		menuDFS();
		break;
	case '4':
		return;//SAIR DA APLICACAO
		break;
	}
	repaint();
	gv->rearrange();
	menuSelection();
}

void menuDFS(){
	welcomeMenu();
	setcolor(11);
	cout << "-> A realizar Pesquisa em profundidade (DFS) <-" << endl;
	setcolor(15);
	vector<Vertex<Node,Way>*> vec = graph.dfs();
	for(unsigned int i = 0; i < vec.size(); i++){
		vec[i]->imprime();
		cout << endl;
	}
	setcolor(11);
	cout << "-> Pesquisa em profundidade concluida! <-" << endl;
	setcolor(12);
	cout << "Prima qualquer tecla para voltar ao inicio.";
	setcolor(15);
	getch();
	return;
}

void menuConetividade(){
	welcomeMenu();
	cout << "-> Conetividade da rede de transportes <-" << endl << endl;
	if(graph.isConex()){
		setcolor(10);
		cout << "A rede de transportesnao encontra-se 100% conectada!" << endl;
		setcolor(15);
	}else{
		setcolor(12);
		cout << "A rede de transportes nao se encontra 100% conectada!" << endl;
		setcolor(15);
	}
	setcolor(11);
	cout << "Lista de pontos de articulacao: " << endl;

	setcolor(12);
	vector<Vertex<Node,Way> *> vec = graph.findArt();
	for(unsigned int i = 0; i < vec.size(); i++){
		vec[i]->imprime();
		cout << endl;
	}
	setcolor(15);

	if(vec.size()==0){
		cout << "Como esta rede de transportes não possui pontos de articulação podemos" << endl;
		cout << "considera-la biconexa." << endl;
	}else{
		cout << "Estes sao pontos criticos da rede que, na eventualidade de um" << endl;
		cout <<	"corte tornara algumas partes da rede de transportes inacessiveis." << endl;
	}
	setcolor(12);
	cout << "Prima qualquer tecla para voltar ao inicio.";
	setcolor(15);
	getch();
	return;
}

void menuDisplayViagem(){
	welcomeMenu();
	list<Vertex<Node,Way>*> path = graph.findWay(inicio,fim,funcao);
	setcolor(3);
	cout << "Ponto de Partida: ";
	setcolor(15);
	inicio->imprime();
	cout << endl;
	setcolor(3);
	cout << "Ponto de Chegada: ";
	setcolor(15);
	fim->imprime();
	setcolor(3);
	cout << endl << "Caminho: ";
	setcolor(15);

	list<Vertex<Node,Way>*>::const_iterator it = path.begin();
	Vertex<Node,Way>* temp = NULL;

	double preco = 0;
	double tempo = 0;
	unsigned int distancia = 0;
	unsigned int numeroTransbordos =0;
	Transport::Type ultimoTipo = Transport::NONE;
	for(it = path.begin(); it != path.end(); it++){

		if(temp != NULL){
			for(unsigned int i = 0; i < temp->getEdges().size() ; i ++){
				if(temp->getEdges()[i].getDest() == (*it)){

					gv->setEdgeColor(temp->getEdges()[i].getWeights().getID(), "white");
					distancia += temp->getEdges()[i].getWeights().getDistance();
					preco += temp->getEdges()[i].getWeights().getPrice();
					tempo += temp->getEdges()[i].getWeights().getTime();

					Transport::Type tipoAtual = temp->getEdges()[i].getWeights().getType();

					if(ultimoTipo != Transport::NONE && ultimoTipo != Transport::WALKING && tipoAtual != Transport::WALKING)
						if(ultimoTipo != tipoAtual)
							numeroTransbordos++;

					if(tipoAtual!= Transport::WALKING)
						ultimoTipo = tipoAtual;

					break;
				}
			}
		}
		temp = *it;

		(*it)->imprime();
	}
	gv->rearrange();

	setcolor(3);
	cout << "\nDistancia total: ";
	setcolor(15);
	cout << distancia << " m\n";
	setcolor(3);
	cout << "Custo: " ;
	setcolor(15);
	cout << preco << " " << char(36) << endl;
	setcolor(3);
	cout << "Duracao: ";
	setcolor(15);
	cout<< tempo << " s\n";
	setcolor(3);
	cout << "Transbordos: ";
	setcolor(15);
	cout << numeroTransbordos << "\n";
	cout << endl << endl;
	setcolor(11);
	cout << "Prima qualquer tecla para voltar ao inicio.";
	setcolor(15);
	getch();
	return;
}

void menuViajarModo(){
	welcomeMenu();
	setcolor(3);
	cout << "Ponto de Partida: ";
	setcolor(15);
	inicio->imprime();
	cout << endl;
	setcolor(3);
	cout << "Ponto de Chegada: ";
	setcolor(15);
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
	setcolor(3);
	cout << "Ponto de Partida: ";
	setcolor(15);
	inicio->imprime();
	cout << endl;
	unsigned int userChoice;
	vector<Vertex<Node,Way>*> destinos = graph.bfs(inicio);
	setcolor(11);
	cout << "Escolha o seu ponto de destino:" << endl;
	setcolor(15);
	for(unsigned int i = 0; i < destinos.size() ; i++){
		cout << i + 1 << ". " << destinos[i]->getID() << endl;
	}
	cin >> userChoice;
	while(userChoice > destinos.size() || userChoice <= 0 || inicio == destinos[userChoice - 1]){
		setcolor(12);
		cout << "O ponto que escolheu nao existe ou e invalido." << endl;
		setcolor(15);
		cout << "Por favor volte a escolher:";
		cin >> userChoice;
	}
	fim = destinos[userChoice - 1];
	return;
}

void menuViajarBegin(){
	welcomeMenu();
	unsigned int userChoice;
	setcolor(11);
	cout << "Escolha o seu ponto de partida:" << endl;
	setcolor(15);
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
	cout << " ___      _        ___  _                          	";
	setcolor(9,15);
	cout <<"Legenda GraphViewer:" << endl;
	setcolor(9,0);
	cout << "|_ _|_ _ <_> ___  | . \\| | ___ ._ _ ._ _  ___  _ _ ";
	setcolor(12);
	cout << "		Train"<< endl;
	setcolor(9);
	cout << " | || '_>| || . \\ |  _/| |<_> || ' || ' |/ ._>| '_>";
	setcolor(11);
	cout << "		Subway"<< endl;
	setcolor(9);
	cout << " |_||_|  |_||  _/ |_|  |_|<___||_|_||_|_|\\___.|_|  ";
	setcolor(10);
	cout << "		Bus" << endl;
	setcolor(9);
	cout << "            |_|                                    ";
	setcolor(14);
	cout << "		Walking" << endl;
	cout << "                                                    ";
	setcolor(15);
	cout << "		Shortest Path" << endl;
	cout << "          	                                         ";
	setcolor(9,15);
	cout <<"Etiqueta da aresta:" << endl;
	setcolor(15,0);
	cout << "                                                    ";
	cout << "Id|Tipo Transporte|Distancia|Preco|Duracao" << endl << endl;
}
//!Menu

int main(){

	graph = loadTxt();
	repaint();
	menuSelection();

	return 0;
}
