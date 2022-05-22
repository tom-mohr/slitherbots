#include "logic.h"
#include <math.h>

using namespace std;

Snake::Snake() {
    radius = 10;
}

double mod(double a, double b) {
    int i = fmod(a, b);
    if (i<a) i += b;
    return i;
}

void World::step() {
    for (auto& snake : snakes) {
        for (auto& other : snakes) {
            double angleDiff = other.angle - snake.angle;
            angleDiff = fmod
        }
    }
}