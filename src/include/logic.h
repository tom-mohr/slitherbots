#ifndef LOGIC_H
#define LOGIC_H
#include <vector>
#include <pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;

class Segment {
    public:
        double x;
        double y;
        double radius;
        double angle;
        Segment(double x, double y, double radius, double angle);
};

class SegmentInfo {
    public:
        double angle;  // orientation
        
        // polar coordinates
        double dir;
        double r;
};

class Api {
    public:
        double angle;  // angle speed
        vector<SegmentInfo> segments;
        vector<SegmentInfo> self_segments;
};

class Snake {
    public:
        Snake(string _name, py::function _step_fn);
        string name;
        double sight_radius;
        vector<Segment*> segments;
        Segment* get_head();  // utility method to get segements[0]
        py::function step_fn;
        void apply_api(Api* api);  // translate api response to snake movement
};


class World {
    public:
        World(vector<Snake>);
        void step();
        double speed; // how many pixels a snake moves per step
        double size; // world goes from -size to +size in each dimension
    private:
        vector<Snake*> snakes;
        double wrap(double x);
        double dist(double x1, double y1, double x2, double y2);
};


inline void util(int schoenheit){

}
#endif

