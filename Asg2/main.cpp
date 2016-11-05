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
    if (argc != 5){
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
    int size;
    NodePegs initialNodePegs;
    NodeMCP initialNodeMCP;


    cout << endl << endl<< endl << endl << "--------------------------------------------" << endl << endl << "    START OF SEARCH"<< endl;
    SearchEngine search;
    clock_t begin = clock();



    /*inputting the problemSpec*/
    ifstream problemSpecification("TextFiles/" + string(argv[1]) + ".txt");

    if (!problemSpecification.is_open()) cout << "problem specification file not open" << endl;
    getline(problemSpecification, strategy);
    problemSpecification >> n_nodes_to_expand;
    problemSpecification >> depth_cutoff;
    getline(problemSpecification, problem);
    if (problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;



    if (VERBOSE) {
        cout << "Problem " << problem << endl;
        cout << "strategy " << strategy << endl;
        if (problem == "Pegs") cout << "pegs_shape " << pegs_shape << endl;
        cout << "depth_costoff " << depth_cutoff << endl;
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
        if(pegs_shape == 4) size = 7;
        /*inputting the initialstate*/

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
                goalStateStream >> goalStatePegs[i][j];
                initialStateStream >> initialStatePegs[i][j];


            }

        initialStateStream.close();
        goalStateStream.close();

        initialNodePegs = NodePegs(size,initialStatePegs);
        search.DFS(&initialNodePegs);


        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs" << endl;
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    cout << initialStatePegs[i][j] << " ";

                }
                cout << endl;
            }
            cout << "Content of the goalState pegs" << endl;
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    cout << goalStatePegs[i][j] << " ";

                }
                cout << endl;
            }

        }
        // END OF VERBOSE

    }
    else if(problem == "MCP"){
        for (int i = 0; i < 3; ++i){
            initialStateStream >> initialStateMCP[i];
            goalStateStream >> goalStateMCP[i];
        }
        initialStateStream.close();
        goalStateStream.close();
        initialNodeMCP = NodeMCP(initialStateMCP);
        search.DFS(&initialNodeMCP);

        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs" << endl;
            for (int i = 0; i < 3; ++i) {
                    cout << initialStateMCP[i] << " ";
                cout << endl;
            }
            cout << "Content of the goalState pegs" << endl;
            for (int i = 0; i < 3; ++i) {
                    cout << goalStateMCP[i] << " ";
                cout << endl;
            }

        }
        // END OF VERBOSE

    }

    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "the elapsed time to solve the problem is: " << elapsed_secs << " seconds" << endl;



/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}