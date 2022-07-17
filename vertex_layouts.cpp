#include <math.h>
#include <functional>
#include <random>
#include "BaseGraph/undirectedgraph.h"
#include "BaseGraph/extensions/random/rng.h"
#include "vertex_embedding.h"


#define _USE_MATH_DEFINES


namespace BaseGraph { namespace graphics {

std::vector<Coordinates> findCircleLayout(size_t graphSize, double radius) {
    std::vector<Coordinates> vertexPositions(graphSize);

    double angle;
    for (size_t i=0; i<graphSize; i++) {
        angle = ((double)i/graphSize - .25) * 2*M_PI;
        vertexPositions[i].x = radius*cos(angle);
        vertexPositions[i].y = radius*sin(angle);
    }
    return vertexPositions;
}

Coordinates min(const Coordinates& coordinates, double value) {
    return {std::min(coordinates.x, value), std::min(coordinates.y, value)};
}

// Algorithm of T. M. J. Fruchterman and E. M. Reingold
std::vector<Coordinates> findForceDirectedLayout(const UndirectedGraph& graph, size_t iterations, double k, double width, double height) {
    size_t n = graph.getSize();
    double area = width*height;

    if (k<=0)
        k = sqrt(area/n);

    double temperature = .1*sqrt(area);
    double coolingFactor = temperature/(iterations+1);

    std::vector<Coordinates> vertexPositions(n), vertexDisplacement(n);

    std::uniform_real_distribution<double> initialPositionDistribution(0, 1);
    for (auto& position: vertexPositions) {
        position.x = initialPositionDistribution(BaseGraph::random::rng)*.25*width;
        position.y = initialPositionDistribution(BaseGraph::random::rng)*.25*height;
    }

    auto attract = [&k] (double deltaNorm) {
        return -deltaNorm*deltaNorm/k;
    };
    auto repel = [&k] (double deltaNorm) {
        return k*k/deltaNorm;
    };

    auto applyForce = [&vertexDisplacement, &vertexPositions] (VertexIndex i, VertexIndex j, const std::function<double(double)>& force) {
        Coordinates delta = vertexPositions[i]-vertexPositions[j];
        double deltaNorm = delta.norm();
        deltaNorm = std::max(deltaNorm, 0.01);
        Coordinates displacement = delta/deltaNorm * force(deltaNorm);

        vertexDisplacement[i] += displacement;
        vertexDisplacement[j] -= displacement;
    };
    auto cool = [&coolingFactor] (double t) { return t-coolingFactor; };


    for (size_t iteration=0; iteration<iterations; iteration++) {
        for (auto& d: vertexDisplacement) {
            d.x = 0; d.y=0;
        }

        for (auto i: graph) {
            for (VertexIndex j=i+1; j!=n; j++)
                applyForce(i, j, repel);

            for (auto j: graph.getOutEdgesOfIdx(i))
                if (i<=j)
                    applyForce(i, j, attract);
        }

        for (auto i: graph) {
            Coordinates& position = vertexPositions[i];
            Coordinates& displacement = vertexDisplacement[i];

            position += displacement/displacement.norm() * temperature;
            //position.x = std::min(.5*width, std::max(-.5*width, position.x));
            //position.y = std::min(.5*height, std::max(-.5*height, position.y));
        }
        temperature = cool(temperature);
    }

    return vertexPositions;
}

}} // namespace BaseGraph::graphics
