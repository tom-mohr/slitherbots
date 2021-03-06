#include "logic.h"
#include <math.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// seed random generator

double random(double min, double max) {
    return min + double(rand()) / double(RAND_MAX) * (max - min);
}

Snake::Snake(string _name, py::function _step_fn) {//todo: pass name and step method from user
    sight_radius = 30;
    name = _name;
    step_fn = _step_fn;
    
    Segment* head = new Segment(0, 0, 10, 0);
    segments.push_back(head);
}

Segment* Snake::get_head() {
    return segments[0];
}

void Snake::apply_api(Api* api) {
    Segment* head = get_head();
    head->angle += clamp(api->angle, -0.5, 0.5);
}

Segment::Segment(double _x, double _y, double _radius, double _angle) {
    x = _x;
    y = _y;
    radius = _radius;
    angle = _angle;
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
    double i = fmod(a, b);
    if (i<a) i += b;
    return i;
}

double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double distance(Segment* a, Segment* b) {
    return hypot(a->x - b->x,  a->y - b->y);
}

// make angle to be in [-pi, pi)
double nice_angle(double angle) {
    return mod(angle + M_PI, M_2_PI) - M_PI;
}

World::World(vector<Snake> _snakes) {
    srand(time(NULL));
    for(auto& snake : _snakes){
        auto new_snake = new Snake(snake);
        snakes.push_back(new_snake);
        auto head = new_snake->get_head();
        head->x = random(-size, size);
        head->y = random(-size,size);
        head->angle = random(0, M_2_PI);
    }
    size = 512;
    speed = 5;
}

double World::wrap(double x) {
    return mod(x + size, 2 * size) - size;
}

double World::double dist(double x1, double y1, double x2, double y2) {
    return hypot(wrap(x2 - x1), wrap(y2 - y1));
}

void World::step() {
    // get api responses
    for (auto snake : snakes) {
        Api api;

        Segment* head = snake->get_head();
        
        for (auto other : snakes) {
            for (auto seg : other->segments) {
                double dist = dist(head->x, head->y, seg->x, seg->y);
                if (dist <= snake->sight_radius + seg->radius) {
                    
                    SegmentInfo si;

                    
                    si.r = dist;
                    si.dir = nice_angle(atan2(seg->y - head->y, seg->x - head->x) - head->angle);
                    si.angle = nice_angle(seg->angle - head->angle);

                    if (other == snake) {
                        api.self_segments.push_back(si);
                    } else {
                        api.segments.push_back(si);
                    }
                }
            }
        }
        snake->step_fn(api);
        // apply api object
        snake->apply_api(&api);
    }
    
    // GAME LOGIC

    // move each snake
    for (auto snake : snakes) {
        Segment* head = snake->get_head();

        if (snake->segments.size() > 1) {

            // move each segment to location of the segment in front of it
            for (int i=snake->segments.size() - 1; i > 0; i--) {// start from last index (tail)
                snake->segments[i]->x = snake->segments[i - 1]->x;
                snake->segments[i]->y = snake->segments[i - 1]->y;
            }
        }

        // move head
        head->x += speed * cos(head->angle);
        head->y += speed * sin(head->angle);

        // wrap coordinates
        for (auto seg : snake->segments) {
            seg->x = wrap(seg->x);
            seg->y = wrap(seg->y);
        }
    }

    // randomly spawn some food
    int n_food_spawn = size * size / 20000;  // how much food to spawn (constant per area)
    for (int i=0; i<n_food_spawn; i++) {
        // select random position
        Food* foo = new Food(random(-size, size), random(-size, size), 5);
        food.push_back(foo);
    }

    // detect & handle collisions
    vector<int> snakes_to_remove;  // indices that are scheduled for removal
    vector<int> food_to_remove;
    for (int i=0; i < snakes.size(); i++) {
        Snake* snake = snakes[i];
        Segment* head = snake->get_head();

        // head-snake collision (killing)
        for (auto other : snakes) {
            if (other == snake) continue;// skip self

            for (auto seg : other->segments) {

                // check for collision
                double dist = dist(head->x, head->y, seg->x, seg->y);
                if (dist < head->radius + seg->radius) {
                    // rip
                    cout << snake->name << " is dead" << endl;
                    snakes_to_remove.push_back(i);  // schedule for later removal
                }
            }
        }

        // head-food collision (eating)
        for (int j=0; j < food.size(); j++) {
            Food* foo = food[j];

            // check for collision
            double dist = dist(head->x, head->y, foo->x, foo->y);
            if (dist < head->radius) {  // head must overlap center of food (don't add food radius)
                // yum
                cout << snake->name << " eats" << endl;
                //todo: grow snake
                food_to_remove.push_back(j);
            }
        }
    }
    // remove dead snakes
    for (int i=0; i < snakes_to_remove.size(); i++) {
        // shift by i because i elements have already be deleted before, hence causing a shift in indices
        int delete_index = snakes_to_remove[i] - i;
        snakes.erase(delete_index);
    }
    // remove eaten food
    for (int i=0; i < food_to_remove.size(); i++) {
        int delete_index = food_to_remove[i] - i;
        food.erase(delete_index);
    }
}
