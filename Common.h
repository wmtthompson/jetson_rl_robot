/*
 * common.h
 *
 *  Created on: Apr 20, 2022
 *      Author: Wm. T. Thompson
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#define EPISODE_LEN 20

enum Steering: uint8_t {L = 0, S = 1, R = 2};
enum Speed: uint8_t {SLOW = 0, FAST = 1};
enum Direction: uint8_t {FWD = 0, REV =1, STOP = 2};
enum Scan: uint8_t {NEAR = 0, FAR = 1, VERY_CLOSE = 2};


struct Action
{
	Steering steer;
	Direction direction;
	Speed speed;
};

struct Scan_State
{
	Scan left;
	Scan right;
	Scan center;
};



#endif /* COMMON_H_ */
