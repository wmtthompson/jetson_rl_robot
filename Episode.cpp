/*
 * Episode.cpp
 *
 *  Created on: Apr 20, 2022
 *      Author: william
 */

#include "Episode.h"
#include "StateActionTable.h"
#include "Agent.h"
#include <iostream>

using namespace std;

Episode::Episode(Agent *agent_in) {
	setup_indices();
	m_state_action_table = new StateActionTable();
	m_agent = agent_in;
}

void Episode::setup_indices()
{
	m_value_index[0][0][0] = 0;
	m_value_index[0][0][2] = 1;
	m_value_index[0][0][1] = 2;
	m_value_index[0][2][0] = 3;
	m_value_index[0][2][2] = 4;
	m_value_index[0][2][1] = 5;
	m_value_index[0][1][0] = 6;
	m_value_index[0][1][2] = 7;
	m_value_index[0][1][1] = 8;
	m_value_index[2][0][0] = 9;
	m_value_index[2][0][2] = 10;
	m_value_index[2][0][1] = 11;
	m_value_index[2][2][0] = 12;
	m_value_index[2][2][2] = 13;
	m_value_index[2][2][1] = 14;
	m_value_index[2][1][0] = 15;
	m_value_index[2][1][2] = 16;
	m_value_index[2][1][1] = 17;
	m_value_index[1][0][0] = 18;
	m_value_index[1][0][2] = 19;
	m_value_index[1][0][1] = 20;
	m_value_index[1][2][0] = 21;
	m_value_index[1][2][2] = 22;
	m_value_index[1][2][1] = 23;
	m_value_index[1][1][0] = 24;
	m_value_index[1][1][2] = 25;
	m_value_index[1][1][1] = 26;
}

float Episode::value_lookup(Scan_State &s1)
{
	unsigned int idx = m_value_index[s1.left][s1.right][s1.center];
	return m_state_values[idx];
}

void Episode::update_value(Scan_State &s1, float value)
{
	unsigned int idx = m_value_index[s1.left][s1.right][s1.center];
	m_state_values[idx] = value;
}

Episode::~Episode() {
	delete m_state_action_table;
}

bool Episode::check_same_state(Scan_State &ss1, Scan_State &ss2)
{
	if ((ss1.center == ss2.center) && (ss1.left == ss2.left) && (ss1.right == ss2.right))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Episode::check_same_action(Action &a1, Action &a2)
{
	if ((a1.direction == a2.direction) && (a1.speed == a2.speed) && (a2.steer == a2.steer))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Episode::reward_calc(Scan scn1)
{
	switch (scn1)
	{
	case NEAR:
		return 0.9;
		break;
	case VERY_CLOSE:
		return -0.2;
		break;
	case FAR:
		return 0.1;
		break;
	default:
		return 0.0;
		break;
	}
}

float Episode::reward_of_total_scan(Scan_State &s1)
{
	float rew = reward_calc(s1.left) + reward_calc(s1.right) + reward_calc(s1.center);
	return rew;
}

void Episode::evaluate_episode(unsigned int episode_number)
{
	float newval;
	float val;
	Action best_action;
	best_action.direction = FWD;
	best_action.speed = SLOW;
	best_action.steer = S;
	for(int t = EPISODE_LEN-1; t>=0; t--)
	{
		m_G = m_gamma*m_G+rewards[t];
		// ######################## Search for earlier instance of the current state
		for(int j = 0; j<t ; j++)
		{
			if ((check_same_state(state_array[j], state_array[t]) == true) &&
					(check_same_action(action_array[j], action_array[t]) == true))
			{
				m_state_action_found = true;
				break;
			}

		}
		// #########################
		if (m_state_action_found == false)
		{
			//store the state, lookup in value table
			val = m_state_action_table->get_action_value(state_array[t], action_array[t]);
			newval = val + (1.0/episode_number)*(m_G-val);

			m_state_action_table->set_action_value(state_array[t], action_array[t], newval);
			// get best action
			m_state_action_table->get_best_action(state_array[t], best_action);
			m_agent->policy_update(state_array[t], best_action);
		}
		m_state_action_found = false;
	}
}

void Episode::report_state_values()
{
	m_state_action_table->report_action_values();
}
