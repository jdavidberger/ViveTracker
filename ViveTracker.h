#pragma once

#include <map>
#include <vector>
#include <stddef.h>
#include "Geom.h"

struct ObjectDescriptor {
    std::vector<double> distances;
    void set(size_t idx1, size_t idx2, double val);
    double get(size_t idx1, size_t idx2) const;
private:
    size_t idx(size_t idx1, size_t idx2) const;
    void sizeToFit(size_t idx);
};


struct Tracker {
    static Plane FindHPlane(size_t time);
    static Plane FindVPlane(size_t time);
    static Line FindLine(size_t timeH, size_t timeV);

    typedef size_t objIdx_t;
    typedef size_t sensorIdx_t;
    struct SensorData {
        objIdx_t obj;
        sensorIdx_t sensor;
        size_t timeHorizontal, timeVertical;
    };

    std::vector<ObjectDescriptor> descriptors;

    void Update(const std::vector<SensorData>& data);

    const std::vector<Point>& Positions(objIdx_t objIdx) const;

private:
    std::map< objIdx_t, std::vector<Point> > positions;
    std::map< objIdx_t, std::vector<double> > errors;
};