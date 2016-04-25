
#ifndef NODE_H_
#define NODE_H_

#define Earth_Ratius 6371000

#include <iostream>
#include <cmath>

/**
 * Classe Node responsavel pelos vértices do grafo
 */
class Node {

	int id;
	double lat;
	double longe;

public:
	Node(){}
	Node(int id, double latitude, double longitude);

	/**
	 * Funcao que calcula a distancia entre dois nodes
	 *
	 * @param n node para o qual se calcula a distancia
	 * @return a distancia entre este node e o node n
	 */
	double calcDist(Node n);
	/**
	 * Funcao get para o Id do node
	 * @return o id do node
	 */
	int getID() const;

	/**
	 * Funcao get para a latitude do node
	 * @return a latitude do node
	 */
	double getLatitude() const;
	/**
	 * Funcao get para a longitude do node
	 * @return a longitude do node
	 */
	double getLongitude() const;
};

bool operator==(const Node& n1, const Node& n2);

std::ostream & operator<<(std::ostream &o , const Node& n1);

#endif /* INTERSECAO_H_ */
