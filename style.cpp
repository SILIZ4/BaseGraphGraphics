#include <unordered_map>
#include <string>


namespace BaseGraph { namespace graphics {

std::unordered_map<std::string, std::string> vertexStyle {
    {"fill", "#e7e7e7"},
    {"stroke", "#333333"},
    {"stroke-width", ".005"},
    {"r", "0.02"},
};
std::unordered_map<std::string, std::string> edgeStyle {
    {"fill", "none"},
    {"stroke", "#333333"},
    {"stroke-width", "0.008"},
};
std::unordered_map<std::string, std::string> directedEdgeMarkerStyle {
    {"viewBox", "0 0 5 5"},
    {"refX", "1"},
    {"refY", "5"},
    {"markerWidth", "2"},
    {"markerHeight", "2"},
    {"orient", "auto"},
};
std::string directedEdgeMarkerPath =
      "<path d=\"M 0 0 L 10 5 L 0 10 z\" fill=\"" + edgeStyle["stroke"] + "\"/>";

}} // namespace BaseGraph::graphics
