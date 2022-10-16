/*
 * StateActionTable.h
 *
 *  Created on: Apr 25, 2022
 *      Author: Wm. T. Thompson
 */

#ifndef STATEACTIONTABLE_H_
#define STATEACTIONTABLE_H_


#include "Common.h"

class StateActionTable {
public:
	StateActionTable();
	float get_action_value(const Scan_State &s1, const Action &a1);
	void set_action_value(const Scan_State &s1, const Action &a1, float value);
	void get_best_action(const Scan_State &s1, Action &a1);
	void report_action_values();
	virtual ~StateActionTable();
private:
	void setup_indices();
	unsigned int get_action_index(const Action &a1);
	void get_action_from_index(const unsigned int index, Action &a1);
	unsigned int get_state_index(const Scan_State &s1);
	void get_state_from_index(const unsigned int index, Scan_State &s1);
	unsigned int m_action_index[3][3][3];
	Action m_actions[27];
	Scan_State m_states[27];
	float m_action_values[27][27] = {0};
	unsigned int m_state_index[3][3][3];
};

#endif /* STATEACTIONTABLE_H_ */
