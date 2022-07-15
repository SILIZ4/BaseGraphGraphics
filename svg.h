#ifndef BASEGRAPH_EXTENSION_GRAPHICS_SVG
#define BASEGRAPH_EXTENSION_GRAPHICS_SVG


#include <fstream>
#include <string>
#include <vector>
#include "BaseGraph/undirectedgraph.h"
#include "vertex_embedding.h"


namespace BaseGraph{ namespace Graphics {

void createSVG(const DirectedGraph&, const std::vector<Coordinates>&, const std::string& fileName);
void createSVG(const UndirectedGraph&, const std::vector<Coordinates>&, const std::string& fileName);


}} // namespace BaseGraph::Graphics

#endif
