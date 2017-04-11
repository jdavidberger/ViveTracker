#define _USE_MATH_DEFINES
#include <assert.h>
#include "ViveTracker.h"
#include <cmath>

void ObjectDescriptor::set(size_t idx1, size_t idx2, double val) {
    if(idx2 < idx1) return set(idx2, idx1, val);
    sizeToFit(idx2);
    assert(idx1 != idx2);
    distances[idx(idx1,idx2)] = val;
}

double ObjectDescriptor::get(size_t idx1, size_t idx2) const {
    if(idx2 < idx1) return get(idx2, idx1);
    if(idx2 >= distances.size() || idx1 >= distances.size()) {
        assert(false);
        return 0;
    }
    if(idx1 == idx2)
        return 0;

    return distances.at(idx(idx1,idx2));
}

void ObjectDescriptor::sizeToFit(size_t idx) {
    if(distances.size() <= idx)
        distances.resize(idx+1);
}

size_t ObjectDescriptor::idx(size_t idx1, size_t idx2) const {
    if(idx2 < idx1) return idx(idx2, idx1);
    size_t offset = (idx2 - 1) * (idx2 - 1);
    return offset + idx1;
}

void Tracker::Update(const std::vector<Tracker::SensorData> &data) {

}

const std::vector<Point> &Tracker::Positions(Tracker::objIdx_t objIdx) const {
    return positions.at(objIdx);
}

Plane Tracker::FindHPlane(size_t time) {
    double planeAngle = (time / 8000 * M_PI) + M_PI/2;
    Plane rtn;
    rtn.D = 0; // We treat the lighthouse as 0,0,0; so the plane must intersect there.
    rtn.A = 0;
    rtn.B = std::cos(planeAngle);
    rtn.C = std::sin(planeAngle);
    return rtn;
}

Plane Tracker::FindVPlane(size_t time) {
    double planeAngle = time / 8000 * M_PI;
    Plane rtn;
    rtn.D = 0; // We treat the lighthouse as 0,0,0; so the plane must intersect there.
    rtn.B = 0;
    rtn.A = std::cos(planeAngle);
    rtn.C = std::sin(planeAngle);
    return rtn;
}

Line Tracker::FindLine(size_t timeH, size_t timeV) {
    return FindHPlane(timeH).Intersection(FindVPlane(timeV));
}

