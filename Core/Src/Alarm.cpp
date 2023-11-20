/*
 * Alarm.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#pragma once

#include <Alarm.h>

Alarm::Alarm(int min, int hour) : min(min), hour(hour), tracker(0, min, hour, 0, 0, 0) {
	// TODO Auto-generated constructor stub
}

Alarm::~Alarm() {
	// TODO Auto-generated destructor stub
}



bool Alarm::is_alarmed(Time *global){
	// is only active for 30s
	if(this->tracker.get_hrr() < global->get_hrr()) return false;
	if(this->tracker.get_min()< global->get_min()) return false;

	// is same minute - check if within 30 s range
	if(global->get_sec() > 15) return false;
	return true;
}


