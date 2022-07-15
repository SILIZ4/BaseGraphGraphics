#include <math.h>
#include "vertex_embedding.h"

#define _USE_MATH_DEFINES


namespace BaseGraph { namespace Graphics {

std::vector<Coordinates> embedOnCircle(size_t graphSize, double radius) {
    std::vector<Coordinates> vertexPositions(graphSize);

    double angle;
    for (size_t i=0; i<graphSize; i++) {
        angle = ((double)i/graphSize - .25) * 2*M_PI;
        vertexPositions[i].x = radius*cos(angle);
        vertexPositions[i].y = radius*sin(angle);
    }
    return vertexPositions;
}


}} // namespace BaseGraph::Graphics
