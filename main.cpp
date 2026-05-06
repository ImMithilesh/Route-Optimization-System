#include <iostream>
#include <string>
#include <map>
#include "Graph.h"
#include "RouteOptimizer.h"

using namespace std;

void displayMenu()
{
    cout << "\n===== Route Optimization System =====\n";
    cout << "1. View Graph\n";
    cout << "2. Select Vehicle Type\n";
    cout << "3. Find Shortest Path\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void displayVehicleMenu()
{
    cout << "\nSelect Vehicle Type:\n";
    cout << "1. Car\n";
    cout << "2. Bicycle\n";
    cout << "3. Walking\n";
    cout << "Enter your choice: ";
}
// Graph Sample

void initializeSampleGraph(Graph &graph)
{
    // Add nodes
    graph.addNode(0, "Home");
    graph.addNode(1, "School");
    graph.addNode(2, "Hospital");
    graph.addNode(3, "Market");
    graph.addNode(4, "Park");
    graph.addNode(5, "Office");

    // Add edges with different weights for different vehicles
    // Home connections
    map<VehicleType, int> homeSchool = {{CAR, 5}, {BICYCLE, 7}, {WALKING, 10}};
    graph.addBidirectionalEdgeWithVehicleWeights(0, 1, homeSchool);

    map<VehicleType, int> homeHospital = {{CAR, 10}, {BICYCLE, 12}, {WALKING, 15}};
    graph.addBidirectionalEdgeWithVehicleWeights(0, 2, homeHospital);

    map<VehicleType, int> homeMarket = {{CAR, 15}, {BICYCLE, 18}, {WALKING, 25}};
    graph.addBidirectionalEdgeWithVehicleWeights(0, 3, homeMarket);

    // School connections
    map<VehicleType, int> schoolHospital = {{CAR, 8}, {BICYCLE, 10}, {WALKING, 12}};
    graph.addBidirectionalEdgeWithVehicleWeights(1, 2, schoolHospital);

    map<VehicleType, int> schoolPark = {{CAR, 12}, {BICYCLE, 8}, {WALKING, 15}};
    graph.addBidirectionalEdgeWithVehicleWeights(1, 4, schoolPark);

    // Hospital connections
    map<VehicleType, int> hospitalMarket = {{CAR, 7}, {BICYCLE, 6}, {WALKING, 10}};
    graph.addBidirectionalEdgeWithVehicleWeights(2, 3, hospitalMarket);

    map<VehicleType, int> hospitalOffice = {{CAR, 20}, {BICYCLE, 22}, {WALKING, 30}};
    graph.addBidirectionalEdgeWithVehicleWeights(2, 5, hospitalOffice);

    // Market connections
    map<VehicleType, int> marketPark = {{CAR, 6}, {BICYCLE, 5}, {WALKING, 8}};
    graph.addBidirectionalEdgeWithVehicleWeights(3, 4, marketPark);

    map<VehicleType, int> marketOffice = {{CAR, 9}, {BICYCLE, 10}, {WALKING, 15}};
    graph.addBidirectionalEdgeWithVehicleWeights(3, 5, marketOffice);

    // Park-Office connection
    map<VehicleType, int> parkOffice = {{CAR, 11}, {BICYCLE, 9}, {WALKING, 12}};
    graph.addBidirectionalEdgeWithVehicleWeights(4, 5, parkOffice);
}

// 🔹 NEW: User Input Graph Initialization
void initializeUserGraph(Graph &graph, int numNodes)
{
    cout << "\nEnter names for each node:\n";
    for (int i = 0; i < numNodes; i++)
    {
        string name;
        cout << "Enter name for node " << i << ": ";
        cin >> name;
        graph.addNode(i, name);
    }

    int edges;
    cout << "\nEnter number of edges: ";
    cin >> edges;

    cout << "Enter source destination index and weight of vehicle Car Bicycle Walking\n";
    // cout << "\nEdge " << i + 1 << ":\n";
    cout<<"Enter the edge(0-"<<edges<<")";
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u>>v;
        // cout << "Enter destination node index:uu  ";
        // cin >> v;

        map<VehicleType, int> weights;

        int car, bicycle, walking;
        // cout << "Enter weight for Car: ";
        // cin >> car;
        // cout << "Enter weight for Bicycle: ";
        // cin >> bicycle;
        // cout << "Enter weight for Walking: ";
        // cin >> walking;
        cin>> car >>bicycle>>walking;
        weights[CAR] = car;
        weights[BICYCLE] = bicycle;
        weights[WALKING] = walking;

        graph.addBidirectionalEdgeWithVehicleWeights(u, v, weights);
    }
}

int main()
{
    int graph_choice;
    int NUM_NODES;
    cout << "Do you want to load graph Yes:1  No: 0 :";
    cin >> graph_choice;

    if (graph_choice == 1)
    {
        NUM_NODES = 6;
    }
    else
    {
        cout << "Enter number of nodes: ";
        cin >> NUM_NODES;
    }

    Graph graph(NUM_NODES);

    if (graph_choice == 1)
    {
        initializeSampleGraph(graph);
    }
    else
    {
        initializeUserGraph(graph, NUM_NODES);
    }

    RouteOptimizer optimizer(graph);

    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\n";
            graph.printGraph();
            break;
        }
        case 2:
        {
            //int vehicleChoice;
            //displayVehicleMenu();
            //cin >> vehicleChoice;

            //switch (vehicleChoice)
            //{
            //case 1:
                //optimizer.setVehicle(CAR);
                //cout << "Vehicle set to Car.\n";
                //break;
            //case 2:
                //optimizer.setVehicle(BICYCLE);
                //cout << "Vehicle set to Bicycle.\n";
                //break;
            //case 3:
                //optimizer.setVehicle(WALKING);
                //cout << "Vehicle set to Walking.\n";
                //break;
            default:
                //cout << "Invalid vehicle choice. Using default (Car).\n";
                optimizer.setVehicle(CAR);
            }
            break;
        }
        case 3:
        {
            cout << "\nAvailable locations:\n";
            for (int i = 0; i < NUM_NODES; ++i)
            {
                cout << i << ". " << graph.getNodeName(i) << endl;
            }

            int start, end;
            cout << "Enter starting location (0-" << NUM_NODES - 1 << "): ";
            cin >> start;
            cout << "Enter destination (0-" << NUM_NODES - 1 << "): ";
            cin >> end;

            if (start >= 0 && start < NUM_NODES && end >= 0 && end < NUM_NODES)
            {
                vector<int> path = optimizer.findShortestPath(start, end);
                optimizer.printRoute(path);
            }
            else
            {
                cout << "Invalid location IDs!" << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
