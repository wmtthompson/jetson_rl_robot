/*
 * Simulator.h
 *
 *  Created on: Apr 21, 2022
 *      Author: Wm. T. Thompson
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "Common.h"
#include "Agent.h"
#include "Episode.h"

class Simulator {
public:
	Simulator(Agent *agent, Episode *episode);
	void generate_episode();
	virtual ~Simulator();
private:
	void get_next_state(Scan_State &ss1);
	Episode *m_episode;
	Agent *m_agent;

};

#endif /* SIMULATOR_H_ */
