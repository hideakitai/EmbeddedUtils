#pragma once
#ifndef EMBEDDEDUTILS_H
#define EMBEDDEDUTILS_H

#ifdef abs
#define abs_tmp abs
#undef abs
#endif
#ifdef round
#define round_tmp round
#undef round
#endif
#ifdef B1
#define B1_tmp B1
#undef B1
#endif

#ifndef __AVR__
#include "lib/Helper.h"
#include "lib/Debug.h"
#include "lib/Calculus.h"
#include "lib/Convert.h"
#include "lib/Filters.h"
#include "lib/MatrixFunc.h"
#include "lib/RingQueue.h"
#include "lib/Vec.h"
#include "lib/Gamma.h"
#else
#include <Arduino.h>
#include "lib/avr/Debug.h"
#include "lib/avr/Calculus.h"
#include "lib/avr/Convert.h"
#include "lib/avr/Filters.h"
#include "lib/MatrixFunc.h"
#include "lib/avr/RingQueue.h"
#include "lib/Vec.h"
#include "lib/avr/Gamma.h"
#endif

#ifdef abs_tmp
#define abs abs_tmp
#endif
#ifdef round_tmp
#define round round_tmp
#endif
#ifdef B1_tmp
#define B1 B1_tmp
#endif

#endif // EMBEDDEDUTILS_H
