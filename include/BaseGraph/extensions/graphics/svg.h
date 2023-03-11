#ifndef BASEGRAPH_EXTENSION_GRAPHICS_SVG
#define BASEGRAPH_EXTENSION_GRAPHICS_SVG


#include <fstream>
#include <string>
#include <vector>

#include <BaseGraph/undirectedgraph.h>
#include "vertex_layouts.h"


namespace BaseGraph{ namespace graphics {

typedef std::unordered_map<std::string, std::string> Style;

extern Style vertexStyle;
extern Style edgeStyle;
extern Style directedEdgeMarkerStyle;
extern std::string directedEdgeMarkerPath;


void createSVG(const DirectedGraph&, const std::vector<Coordinates>&, const std::string& fileName);
void createSVG(const UndirectedGraph&, const std::vector<Coordinates>&, const std::string& fileName);


}} // namespace BaseGraph::graphics

#endif
