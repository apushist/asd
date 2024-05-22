#pragma once

#include <iostream>
#include <vector>
#include <algorithm>



class Graph {
    std::vector<std::pair<int, std::pair<int, int>>> graph; // graph
    std::vector<std::pair<int, std::pair<int, int>>> tree; // mst
    int* cluster;

public:
    Graph(int size) {
        cluster = new int[size];

        for (int i = 0; i < size; i++)
            cluster[i] = i;
    }
    void add_edge(int left, int right, int weight) {
        graph.push_back(std::make_pair(weight, std::make_pair(left, right)));
    }

    void union_set(int l, int r) {
        cluster[l] = cluster[r];
    }
    int find_set(int i) {
        if (i == cluster[i])
            return i;
        else
            return find_set(cluster[i]);
    }

    void kruskal() {
        int i, uRep, vRep;
        std::sort(graph.begin(), graph.end());
        for (i = 0; i < graph.size(); i++) {
            uRep = find_set(graph[i].second.first);
            vRep = find_set(graph[i].second.second);
            if (uRep != vRep) {
                tree.push_back(graph[i]);
                union_set(uRep, vRep);
            }
        }
    }

    void printMST() {
        std::cout << "Edge :" << " Weight" << std::endl;
        for (int i = 0; i < tree.size(); i++) {
            std::cout << tree[i].second.first << " - " << tree[i].second.second << " : "
                << tree[i].first;
            std::cout << "\n";
        }
    }
};
