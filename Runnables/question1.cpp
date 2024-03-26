
#include "../Algorithms/Dijkstra/Dijkstra.h"
#include "../DataStructures/Graph/Classes/StaticGraph.h" 
#include "../DataStructures/Graph/Graph.h"
#include "../DataStructures/Graph/Utils/IO.h"
#include "../Helpers/Timer.h"
#include <iostream>
#include <map>

int main(){
    StaticGraph<NoVertexAttributes,WithTravelTime> graph;
    Graph::fromDimacs("USA-road-d.FLA.gr",graph);
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
        if(!path.empty() &&
            distance == 0){
            std::cout<<"Error: Path is not empty but distance is 0"<<std::endl;
        }
        else{
            std::cout<<"Path is empty and distance is 0"<<std::endl;
        }
        for(Vertex vert : path){
            std::cout<<vert<<", ";
        }
        std::cout<<std::endl<<"Length: "<< distance<<std::endl;

    }double milliseconds_passed = timer.elapsedMilliseconds();
    std::cout<<"Total runtime in seconds for 200 random Dijkstra\'s : "<<milliseconds_passed/1000<<" seconds"<<std::endl;
    return 0;
}

