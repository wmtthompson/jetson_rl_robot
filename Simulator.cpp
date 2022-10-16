/*
 * Simulator.cpp
 *
 *  Created on: Apr 21, 2022
 *      Author: Wm. T. Thompson
 */

#include "Simulator.h"
#include <random>
#include <iostream>

using namespace std;

Simulator::Simulator(Agent *agent, Episode *episode) {
	m_agent = agent;
	m_episode = episode;

}

void Simulator::get_next_state(Scan_State &ss1)
{
	uint8_t left = static_cast<uint8_t>(random() % 3);
	uint8_t right = static_cast<uint8_t>(random() % 3);
	uint8_t center = static_cast<uint8_t>(random() % 3);

	ss1.left = static_cast<Scan>(left);
	ss1.right = static_cast<Scan>(right);
	ss1.center = static_cast<Scan>(center);
}

void Simulator::generate_episode()
{
	Scan_State s1 = {FAR, FAR, FAR};
	Action a1;
	a1.direction = FWD;
	a1.speed = FAST;
	a1.steer = S;
	float rew = 0;
	int idx = 0;

	for (int ii = 0; ii < EPISODE_LEN; ii++)
	{
		get_next_state(s1);
		//get next action from the policy
		m_agent->policy_lookup(s1, a1);
		//the state s1 is the result of previous action
		rew = m_episode->reward_of_total_scan(s1);
		m_episode->rewards[ii] = rew;
		m_episode->state_array[ii] = s1;
		m_episode->action_array[ii] = a1;
	}
}


Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}

