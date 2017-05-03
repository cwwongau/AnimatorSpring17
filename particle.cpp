#include "particle.h"
// SAMPLE_SOLUTION

particle::particle(Vec3f pos, Vec3f vel, float life) : position(pos), velocity(vel), timeAlive(0), lifeSpan(life)
{
}
