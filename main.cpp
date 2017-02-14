#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>


#include "Node.h"
#include "PegsLogicNode.h"
#include "SearchEngine.h"
#include "MCPNode.h"

#define VERBOSE 1

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4){
        cout << "one of the args is missing" << endl;
        return 0;

    }

    //char initialStatePegs4[7][7];
    vector<vector<char> > initialStatePegs(9,vector<char>(9));
    vector<int> initialStateMCP(3);



    string problem;
    string strategy;
    int pegs_shape;
    int n_nodes_to_expand = 0;
    int depth_cutoff = 0;
    int size = 0;
    NodeMCP initialNodeMCP;


    cout << endl << endl<< endl << endl << "--------------------------------------------" << endl << endl << "    START OF SEARCH"<< endl;
    SearchEngine search;
    clock_t begin = clock();



    /*inputting the problemSpec*/
    ifstream problemSpecification("TextFiles/" + string(argv[1]) + ".txt");

    if (!problemSpecification.is_open()) cout << "problem specification file not open" << endl;
    getline(problemSpecification, strategy);

    problemSpecification >> depth_cutoff;
    problemSpecification >> n_nodes_to_expand;

    getline(problemSpecification, problem);
    getline(problemSpecification, problem);
    if (problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;


    if (VERBOSE) {
        cout << "Problem " << problem << endl;
        cout << "strategy " << strategy << endl;
        if (problem == "Pegs") cout << "pegs_shape " << pegs_shape << endl;
        cout << "depth_costoff " << depth_cutoff << endl;
        cout << "n_nodes_to_expand " << n_nodes_to_expand << endl;
    }
    problemSpecification.close();
    /*end of inputting the problemSpec file*/


    /*inputting the initial state and the goal state at the same time*/
    ifstream initialStateStream("TextFiles/" + string(argv[2]) + ".txt");
    if (!initialStateStream.is_open()) {
        cout << "could not open initial state file";
        return 0;
    }

    ifstream goalStateStream("TextFiles/" + string(argv[3]) + ".txt"); //GoalStatePegs4.txt
    if (!goalStateStream.is_open()) {
        cout << "could not open goal state file";
        return 0;
    }



    if (problem == "Pegs") {
        if(pegs_shape == 4 || pegs_shape == 1) size = 7;
        else if(pegs_shape == 2 || pegs_shape == 5) size = 9;
        else if(pegs_shape == 3) size = 8;
        else if(pegs_shape == 6) size = 5;
        /*inputting the initialstate*/

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
                goalStateStream >> goalStatePegs[i][j];
                initialStateStream >> initialStatePegs[i][j];


            }

        initialStateStream.close();
        goalStateStream.close();

        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs" << endl;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cout << initialStatePegs[i][j] << " ";

                }
                cout << endl;
            }
            cout << "Content of the goalState pegs" << endl;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cout << goalStatePegs[i][j] << " ";

                }
                cout << endl;
            }

        }
        // END OF VERBOSE

        /*triangular shape*/
        if(pegs_shape == 6){
            PegsTriangleNode initialPegsTriangleNode = PegsTriangleNode(size,initialStatePegs);
            if(strategy == "DFS")search.DFS(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "A*")search.AStar(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "BFS")search.BFS(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "UCS")search.UCS(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "GBFS")search.Greedy(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "IDS")search.IDS(&initialPegsTriangleNode, n_nodes_to_expand);
            else if(strategy == "DLS")search.DLS(&initialPegsTriangleNode, n_nodes_to_expand,depth_cutoff);

        }
        else{
            NodePegs initialNodePegs;
            initialNodePegs = NodePegs(size,initialStatePegs);
            if(strategy == "DFS")search.DFS(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "A*")search.AStar(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "BFS")search.BFS(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "UCS")search.UCS(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "GBFS")search.Greedy(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "IDS")search.IDS(&initialNodePegs, n_nodes_to_expand);
            else if(strategy == "DLS")search.DLS(&initialNodePegs, n_nodes_to_expand,depth_cutoff);
        }

    }
        // TODO make sure that M>C
    else if(problem == "MCP"){
        for (int i = 0; i < 3; ++i){
            initialStateStream >> problemSpecMCP[i];
            goalStateStream >> goalStateMCP[i];
        }
        if(problemSpecMCP[1] > problemSpecMCP[0]){
            cout << "Initial number of Missionaries : "<< problemSpecMCP[0]
                 << " cannot be less than the initial number of Cannibals: "
                 << problemSpecMCP[1] << endl;
            cout << "Please choose another problem specifiaction file." << endl;
            return 0;
        }

        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs" << endl;
            for (int i = 0; i < 3; ++i)
                cout << problemSpecMCP[i] << " ";
            cout << endl;

            cout << "Content of the goalState pegs" << endl;
            for (int i = 0; i < 3; ++i)
                cout << goalStateMCP[i] << " ";
            cout << endl;
        }
        // END OF VERBOSE

        initialStateStream.close();
        goalStateStream.close();
        initialStateMCP = problemSpecMCP;
        initialStateMCP[2] = 1;
        initialNodeMCP = NodeMCP(initialStateMCP);
        if(strategy == "DFS")search.DFS(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "A*")search.AStar(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "BFS")search.BFS(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "UCS")search.UCS(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "GBFS")search.Greedy(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "IDS")search.IDS(&initialNodeMCP, n_nodes_to_expand);
        else if(strategy == "DLS")search.DLS(&initialNodeMCP, n_nodes_to_expand,depth_cutoff);
    }


    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "the elapsed time to solve the problem is: " << elapsed_secs << " seconds" << endl;

    return 0;
}