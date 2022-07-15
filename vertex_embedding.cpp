#include <math.h>
#include "vertex_embedding.h"

#define _USE_MATH_DEFINES


namespace BaseGraph { namespace Graphics {

std::vector<Coordinates> embedOnCircle(const UndirectedGraph& graph, double radius) {
    const auto& n = graph.getSize();
    std::vector<Coordinates> vertexPositions(n);

    double angle;
    for (auto vertex: graph) {
        angle = ((double)vertex/n - .25) * 2*M_PI;
        vertexPositions[vertex].x = radius*cos(angle);
        vertexPositions[vertex].y = radius*sin(angle);
    }
    return vertexPositions;
}


}} // namespace BaseGraph::Graphics
