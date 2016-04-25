/*
 * Transport.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

//TWEAKS
#define TRAIN_COST 0.02
#define BUS_COST 0.03
#define SUBWAY_COST 0.01
#define WALKING_COST 0


#define TRAIN_VELO 3
#define BUS_VELO 1
#define SUBWAY_VELO 2
#define WALKING_VELO 0.5

class Transport {



public:

	typedef enum {
		NONE,
		TRAIN,
		BUS,
		SUBWAY,
		WALKING
	}Type;

	/**
	 \param type tipo de transporte
	 \return devolve o preço por metro do transporte passado como argumento
	 */
	static double PricePerMeter(Type type);
	/**
	\param type tipo de transporte
	\return devolve a velocidade por metro do transporte passado como argumento
	*/
	static double VelocityPerMeter(Type type);
	/**
	 * construtor default
	 */
	Transport();
	/**
	 * destrutor
	 */
	virtual ~Transport();



};

#endif /* TRANSPORT_H_ */
