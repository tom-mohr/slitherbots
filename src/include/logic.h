#include <vector>

using namespace std;
using namespace pybind11;

class Api {
    public:
        double angle;  // angle speed
}

class Snake {
    public:
        Snake();
        double x;
        double y;
        double radius;
        double angle;
    private:

};

class World {
    public:
        World();
        void step();
    private:
        vector<Snake> snakes;//.push_back(), .size()
};
