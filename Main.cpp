#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "common.h"
#include "i2c.h"
#include "Episode.h"
#include "Agent.h"
//#include "Simulator.h"

using namespace std;

int bus;
//I2CDevice device;
char buffer[8] = {0};

Action ac1;
Scan_State ss1;
Agent agent1(0.5);
float rew; //reward
void print_action(Action a2);



int main(int argc, char **argv) {

	ac1.steer = R;
	ac1.direction = REV;
	ac1.speed = SLOW;

	Episode ep1(&agent1);
//	Simulator sim1(&a1, &ep1);


	cout << "Hello world" << endl;


	/* Open i2c bus /dev/i2c-0 */
	if ((bus = i2c_open("/dev/i2c-1")) == -1) {

		cout << "Could not open i2c bus" << endl;
	}
	else
	{
		cout << "I2C device opened successfully. " << endl;
	}

	if (ioctl(bus, I2C_SLAVE, 8) < 0)
	{
		cout << "Failed to acquire bus access and/or talk to slave." << endl;
		return -1;
	}



	ssize_t size = sizeof(Action);

//	sim1.generate_episode();


	for (int ep = 1; ep < 1; ep++)
	{
		for (int i = 0; i < EPISODE_LEN; i++)
		{
			size = sizeof(Scan_State);

			if(read(bus, buffer, size) != size)
			{
				cout << "Failed to read from the i2c bus." << endl;
			}

			memcpy((void *)&ss1, (void *)buffer, sizeof(Scan_State));
			//		cout << "Buffer contents = " << buffer << endl;

			cout << "Scan State, left = " << ss1.left << " right = " << ss1.right << " center = " << ss1.center << endl;

			//use scan state to chose the next action, and get a reward.
			agent1.policy_lookup(ss1,ac1);
			rew = ep1.reward_of_total_scan(ss1);
			ep1.rewards[i] = rew;
			ep1.state_array[i] = ss1;
			ep1.action_array[i] = ac1;

			sleep(0.01);

			cout << " " << endl;
			size = sizeof(Action);
			cout << "Sending action " << endl;
			print_action(ac1);

			memcpy((void *)buffer, (void *)&ac1, sizeof(Action));
			if (write(bus, buffer, size) != size)
			{
				cout << "Failed to write to the i2c bus." << endl;
			}


			sleep(2);
		}

		ep1.evaluate_episode(ep);
	}

	ep1.report_state_values();


	i2c_close(bus);

	return 0;
}

void print_action(Action a2)
{
	cout << "Action = ";
	switch (a2.direction)
	{
	case FWD:
		cout << " FORWARD ";
		break;
	case REV:
		cout << " REVERSE ";
		break;
	case STOP:
		cout << " STOP ";
		break;
	default:
		break;
	}

	switch (a2.speed)
	{
	case SLOW:
		cout << " SLOW ";
		break;
	case FAST:
		cout << " FAST ";
		break;
	default:
		break;
	}

	switch (a2.steer)
	{
	case L:
		cout << " LEFT ";
		break;
	case R:
		cout << " RIGHT ";
		break;
	case S:
		cout << " CENTER ";
		break;
	default:
		break;
	}

	cout << endl;
}
