#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Classes/DynamicGraph.h"
#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Utils/Utils.h"
#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/Algorithms/Dijkstra/Dijkstra.h"
#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Graph.h"
#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Utils/IO.h"
#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Classes/GraphInterface.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <numeric> // Include the <numeric> header for accumulate
using namespace std;
using namespace Graph;

int main() {
    DynamicGraphImplementation<
        Meta::InsertAttribute<Attribute<BeginOut, Edge>,
        Meta::InsertAttribute<Attribute<OutDegree, size_t>,
        Meta::InsertAttribute<Attribute<IncomingEdges, std::vector<Edge>>,
        Meta::SortAttributes<Meta::List<Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>>>>>,
        Meta::InsertAttribute<Attribute<Valid, bool>,
        Meta::InsertAttribute<Attribute<IncomingEdgePointer, size_t>,
        Meta::InsertAttribute<Attribute<FromVertex, Vertex>,
        Meta::InsertAttribute<Attribute<ToVertex, Vertex>,
        Meta::SortAttributes<Meta::List<Attribute<Weight, int>>>>>>>> graph;
    
    fromDimacs("/Users/paawankashyap/Downloads/USA-road-d.FLA/USA-road-d.FLA", graph);

    cout << "Graph shape is " << graph.numVertices() << " " << graph.numEdges() << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, graph.numVertices() - 1);
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) {
        Vertex src = Vertex(dis(gen));
        Vertex trgt = Vertex(dis(gen));

        Dijkstra<DynamicGraphImplementation<
            Meta::InsertAttribute<Attribute<BeginOut, Edge>,
            Meta::InsertAttribute<Attribute<OutDegree, size_t>,
            Meta::InsertAttribute<Attribute<IncomingEdges, std::vector<Edge>>,
            Meta::SortAttributes<Meta::List<Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>>>>>,
            Meta::InsertAttribute<Attribute<Valid, bool>,
            Meta::InsertAttribute<Attribute<IncomingEdgePointer, size_t>,
            Meta::InsertAttribute<Attribute<FromVertex, Vertex>,
            Meta::InsertAttribute<Attribute<ToVertex, Vertex>,
            Meta::SortAttributes<Meta::List<Attribute<Weight, int>>>>>>>>, false> dijkstra(graph, graph[Weight]);
        dijkstra.run(src, trgt);
        vector<Vertex> sp = dijkstra.getPath(trgt);

        cout << "Path from " << src << " to " << trgt << " is ";
        for (Vertex v : sp) {
            cout << v << "-" << " ";
        }
        cout << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Time taken for 200 iterations is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}
