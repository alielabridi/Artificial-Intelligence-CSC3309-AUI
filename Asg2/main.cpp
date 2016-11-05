#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>


#include "Node.h"
#include "PegsLogicNode.h"
#include "SearchEngine.h"

#define VERBOSE 1

using namespace std;



int main(int argc, char *argv[]) {
    if (argc != 5){
        cout << "one of the args is missing" << endl;
        return 0;

    }

    //char initialStatePegs4[7][7];
    vector<vector<char>> initialStatePegs4(7,vector<char>(7));


    string problem;
    string strategy;
    int pegs_shape;
    int n_missionaries;
    int n_cannibals;
    int boatCapacity;
    int n_nodes_to_expand;
    int depth_cutoff = 0;
    int n_pairs_MCP;

    /*inputting the problemSpec*/
    ifstream problemSpecification("TextFiles/" + string(argv[1]) + ".txt"); //problemSpec.txt

    if (!problemSpecification.is_open()) cout << "problem specification file not open" << endl;

    getline(problemSpecification, problem);
    getline(problemSpecification, strategy);

    problemSpecification >> depth_cutoff;

    if (problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;

        //MCP
    else if (problem == "MCP") {
        problemSpecification >> n_pairs_MCP;
        n_cannibals = n_missionaries = n_pairs_MCP;

        problemSpecification >> boatCapacity;
    }
    problemSpecification >> n_nodes_to_expand;


    if (VERBOSE) {
        cout << "Problem " << problem << endl;
        cout << "strategy " << strategy << endl;
        cout << "pegs_shape " << pegs_shape << endl;
        cout << "n_pairs_MCP " << n_pairs_MCP << endl;
        cout << "n_missionaries " << n_missionaries << endl;
        cout << "n_cannibals " << n_cannibals << endl;
        cout << "boatCapacity " << boatCapacity << endl;
        cout << "depth_costoff " << depth_cutoff << endl;
    }
    problemSpecification.close();
    /*end of inputting the problemSpec file*/


    if (problem == "Pegs" ) {
        int size;
        if(pegs_shape == 5) size = 9;
        else if(pegs_shape == 4) size = 7;
        /*inputting the initialstate*/
        ifstream initialStateStream("TextFiles/" + string(argv[2]) + ".txt"); //InitialStatePegs4.txt
        if (!initialStateStream.is_open()) {
            cout << "could not open initial state file";
            return 0;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                initialStateStream >> initialStatePegs4[i][j];

            }
        }
        initialStateStream.close();

        /*inputting the goal state*/
        ifstream goalStateStream("TextFiles/" + string(argv[3]) + ".txt"); //GoalStatePegs4.txt
        if (!goalStateStream.is_open()) {
            cout << "could not open goal state file";
            return 0;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                goalStateStream >> goalStatePegs4[i][j];

            }
        }
        goalStateStream.close();

        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs 4" << endl;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cout << initialStatePegs4[i][j] << " ";

                }
                cout << endl;
            }
            cout << "Content of the goalState pegs 4" << endl;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cout << goalStatePegs4[i][j] << " ";

                }
                cout << endl;
            }

        }

    cout << endl << endl<< endl << endl << "--------------------------------------------" << endl << endl << "    START OF SEARCH"<< endl;
    SearchEngine search;
    NodePegs initialNode(size,initialStatePegs4);

        clock_t begin = clock();
        search.DFS(&initialNode);

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        cout << "the elapsed time to solve the problem is: " << elapsed_secs << " seconds" << endl;
    }




/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}