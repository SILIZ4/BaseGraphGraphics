#ifndef BASEGRAPH_EXTENSION_GRAPHICS_EMBEDDING_H
#define BASEGRAPH_EXTENSION_GRAPHICS_EMBEDDING_H

#include <vector>
#include "BaseGraph/undirectedgraph.h"
#include <math.h>


namespace BaseGraph{ namespace graphics {


struct Coordinates {
    double x;
    double y;

    double norm() const {
        return sqrt(x*x + y*y);
    }
    double dot(const Coordinates& other) const {
        return x*other.x + y*other.y;
    }
    Coordinates operator-(const Coordinates& other) const {
        return Coordinates {x-other.x, y-other.y};
    }
    Coordinates operator+(const Coordinates& other) const {
        return Coordinates {x-other.x, y-other.y};
    }
    Coordinates operator*(double constant) const {
        return Coordinates {x*constant, y*constant};
    }
    Coordinates operator*(const Coordinates& other) const {
        return Coordinates {x*other.x, y*other.y};
    }
    Coordinates operator/(double constant) const {
        return Coordinates {x/constant, y/constant};
    }
    Coordinates operator/(const Coordinates& other) const {
        return Coordinates {x/other.x, y/other.y};
    }
    void operator+=(const Coordinates& other) {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Coordinates& other) {
        x -= other.x;
        y -= other.y;
    }
};

std::vector<Coordinates> findCircleLayout(size_t graphSize, double radius=1);
std::vector<Coordinates> findForceDirectedLayout(const UndirectedGraph& graph, size_t iterations=100, double k=-1, double width=1, double height=1);


}} // namespace BaseGraph::graphics


#endif
