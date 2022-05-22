#include "logic.h"
#include <math.h>
#include <pybind11/pybind11.h>

using namespace std;

Snake::Snake(string name,) {//todo: pass name and step method from user
    sight_radius;
}

Segment& Snake::get_head() {
    return segments[0];
}

void Snake::apply_api(Api api) {
    Segment& head = get_head();
    head.angle += clamp(api.angle, -0.5, 0.5);
}

double clamp(double value, double min, double max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

double mod(double a, double b) {
    int i = fmod(a, b);
    if (i<a) i += b;
    return i;
}

double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double distance(Segment& a, Segment& b) {
    return distance(a.x, a.y, b.x, b.y);
}

void World::step() {
    for (auto& snake : snakes) {
        Api api;

        Segment& head = snake.get_head();

        for (auto& other : snakes) {
            for (auto& seg : other.segments) {
                double dist = distance(head, seg);
                if (dist <= snake.sight_radius) {

                    SegmentInfo si;

                    si.r = dist;
                    si.dir = atan2(seg.y - head.y, seg.x - head.x);
                    si.angle = mod(seg.angle - head.angle + M_PI, M_2_PI) - M_PI;// angle in interval [-pi, +pi)

                    api.segments.push_back(si);
                }
            }
        }

        //todo: execute user code: snake.step(api);

        // apply api object
        snake.apply_api(api);
    }
}
