#include <vector>

using namespace std;
//using namespace pybind11;

class Api {
    public:
        double angle;  // angle speed
        vector<SegmentInfo> segments;
};

class SegmentInfo {
    public:
        double angle;  // orientation

        // polar coordinates
        double dir;
        double r;
};

class Snake {
    public:
        Snake();
        //todo: username
        //todo: step method from user
        double sight_radius;
        vector<Segment> segments;
        Segment& get_head();  // utility method to get segements[0]
        void apply_api(Api api);  // translate api response to snake movement
    private:
};

class Segment {
    public:
        Segment();
        double x;
        double y;
        double radius;
        double angle;
};

class World {
    public:
        World();
        void step();
        double speed; // how many pixels a snake moves per step
    private:
        vector<Snake> snakes;//.push_back(), .size()
};
