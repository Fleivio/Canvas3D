#include "EngineGroup.h"

double EngineGroup::angle = 1;
Engine EngineGroup::e1 = Engine({}, true, 40, 150);
Engine EngineGroup::e2 = Engine({}, false, 40, 150);
Engine3D EngineGroup::engine3d1 = Engine3D();
Engine3D EngineGroup::engine3d2 = Engine3D();

