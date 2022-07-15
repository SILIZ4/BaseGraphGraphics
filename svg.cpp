#include "svg.h"
#include <stdexcept>
#include <array>


namespace BaseGraph { namespace Graphics {

double edgeStrokeWidth = 1;

std::string edgeStyle = "fill:none;stroke:#333333;stroke-width:1;stroke-opacity:.8";
std::string vertexStyle = "fill:#e7e7e7;fill-opacity:1;stroke:#333333;stroke-width:0.708;stroke-opacity:1";
int vertexRadius = 3;


inline std::string indent(int n) {
    return std::string(4*n, ' ');
}
static std::ofstream openSVG(const std::string& fileName);
static void writeEdge(std::ofstream& svgFile, Coordinates v1, Coordinates v2);
static void writeVertex(std::ofstream& svgFile, Coordinates vertex);
static std::array<double, 4> findTightViewBox(const std::vector<Coordinates>& vertexPositions);

void createSVG(const UndirectedGraph& graph, const std::vector<Coordinates>& vertexPositions, const std::string& fileName) {
    if (graph.getSize() != vertexPositions.size())
        throw std::logic_error("Cannot create SVG: graph has "+std::to_string(graph.getSize())+" vertices"
                " while there are " + std::to_string(vertexPositions.size()) + " vertex positions.");

    auto svgFile = openSVG(fileName);
    if (graph.getSize() == 0)
        return;

    auto corners = findTightViewBox(vertexPositions);

    svgFile
        << "<svg xmlns=\"http://www.w3.org/2000/svg\""
            << " viewBox=\""
            << corners[0] << ' ' << corners[1] << ' '
            << corners[2] << ' ' << corners[3]
            << "\">\n";

    for (auto i: graph)
        for (auto j: graph.getOutEdgesOfIdx(i))
            if (i<j)
                writeEdge(svgFile, vertexPositions[i], vertexPositions[j]);

    for (auto i: graph)
        writeVertex(svgFile, vertexPositions[i]);

    svgFile << "</svg>";
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

    double shift = vertexRadius+.5*edgeStrokeWidth;
    // {x, y, width, height}
    return {minX-shift, minY-shift, maxX-minX+2*shift, maxY-minY+2*shift};
}


std::ofstream openSVG(const std::string& fileName) {
    std::ofstream svgFile(fileName);

    svgFile
        << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
        << "<!-- Created with BaseGraph (https://base-graph.readthedocs.io/en/latest/) -->\n"
        << "\n";

    return svgFile;
};

void writeEdge(std::ofstream& svgFile, Coordinates v1, Coordinates v2) {
    svgFile
        << indent(1) << "<path\n"
        << indent(2) << "style=\"" << edgeStyle << "\"\n"
        << indent(2) << "d=\""
            << "M " << v1.x << ',' << v1.y
            << " L " << v2.x << ',' << v2.y
            << "\"\n"
        << indent(1) << "/>\n";
}

void writeVertex(std::ofstream& svgFile, Coordinates vertex) {
    svgFile
        << indent(1) << "<circle\n"
        << indent(2) << "style=\"" << vertexStyle << "\"\n"
        << indent(2) << "cx=\"" << vertex.x << "\"\n"
        << indent(2) << "cy=\"" << vertex.y << "\"\n"
        << indent(2) << "r=\"" << vertexRadius << "\"\n"
        << indent(1) << "/>\n";
}

}} // namespace BaseGraph::Graphics
