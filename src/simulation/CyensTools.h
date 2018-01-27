#include "Particle.h"
#include "Simulation.h"
#include "../../generated/ElementClasses.h"

int makeAlk(int c);
int getBondLoc(int c);
bool isAlkane(int c, int h);
bool isAlkene(int c, int h);
bool isAlkyne(int c, int h);

void ClampOrganic(Particle* p);