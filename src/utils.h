#ifndef UTILS_H
#define UTILS_H


#include "VertexAndEdge.h"
#include "Node.h"
#include "Way.h"
#include <Windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

/**
 * Funcao que calcula o custo relativo da distancia
 */
int distCost(Edge<Node,Way> *e,Vertex<Node,Way> *v);

/**
 * Funcao que calcula o custo relativo do preço
 */
int priceCost(Edge<Node,Way> *e,Vertex<Node,Way> *v);

/**
 * Funcao que calcula o custo relativo da duracao
 */
int durationCost(Edge<Node,Way> *e,Vertex<Node,Way> *v);

/**
 * Funcao que calcula o custo relativo da mudança de transporte
 */
int changeStationCost(Edge<Node,Way> *e,Vertex<Node,Way> *v);

template<class A,class B>
struct VertexHandler{
	Vertex<A,B> *v;
};

template<class A,class B>
inline bool operator<(VertexHandler<A,B>& v1,VertexHandler<A,B>& v2){
		return v1.v->getCost() < v2.v->getCost();
}

template<class A,class B>
inline bool operator==(const VertexHandler<A,B>& v1,const VertexHandler<A,B>& v2){
		return (v1.v == v2.v);
}

/**
 * Funcao para alterar a cor da letra na consola
 */
void setcolor(unsigned int color);

void setcolor(unsigned int color, unsigned int background_color);


#endif
