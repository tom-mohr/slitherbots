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
        Segment(double x, double y, double radius, double angle) {
            this.x = x;
            this.y = y;
            this.radius = radius;
            this.angle = angle;
        }
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
};

class Snake {
    public:
        Snake(string _name, py::function _step_fn);
        double sight_radius;
        vector<Segment> segments;
        Segment& get_head();  // utility method to get segements[0]
        py::function step_fn;
        void apply_api(Api api);  // translate api response to snake movement
    private:
        string name;
};


class World {
    public:
        World(vector<Snake> _snakes);
        void step();
        double speed; // how many pixels a snake moves per step
    private:
        vector<Snake> snakes;//.push_back(), .size()
};
