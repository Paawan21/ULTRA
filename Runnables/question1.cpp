
#include "../Algorithms/Dijkstra/Dijkstra.h"
#include "../DataStructures/Graph/Classes/StaticGraph.h" 
#include "../DataStructures/Graph/Graph.h"
#include "../DataStructures/Graph/Utils/IO.h"
#include "../Helpers/Timer.h"
#include <iostream>
#include <map>

int main(){
    StaticGraph<NoVertexAttributes,WithTravelTime> graph;
    Graph::fromDimacs("./USA-road-d.FLA.gr",graph);
    Dijkstra<StaticGraph<NoVertexAttributes,WithTravelTime>> dijkstra(graph);
   

    Range<Vertex> graph_vertices = graph.vertices();

    std::random_device random_gen; //non-deterministic distributor
    std::mt19937 gen(random_gen()); //Mersene twister

    
    int number_of_vertices = graph_vertices.size();

    Timer timer;
    
    for(size_t i = 0; i<200;++i){
        std::uniform_int_distribution<> dis(0,number_of_vertices-i-1);
        int random_source = dis(gen);
        int random_destination = dis(gen);

        Vertex random_source_vertex = graph_vertices[random_source];
        Vertex random_destination_vertex = graph_vertices[random_destination];

        dijkstra.run(random_source_vertex,random_destination_vertex);

        std::vector<Vertex> path = dijkstra.getPath(random_destination_vertex);

        int distance = dijkstra.getDistance(random_destination_vertex);

    }

    double milliseconds_passed = timer.elapsedMilliseconds();
    std::cout<<"Total runtime in seconds for 200 random Dijkstra\'s : "<<milliseconds_passed/1000<<" seconds"<<std::endl;



        

/*
    //TEST CASES [VWorks]
    //Source = 0, Target = 1
    //Source = 264345, Target = 264327

    Vertex source(1234);
    Vertex target(1272);
    dijkstra.run(source,target);

    std::vector<Vertex> path = dijkstra.getPath(target);

    for(Vertex vert : path){
        std::cout<<vert<<", ";
    }
    std::cout<<std::endl;
    int length = dijkstra.getDistance(target);
    std::cout<<"Length: "<< length<<std::endl;

*/
    return 0;
}

