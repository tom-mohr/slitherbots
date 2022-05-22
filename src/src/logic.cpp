#include "logic.h"
#include <math.h>
#include <string>

using namespace std;

Snake::Snake(string _name, py::function _step_fn) {//todo: pass name and step method from user
    sight_radius = 30;
    name = _name;
    step_fn = _step_fn;

    //todo: add head to segments
    //todo: pick random head angle at start
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

// make angle to be in [-pi, pi)
double nice_angle(double angle) {
    return mod(angle + M_PI, M_2_PI) - M_PI;
}

void World::step() {

    // get api responses
    for (auto& snake : snakes) {
        Api api;

        Segment& head = snake.get_head();

        for (auto& other : snakes) {
            for (auto& seg : other.segments) {
                double dist = distance(head, seg);
                if (dist <= snake.sight_radius) {

                    SegmentInfo si;

                    si.r = dist;
                    si.dir = nice_angle(atan2(seg.y - head.y, seg.x - head.x) - head.angle);
                    si.angle = nice_angle(seg.angle - head.angle);
                    api.segments.push_back(si);
                }
            }
        }

        //todo: execute user code: snake.step(api);

        // apply api object
        snake.apply_api(api);
    }

    // GAME LOGIC

    // move each snake
    for (auto& snake : snakes) {
        Segment& head = snake.get_head();

        if (snake.segments.size() > 1) {

            // move each segment to location of the segment in front of it
            for (int i=snake.segments.size() - 1; i > 0; i--) {// start from last index (tail)
                snake.segments[i].x = snake.segments[i - 1].x;
                snake.segments[i].y = snake.segments[i - 1].y;
            }
        }

        // move head
        head.x += speed * cos(head.angle);
        head.y += speed * sin(head.angle);
    }

    // detect & handle collisions
        for (auto& snake : snakes) {
        Segment& head = snake.get_head();

        for (auto& other : snakes) {
            if (&other == &snake) continue;// skip self

            for (auto& seg : other.segments) {
                double dist = distance(head, seg);

                // check for collision
                if (dist < head.radius + seg.radius) {
                    //todo: rip
                }
            }
        }
    }
}

World::World(vector<Snake> _snakes){

}

