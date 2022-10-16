/*
 * Episode.h
 *
 *  Created on: Apr 20, 2022
 *      Author: Wm. T. Thompson
 */

#ifndef EPISODE_H_
#define EPISODE_H_


#include "Common.h"
class StateActionTable;

class Agent;


class Episode {
public:
	Episode(Agent *agent_in);
	virtual ~Episode();
	float value_lookup(Scan_State &s1);
	void update_value(Scan_State &s1, float value);
	float reward_of_total_scan(Scan_State &s1);
	void evaluate_episode(unsigned int episode_number);
	void report_state_values();
	Scan_State state_array[EPISODE_LEN];
	Action action_array[EPISODE_LEN];
	float rewards[EPISODE_LEN];
private:
	void setup_indices();
	float reward_calc(Scan scn1);
	bool check_same_state(Scan_State &ss1, Scan_State &ss2);
	bool check_same_action(Action &a1, Action &a2);
	float m_G = 0;
	const float m_gamma = 0.5;
	bool m_state_action_found = false;
	float m_state_values[27] = {0.0};
	unsigned int m_value_index[3][3][3] = {0};
	StateActionTable *m_state_action_table;
	Agent *m_agent;
};

#endif /* EPISODE_H_ */
