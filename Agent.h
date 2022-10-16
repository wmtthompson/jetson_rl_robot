/*
 * Agent.h
 *
 *  Created on: Apr 20, 2022
 *      Author: william
 */



#ifndef AGENT_H_
#define AGENT_H_

#include "common.h"
#include <random>

enum CHOOSE_STATE {RANDOM, BEST};

class Agent {
public:
	Agent(double greedyness);
	void policy_lookup(const Scan_State &s1, Action &a1);
	void policy_update(const Scan_State &s1, const Action &a1);


private:
	void setup_indices();
	Action m_actions[27];
	unsigned int m_action_index[3][3][3] = {0};
	CHOOSE_STATE m_chosen_state = BEST;
	std::default_random_engine m_generator;
	double m_greedyness = 0.6;
};

#endif /* AGENT_H_ */
