#include "kruskal.h"


int main() {
    Graph g(6);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 0, 4);
    g.add_edge(2, 0, 4);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(2, 5, 2);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 2, 3);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 2, 4);
    g.add_edge(4, 3, 3);
    g.add_edge(5, 2, 2);
    g.add_edge(5, 4, 3);
    g.kruskal();
    g.printMST();
    

}