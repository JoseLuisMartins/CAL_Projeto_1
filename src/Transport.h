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
#define WALKING_COST 0


#define TRAIN_VELO 12
#define BUS_VELO 12
#define SUBWAY_VELO 12
#define WALKING_VELO 3

class Transport {



public:

	typedef enum {
		NONE,
		TRAIN,
		BUS,
		SUBWAY,
		WALKING
	}Type;

	static double PricePerMeter(Type type);
	static double VelocityPerMeter(Type type);
	Transport();
	virtual ~Transport();



};

#endif /* TRANSPORT_H_ */
