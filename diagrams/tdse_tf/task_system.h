/*
 * task_system.h
 *
 *  Created on: 11 jun 2026
 *      Author: lauta
 */

#ifndef TASK_SYSTEM_H_
#define TASK_SYSTEM_H_

typedef enum task_system_mode {MANUAL, AUTO} task_system_mode_t;

typedef struct stream_bluetooth {
	char command[];
	char value[];
} stream_bluetooth_t;

#endif /* TASK_SYSTEM_H_ */
