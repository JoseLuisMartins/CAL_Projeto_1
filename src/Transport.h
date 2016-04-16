/*
 * Transport.h
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

//TWEAKS
#define TRAIN_COST 0.5
#define BUS_COST 0.5
#define SUBWAY_COST 0.5

#define TRAIN_VELO 12
#define BUS_VELO 12
#define SUBWAY_VELO 12


class Transport {



public:

	typedef enum {
		NONE,
		TRAIN,
		BUS,
		SUBWAY
	}Type;

	static double PricePerMeter(Type type);
	static double VelocityPerMeter(Type type);
	Transport();
	virtual ~Transport();



};

#endif /* TRANSPORT_H_ */
