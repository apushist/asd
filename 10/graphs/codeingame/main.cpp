#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>

using namespace std;

struct Stop {
    string name;
    double latitude, longitude;

public:
    Stop(string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}

    Stop():name(""), latitude(0),longitude(0){}
};

class Graph {
    map<string, vector<pair<string, double>>> adjList;
    
public: 


    void addEdge(string startID, string endID, double weight) {
       adjList[startID].push_back({ endID, weight });
    }

     vector < string> dijkstra(string startId, string endId) {
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        map<string, double> distance;
        map<string, string> previousNode;

        if (adjList.size() == 0)
            return vector<string>();
        if (startId == endId) {
            return vector<string>{ startId };
        }

        for (auto const& it : adjList) {
            distance[it.first] = numeric_limits<double>::infinity();
        }
        distance[startId] = 0;
        pq.push({ 0, startId });
        while (!pq.empty()) {
            string u = pq.top().second;
            pq.pop();
            for (auto const& neighbor : adjList[u]) {
                string v = neighbor.first;
                double weight = neighbor.second;

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    previousNode[v] = u;
                    pq.push({ distance[v], v });
                }
            }
        }

        vector<string> path;
        string current = endId;
        while (current != startId) {
            if(current == "")
                return vector<string>();
            path.push_back(current);
            current = previousNode[current];
        }
        path.push_back(startId);
        reverse(path.begin(), path.end());

        return path;
    }
};

double toRadians(double degrees) {
    double pi = 3.14159265359;
    return (degrees * (pi / 180));
}

double getWeight(Stop stop1, Stop stop2) {
    double x = (toRadians(stop2.longitude) - toRadians(stop1.longitude)) * cos((stop2.latitude - stop1.latitude) / 2);
    double y = toRadians(stop2.latitude) - toRadians(stop1.latitude);
    return sqrt(x * x + y * y) * 6371;
}


int main()//67%
{
    Graph g;

    string start_point;
    cin >> start_point; cin.ignore();
    string end_point;
    cin >> end_point; cin.ignore();
    int n;
    cin >> n; cin.ignore();
    
    map<string,Stop> stops;
    for (int i = 0; i < n; i++) {
        string stop_name;
        getline(cin, stop_name);

        stringstream ss(stop_name);
        string id, name;
        double latitude, longitude;
        int type;
        getline(ss, id, ',');
        getline(ss, name, '"');
        getline(ss, name, '"');
        ss.ignore();//description
        ss.ignore();//description
        ss >> latitude;
        ss.ignore();//,
        ss >> longitude;
        stops[id] = Stop(name, latitude, longitude);
    }
    
    int m;
    cin >> m; cin.ignore();
    vector<pair<Stop, Stop>> routes;
    for (int i = 0; i < m; i++) {
        string route;
        getline(cin, route);
        string start, stop;
        stringstream ss(route);
        ss >> start >> stop;
        
        g.addEdge(start, stop, getWeight(stops[start], stops[stop]));
    }

    vector<string> route = g.dijkstra(start_point, end_point);
    if (route.size() == 0) {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (string var : route)
        {
            cout << stops[var].name << "\n";
        }
    }

}