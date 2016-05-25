/*
 * Way.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef WAY_H_
#define WAY_H_

#include<string>
#include "Transport.h"


using namespace std;

/**
 * Classe Way que gere as informações das arestas
 */
class Way {

	unsigned int id;
	string name;
	double distance;
	Transport::Type type;
	string linha;


public:
	Way(){}
	Way(int id, string name, Transport::Type type, string linha);
	virtual ~Way();

	/**
	 * Funcao get para o Id de Way
	 * @return o Id de Way
	 */
	unsigned int getID() const;
	/**
	 * Funcao get para o nome do Way
	 * @return nome do Way
	 */
	string getName() const;
	/**
	 * Funcao get para o preço por metro mediante o tipo de transporte
	 * @return o preço do metro
	 */
	double getPricePerMeter() const;
	/**
	 * Funcao get para a distancia do Way
	 * @return a distancia do Way
	 */
	double getDistance() const;
	/**
	 * Funcao set para a distancia do Way
	 * @param dist a nova distancia do Way
	 */
	void setDistance(double dist);
	/**
	 * Funcao get para o tempo mediante o tipo de transporte
	 * @return o tempo de transição do Way
	 */
	double getTime() const;
	/**
	 * Funcao get para o preço
	 * @return o custo do Way
	 */
	double getPrice() const;
	/**
	 * Funcao get para o tipo de transporte do Way
	 * @return o tipo de transporte
	 */
	Transport::Type getType() const;

	/**
	 * Funcao get para o nome da linha
	 * @return o nome da linha
	 */
	string getLinha() const;

	/*
	 * Funcao set para o nome da linha
	 * @param l novo nome da linha
	 */
	void setLinha(string l);
};

#endif /* WAY_H_ */
