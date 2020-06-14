/* 
 * circularQueue.h - The C head file of 环形队列
 * NOTE: This file is based on C++11
 *
 * Copyright (c) 2020-, FOSH Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-06-14     StudyHooligen     first version   2373180028@qq.com
 */
#ifndef circularQueue_H

#define circularQueue_H

#define uint16_t int
#define uint32_t int

typedef struct circularQueue
{
	uint16_t readIndex;
	uint16_t writeIndex;
	uint16_t bufferSize;
	char* buffer;
}circularQueue;

void circularQueueInit(circularQueue* cq, char* bufferPtr, uint16_t bufferSize);

void circularQueueAdd(circularQueue* cq, char* stringPtr, uint16_t stringSize);



#endif // !circularQueue_H
