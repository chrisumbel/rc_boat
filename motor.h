/* 
 * File:   motor.h
 * Author: cumbel
 *
 * Created on March 14, 2017, 11:21 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#define MOTOR_DIRECTION_STOP    0
#define MOTOR_DIRECTION_FORWARD 1
#define MOTOR_DIRECTION_LEFT    2
#define MOTOR_DIRECTION_RIGHT   4

#ifdef	__cplusplus
extern "C" {
#endif

int motor_init();
int motor_set_direction(int direction);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

