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

#include "lib/Helper.h"
#include "lib/Debug.h"
#include "lib/Calculus.h"
#include "lib/Convert.h"
#include "lib/Filters.h"
#include "lib/MatrixFunc.h"
#include "lib/RingQueue.h"
#include "lib/Vec.h"
#include "lib/Gamma.h"
