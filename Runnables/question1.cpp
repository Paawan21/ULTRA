#include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Classes/StaticGraph.h"
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
#include <numeric> 
using namespace std;
using namespace Graph;

int main() {
    StaticGraph<
        Meta::List<Attribute<BeginOut, Edge>, Attribute<OutDegree, size_t>, Attribute<IncomingEdges, std::vector<Edge>>, Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>, 
        Meta::List<Attribute<Valid, bool>, Attribute<IncomingEdgePointer, size_t>, Attribute<FromVertex, Vertex>, Attribute<ToVertex, Vertex>>
    > graph;
    
    // Load graph from DIMACS file
    fromDimacs("/Users/paawankashyap/Downloads/USA-road-d.FLA/USA-road-d.FLA", graph);
    vector<Vertex> validVertices;
    for (Vertex v : graph.vertices()) {
        if(v.isValid() == true) {
            validVertices.push_back(v);
        }
    }
    if (validVertices.empty()) {
        cout << "No valid vertices found." << endl;
        return 0;
    }

    random_device rd;
    mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd() 
    uniform_int_distribution<> dis(0, validVertices.size() - 1);
    
    // Print basic information about the graph
    cout << "Graph shape is " << graph.numVertices() << " vertices and " << graph.numEdges() << " edges." << endl;
    auto start = chrono::high_resolution_clock::now();
    // Define source and target vertices
    Vertex src = validVertices[dis(gen)-1];  
    Vertex trgt = validVertices[dis(gen)-1]; 
    
    // Check if the source and target vertices are valid
    if (!graph.isVertex(src) || !graph.isVertex(trgt)) {
        cout << "Source and/or target vertices are not valid." << endl;
        return 0;
    }

    // Create Dijkstra instance and run algorithm
    Dijkstra<StaticGraph<
        Meta::List<Attribute<BeginOut, Edge>, Attribute<OutDegree, size_t>, Attribute<IncomingEdges, std::vector<Edge>>, Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>, 
        Meta::List<Attribute<Valid, bool>, Attribute<IncomingEdgePointer, size_t>, Attribute<FromVertex, Vertex>, Attribute<ToVertex, Vertex>>
    >, false> dijkstra(graph, graph[Weight]);

    // Run Dijkstra's algorithm
    dijkstra.run(src, trgt);

    // Retrieve shortest path and distance
    int dist = dijkstra.getDistance(trgt);
    vector<Vertex> sp = dijkstra.getPath(trgt);
    
    // Print distance from source to target
    cout << "Distance from " << src << " to " << trgt << " is " << dist << endl;

    // Print shortest path
    if (!sp.empty()) {
        cout << "Path from " << src << " to " << trgt << " is ";
        for (Vertex v : sp) {
            cout << v << " - ";
        }
        cout << endl;

        // Compute shortest path length
        int shortestPathLength = 0;
        for (int i = 0; i < sp.size() - 1; ++i) {
            Vertex u = sp[i];
            Vertex v = sp[i + 1];
            bool edgeFound = false;
            for (Edge e : graph.edgesFrom(u)) {
                if (graph.get(ToVertex, e) == v) {
                    shortestPathLength += graph[Weight][e];
                    edgeFound = true;
                    break;
                }
            }
            if (!edgeFound) {
                cout << "Error: Edge not found between vertices " << u << " and " << v << endl;
                // Handle the error condition (optional)
            }
        }
    }
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " seconds" << endl;
    return 0;
}

// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Classes/DynamicGraph.h"
// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Utils/Utils.h"
// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/Algorithms/Dijkstra/Dijkstra.h"
// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Graph.h"
// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Utils/IO.h"
// #include "/Users/paawankashyap/Desktop/ULTRA/ULTRA/DataStructures/Graph/Classes/GraphInterface.h"
// #include <iostream>
// #include <vector>
// #include <random>
// #include <chrono>
// #include <string>
// #include <numeric> // Include the <numeric> header for accumulate
// using namespace std;
// using namespace Graph;

// int main() {
//     DynamicGraphImplementation<
//         Meta::InsertAttribute<Attribute<BeginOut, Edge>,
//         Meta::InsertAttribute<Attribute<OutDegree, size_t>,
//         Meta::InsertAttribute<Attribute<IncomingEdges, std::vector<Edge>>,
//         Meta::SortAttributes<Meta::List<Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>>>>>,
//         Meta::InsertAttribute<Attribute<Valid, bool>,
//         Meta::InsertAttribute<Attribute<IncomingEdgePointer, size_t>,
//         Meta::InsertAttribute<Attribute<FromVertex, Vertex>,
//         Meta::InsertAttribute<Attribute<ToVertex, Vertex>,
//         Meta::SortAttributes<Meta::List<Attribute<Weight, int>>>>>>>> graph;
    
//     fromDimacs("/Users/paawankashyap/Downloads/USA-road-d.FLA/USA-road-d.FLA", graph);

//     cout << "Graph shape is " << graph.numVertices() << " " << graph.numEdges() << endl;
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<> dis(0, graph.numVertices() - 1);
    
//     auto start = chrono::high_resolution_clock::now();
//     for (int i = 0; i < 10; ++i) {
//         Vertex src = Vertex(dis(gen));
//         Vertex trgt = Vertex(dis(gen));

//         Dijkstra<DynamicGraphImplementation<
//             Meta::InsertAttribute<Attribute<BeginOut, Edge>,
//             Meta::InsertAttribute<Attribute<OutDegree, size_t>,
//             Meta::InsertAttribute<Attribute<IncomingEdges, std::vector<Edge>>,
//             Meta::SortAttributes<Meta::List<Attribute<Coordinates, Geometry::Point>, Attribute<Weight, int>>>>>>,
//             Meta::InsertAttribute<Attribute<Valid, bool>,
//             Meta::InsertAttribute<Attribute<IncomingEdgePointer, size_t>,
//             Meta::InsertAttribute<Attribute<FromVertex, Vertex>,
//             Meta::InsertAttribute<Attribute<ToVertex, Vertex>,
//             Meta::SortAttributes<Meta::List<Attribute<Weight, int>>>>>>>>, false> dijkstra(graph, graph[Weight]);
//         dijkstra.run(src, trgt);
//         vector<Vertex> sp = dijkstra.getPath(trgt);

//         cout << "Path from " << src << " to " << trgt << " is ";
//         for (Vertex v : sp) {
//             cout << v << "-" << " ";
//         }
//         cout << endl;
//     }
//     auto end = chrono::high_resolution_clock::now();
//     cout << "Time taken for 200 iterations is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

//     return 0;
// }
