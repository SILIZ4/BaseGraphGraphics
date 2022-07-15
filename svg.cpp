#include "svg.h"
#include <stdexcept>
#include <array>
#include <unordered_map>
#include <math.h>


namespace BaseGraph { namespace Graphics {

std::unordered_map<std::string, std::string> vertexStyle {
    {"fill", "#e7e7e7"},
    {"stroke", "#333333"},
    {"stroke-width", ".7"},
    {"r", "3"},
};
std::unordered_map<std::string, std::string> edgeStyle {
    {"fill", "none"},
    {"stroke", "#333333"},
    {"stroke-width", "1"},
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


inline std::string indent(int n) {
    return std::string(4*n, ' ');
}

static void writeHeader(std::ofstream& svgFile);
static void writeDefs(std::ofstream& svgFile);
static void writeEdge(std::ofstream& svgFile, Coordinates v1, Coordinates v2, bool directed);
static void writeVertex(std::ofstream& svgFile, Coordinates vertex);

static std::array<double, 4> findTightViewBox(const std::vector<Coordinates>& vertexPositions);
static std::string getStyleString(const std::unordered_map<std::string, std::string>& style);

static double getDoubleProperty(const std::unordered_map<std::string, std::string>& style, const std::string& propertyName);

template <typename Graph>
static void _createSVG(const Graph& graph, const std::vector<Coordinates>& vertexPositions, const std::string& fileName, bool directed) {
    if (graph.getSize() != vertexPositions.size())
        throw std::logic_error("Cannot create SVG: graph has "+std::to_string(graph.getSize())+" vertices"
                " while there are " + std::to_string(vertexPositions.size()) + " vertex positions.");


    std::ofstream svgFile(fileName);
    if (graph.getSize() == 0)
        return;

    auto corners = findTightViewBox(vertexPositions);

    svgFile
        << "<svg xmlns=\"http://www.w3.org/2000/svg\""
            << " viewBox=\""
            << corners[0] << ' ' << corners[1] << ' '
            << corners[2] << ' ' << corners[3]
            << "\">\n";

    writeDefs(svgFile);

    for (auto i: graph)
        for (auto j: graph.getOutEdgesOfIdx(i))
            if (directed or i<j)
                writeEdge(svgFile, vertexPositions[i], vertexPositions[j], directed);

    for (auto i: graph)
        writeVertex(svgFile, vertexPositions[i]);

    svgFile << "</svg>";
}


void createSVG(const UndirectedGraph& graph, const std::vector<Coordinates>& vertexPositions, const std::string& fileName) {
    _createSVG(graph, vertexPositions, fileName, false);
}

void createSVG(const DirectedGraph& graph, const std::vector<Coordinates>& vertexPositions, const std::string& fileName) {
    _createSVG(graph, vertexPositions, fileName, true);
}


static std::array<double, 4> findTightViewBox(const std::vector<Coordinates>& vertexPositions) {
    if (vertexPositions.size() == 0)
        throw std::logic_error("Cannot find tight borders: no vertex in input.");

    double minX(vertexPositions[0].x), maxX(vertexPositions[0].x);
    double minY(vertexPositions[0].y), maxY(vertexPositions[0].y);

    for (auto coordinates: vertexPositions) {
        if (coordinates.x < minX)
            minX = coordinates.x;
        if (coordinates.x > maxX)
            maxX = coordinates.x;

        if (coordinates.y < minY)
            minY = coordinates.y;
        if (coordinates.y > maxY)
            maxY = coordinates.y;
    }

    double shift = getDoubleProperty(vertexStyle, "r")+.5*getDoubleProperty(vertexStyle, "stroke-width");
    // {x, y, width, height}
    return {minX-shift, minY-shift, maxX-minX+2*shift, maxY-minY+2*shift};
}


static void writeHeader(std::ofstream& svgFile) {
    svgFile
        << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
        << "<!-- Created with BaseGraph (https://base-graph.readthedocs.io/en/latest/) -->\n"
        << "\n";
};


static void writeDefs(std::ofstream& svgFile) {
    svgFile
        << indent(1) << "<defs>\n"

        << indent(2) << "<marker id=\"arrow\" markerUnits=\"strokeWidth\" "
            << getStyleString(directedEdgeMarkerStyle) << ">\n"
        << indent(3) << directedEdgeMarkerPath  << "\n"
        << indent(2) << "</marker>"

        << indent(1) << "</defs>\n";
}

std::pair<Coordinates, Coordinates> getShortenedEdge(const Coordinates& v1, const Coordinates& v2) {
    double distance = sqrt( pow(v2.x-v1.x, 2) + pow(v2.y-v1.y, 2));
    double angle = atan( (v2.y-v1.y)/(v2.x-v1.x) );

    double sign = v1.x<=v2.x ? 1:-1;
    double shift = getDoubleProperty(vertexStyle, "r")+.5*getDoubleProperty(vertexStyle, "stroke-width")
                    +1.5*getDoubleProperty(directedEdgeMarkerStyle, "markerWidth");

    Coordinates adjusted_v2 = {
        v1.x + sign*(distance-shift)*cos(angle),
        v1.y + sign*(distance-shift)*sin(angle)
    };
    return {v1, adjusted_v2};
}

void writeEdge(std::ofstream& svgFile, Coordinates v1, Coordinates v2, bool directed) {
    svgFile
        << indent(1) << "<path\n"
        << indent(2) << getStyleString(edgeStyle) << "\n";

    if (directed) {
        auto shortenedEdge = getShortenedEdge(v1, v2);
        svgFile
            << indent(2) << "marker-end=\"url(#arrow)\"\n"
            << indent(2) << "d=\""
                << "M " << shortenedEdge.first.x << ',' << shortenedEdge.first.y
                << " L " << shortenedEdge.second.x << ',' << shortenedEdge.second.y
                << "\"\n";
    }
    else {
        svgFile
            << indent(2) << "d=\""
                << "M " << v1.x << ',' << v1.y
                << " L " << v2.x << ',' << v2.y
                << "\"\n";
    }

    svgFile
        << indent(1) << "/>\n";
}


void writeVertex(std::ofstream& svgFile, Coordinates vertex) {
    svgFile
        << indent(1) << "<circle\n"
        << indent(2) << getStyleString(vertexStyle) << "\n"
        << indent(2) << "cx=\"" << vertex.x << "\"\n"
        << indent(2) << "cy=\"" << vertex.y << "\"\n"
        << indent(1) << "/>\n";
}


static std::string getStyleString(const std::unordered_map<std::string, std::string>& style) {
    std::string styleString = "";

    for (auto key_value: style)
        styleString += key_value.first + "=\"" + key_value.second + "\" ";

    return styleString;
}


static double getDoubleProperty(const std::unordered_map<std::string, std::string>& style, const std::string& propertyName) {
    double propertyValue=0;
    try {
        propertyValue = std::stod(style.at(propertyName));
    }
    catch (std::out_of_range& error) { }
    return propertyValue;
}


}} // namespace BaseGraph::Graphics
