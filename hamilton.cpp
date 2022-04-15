#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, int> pdi;
typedef pair<double, pii> pdii;
#define mkpair(x, y) make_pair(x, y)

void calculateHamiltonWithNearestNeighbor(ifstream &inp) {
    int numberOfNodes, numberOfEdges, startPoint;
    inp>>numberOfNodes>>numberOfEdges>>startPoint;

    vector<pdi> adjList[numberOfNodes];
    for(int i=0; i<numberOfEdges; i++) {
        int source, dest;
        double distance;
        inp>>source>>dest>>distance;

        adjList[source - 1].push_back(mkpair(distance, dest - 1));
    }

    for(auto &i: adjList)
        sort(i.begin(), i.end());

    vector<int> visitedNode;
    double totalDistance = 0.0;

    auto currentNode = mkpair(0.0, startPoint - 1);
    bool isStartSearch = true;
    cout<<"Diawali dari verteks: "<<currentNode.second + 1<<'\n';
    while(true) {
        if(find(visitedNode.begin(), visitedNode.end(), currentNode.second) != visitedNode.end()) {
            cout<<"Berpotensi infinite loop.\n";
            break;
        }

        if(!isStartSearch) {
            visitedNode.push_back(currentNode.second);
            totalDistance += currentNode.first;
            cout<<"Menuju verteks "<<currentNode.second + 1<<" dengan jarak "<<currentNode.first<<" km."<<'\n';
            cout<<"Total jarak tempuh saat ini: "<<totalDistance<<" km.\n";
        }

        if(currentNode.second + 1 == startPoint && !isStartSearch)
            break;
        if(isStartSearch)
            isStartSearch = false;

        for(auto i: adjList[currentNode.second])
            if(find(visitedNode.begin(), visitedNode.end(), i.second) == visitedNode.end()) {
                currentNode = i;
                break;
            }
    }

    cout<<"\nJalur yang ditempuh: "<<startPoint<<" - ";
    for(int i=0; i<visitedNode.size(); i++) {
        cout<<visitedNode[i] + 1;
        if(i < visitedNode.size() - 1)
            cout<<" - ";
        else cout<<"\n";
    }
    cout<<"Total jarak: "<<totalDistance<<" km.\n";
}

int main() {
    auto TMBRouteFile = ifstream("hamiltonTMB.txt");

    calculateHamiltonWithNearestNeighbor(TMBRouteFile);

    return 0;
}