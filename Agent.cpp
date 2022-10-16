/*
 * Agent.cpp
 *
 *  Created on: Apr 20, 2022
 *      Author: william
 */

#include "Agent.h"

Agent::Agent(double greedyness) {

	m_greedyness = greedyness;
	setup_indices();
}


void Agent::policy_lookup(const Scan_State &s1, Action &a1)
{
	//Refer to MultiArmedBandit from Jupyter Notebook
	std::binomial_distribution<int> distribution(1, (1.0 - m_greedyness));
	std::uniform_int_distribution<unsigned int> random_index(0, 26);
	int be_greedy = distribution(m_generator);
	unsigned int idx;
	switch (m_chosen_state)
	{
	case RANDOM:
		//chose a random integer between 0 and 26
		idx = random_index(m_generator);
		if (be_greedy == 0)
		{
			m_chosen_state = RANDOM;
		}
		else
		{
			m_chosen_state = BEST;
		}
		break;
	case BEST:
		idx = m_action_index[s1.left][s1.right][s1.center];
		break;
	default:
		break;
	}

	a1 = m_actions[idx];
}

void Agent::policy_update(const Scan_State &s1, const Action &a1)
{
	unsigned int idx = m_action_index[s1.left][s1.right][s1.center];
	m_actions[idx] = a1;
}

void Agent::setup_indices()
{
	m_action_index[0][0][0] = 0;
	m_action_index[0][0][2] = 1;
	m_action_index[0][0][1] = 2;
	m_action_index[0][2][0] = 3;
	m_action_index[0][2][2] = 4;
	m_action_index[0][2][1] = 5;
	m_action_index[0][1][0] = 6;
	m_action_index[0][1][2] = 7;
	m_action_index[0][1][1] = 8;
	m_action_index[2][0][0] = 9;
	m_action_index[2][0][2] = 10;
	m_action_index[2][0][1] = 11;
	m_action_index[2][2][0] = 12;
	m_action_index[2][2][2] = 13;
	m_action_index[2][2][1] = 14;
	m_action_index[2][1][0] = 15;
	m_action_index[2][1][2] = 16;
	m_action_index[2][1][1] = 17;
	m_action_index[1][0][0] = 18;
	m_action_index[1][0][2] = 19;
	m_action_index[1][0][1] = 20;
	m_action_index[1][2][0] = 21;
	m_action_index[1][2][2] = 22;
	m_action_index[1][2][1] = 23;
	m_action_index[1][1][0] = 24;
	m_action_index[1][1][2] = 25;
	m_action_index[1][1][1] = 26;

	m_actions[0] = {S,FWD,FAST};
	m_actions[1] = {R,REV,FAST};
	m_actions[2] = {L,FWD,SLOW};
	m_actions[3] = {S,REV,FAST};
	m_actions[4] = {R,REV,SLOW};
	m_actions[5] = {L,REV,SLOW};
	m_actions[6] = {R,REV,FAST};
	m_actions[7] = {R,REV,FAST};
	m_actions[8] = {S,REV,SLOW};
	m_actions[9] = {L,REV,SLOW};
	m_actions[10] = {L,FWD,SLOW};
	m_actions[11] = {L,REV,FAST};
	m_actions[12] = {R,REV,FAST};
	m_actions[13] = {S,REV,FAST};
	m_actions[14] = {L,REV,SLOW};
	m_actions[15] = {S,REV,FAST};
	m_actions[16] = {L,REV,FAST};
	m_actions[17] = {L,REV,SLOW};
	m_actions[18] = {L,FWD,SLOW};
	m_actions[19] = {L,REV,SLOW};
	m_actions[20] = {L,FWD,FAST};
	m_actions[21] = {S,REV,SLOW};
	m_actions[22] = {L,REV,FAST};
	m_actions[23] = {L,REV,FAST};
	m_actions[24] = {R,REV,FAST};
	m_actions[25] = {R,REV,FAST};
	m_actions[26] = {S,FWD,FAST};
}
