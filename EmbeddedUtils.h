#pragma once

#include <Arduino.h>

#ifdef abs
#undef abs
#endif

#ifdef round
#undef round
#endif

#ifdef B1
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
#include "lib/avr/Debug.h"
#include "lib/avr/Calculus.h"
#include "lib/avr/Convert.h"
#include "lib/avr/Filters.h"
#include "lib/MatrixFunc.h"
#include "lib/avr/RingQueue.h"
#include "lib/Vec.h"
#include "lib/avr/Gamma.h"
#endif
