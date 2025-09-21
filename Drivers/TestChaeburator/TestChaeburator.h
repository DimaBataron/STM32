/*
 * TestChaeburator.h
 *
 *  Created on: Sep 19, 2025
 *      Author: dima
 */

#ifndef TESTCHAEBURATOR_TESTCHAEBURATOR_H_
#define TESTCHAEBURATOR_TESTCHAEBURATOR_H_

//#include "main.h"
#include "BrushedDC.h"
#include "Chaeburator.h"

void TestFunction();

void TestMotor(DC_Motor *Motor, int8_t acceleration);

void Test2Motor(DC_Motor *Motor1, DC_Motor *Motor2, int8_t acceleration);

#endif /* TESTCHAEBURATOR_TESTCHAEBURATOR_H_ */
