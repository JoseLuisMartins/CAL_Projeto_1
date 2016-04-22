/*
 * Transport.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Joao
 */

#include "Transport.h"

Transport::Transport() {
	// TODO Auto-generated constructor stub

}

Transport::~Transport() {
	// TODO Auto-generated destructor stub
}

double Transport::VelocityPerMeter(Type type){

	switch(type){

	case BUS:
		return BUS_VELO;
		break;

	case TRAIN:
		return TRAIN_VELO;
		break;

	case SUBWAY:
		return SUBWAY_VELO;
		break;
	case WALKING:
		return WALKING_VELO;
		break;
	default:
		return 0;
	}
}

double Transport::PricePerMeter(Type type){

	switch(type){

	case BUS:
		return BUS_COST;
		break;

	case TRAIN:
		return TRAIN_COST;
		break;

	case SUBWAY:
		return SUBWAY_COST;
		break;
	case WALKING:
		return WALKING_COST;
		break;
	default:
		return 0;
	}


}
