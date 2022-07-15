#ifndef BASEGRAPH_EXTENSION_GRAPHICS_EMBEDDING_H
#define BASEGRAPH_EXTENSION_GRAPHICS_EMBEDDING_H

#include <vector>
#include "BaseGraph/undirectedgraph.h"

namespace BaseGraph{ namespace Graphics {


struct Coordinates {
    double x;
    double y;
};

std::vector<Coordinates> embedOnCircle(const UndirectedGraph&, double radius=1);


}} // namespace BaseGraph::Graphics


#endif
