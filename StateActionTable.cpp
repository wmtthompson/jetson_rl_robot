/*
 * StateActionTable.cpp
 *
 *  Created on: Apr 25, 2022
 *      Author: william
 */

#include "StateActionTable.h"
#include <iostream>
using namespace std;

StateActionTable::StateActionTable() {
	setup_indices();

}

void StateActionTable::setup_indices()
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

	m_state_index[0][0][0] = 0;
	m_state_index[0][0][2] = 1;
	m_state_index[0][0][1] = 2;
	m_state_index[0][2][0] = 3;
	m_state_index[0][2][2] = 4;
	m_state_index[0][2][1] = 5;
	m_state_index[0][1][0] = 6;
	m_state_index[0][1][2] = 7;
	m_state_index[0][1][1] = 8;
	m_state_index[2][0][0] = 9;
	m_state_index[2][0][2] = 10;
	m_state_index[2][0][1] = 11;
	m_state_index[2][2][0] = 12;
	m_state_index[2][2][2] = 13;
	m_state_index[2][2][1] = 14;
	m_state_index[2][1][0] = 15;
	m_state_index[2][1][2] = 16;
	m_state_index[2][1][1] = 17;
	m_state_index[1][0][0] = 18;
	m_state_index[1][0][2] = 19;
	m_state_index[1][0][1] = 20;
	m_state_index[1][2][0] = 21;
	m_state_index[1][2][2] = 22;
	m_state_index[1][2][1] = 23;
	m_state_index[1][1][0] = 24;
	m_state_index[1][1][2] = 25;
	m_state_index[1][1][1] = 26;
}

float StateActionTable::get_action_value(const Scan_State &s1, const Action &a1)
{
	unsigned int state_index = get_state_index(s1);
	unsigned int action_index = get_action_index(a1);

	return m_action_values[state_index][action_index];
}

void StateActionTable::set_action_value(const Scan_State &s1, const Action &a1, float value)
{
	unsigned int state_index = get_state_index(s1);
	unsigned int action_index = get_action_index(a1);

	m_action_values[state_index][action_index] = value;
}

void StateActionTable::get_best_action(const Scan_State &s1, Action &a1)
{
	float max_val = 0;
	float next_val = 0;
	unsigned int state_index = 0;
	for (int i = 0; i < 19; i++)
	{
		state_index = get_state_index(s1);
		next_val = m_action_values[state_index][i];
		if (next_val > max_val)
		{
			max_val = next_val;
			a1 = m_actions[i];
		}
	}
}

unsigned int StateActionTable::get_action_index(const Action &a1)
{
	return m_action_index[a1.steer][a1.direction][a1.speed];
}

void StateActionTable::get_action_from_index(const unsigned int index, Action &a1)
{
	a1 = m_actions[index];
}

unsigned int StateActionTable::get_state_index(const Scan_State &s1)
{
	unsigned int left = static_cast<unsigned int>(s1.left);
	unsigned int right = static_cast<unsigned int>(s1.right);
	unsigned int center = static_cast<unsigned int>(s1.center);


	return m_state_index[left][right][center];
}

void StateActionTable::get_state_from_index(const unsigned int index, Scan_State &s1)
{
	s1 = m_states[index];
}

void StateActionTable::report_action_values()
{
	cout << "State Values :";
	for (int ii = 0; ii < 27 ; ii++)
	{
		for(int jj = 0; jj < 27; jj++)
		{
			cout << m_action_values[jj][ii];
			cout << " , ";
		}
		cout << endl;

	}
	cout << endl;
}

StateActionTable::~StateActionTable() {
	// TODO Auto-generated destructor stub
}

