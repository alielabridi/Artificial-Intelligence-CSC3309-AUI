#include <iostream>
#include <fstream>
#include <string>

#define VERBOSE 1

using namespace std;

/*Node object representation*/
class NodePegs4: public Node{
public:
    string problem;
    char state[7][7];

    NodePegs4(string problem_, char state_[7][7]){
        problem = problem_;
        /*copy matrix*/
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                state[i][j] = state_[i][j];
            }
        }
    }


};
class Node{
    /*prev next */
};
int main(int argc, char *argv[]){
    if(argc != 5)
        return 0;

    char initialStatePegs4[7][7];
    char goalStatePegs4[7][7];

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
    ifstream problemSpecification(string(argv[1])+".txt"); //problemSpec.txt

    if (!problemSpecification.is_open()) cout << "problem specification file not open" << endl;

    getline(problemSpecification, problem);
    getline(problemSpecification,strategy);

    problemSpecification >> depth_cutoff;

    if(problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;

        //MCP
    else if(problem == "MCP"){
        problemSpecification >> n_pairs_MCP;
        n_cannibals = n_missionaries = n_pairs_MCP;

        problemSpecification >> boatCapacity;
    }
    problemSpecification >> n_nodes_to_expand;


    if(VERBOSE){
        cout << "Problem " << problem  << endl;
        cout << "strategy " << strategy  << endl;
        cout << "pegs_shape " << pegs_shape  << endl;
        cout << "n_pairs_MCP " << n_pairs_MCP  << endl;
        cout << "n_missionaries " << n_missionaries  << endl;
        cout << "n_cannibals " << n_cannibals  << endl;
        cout << "boatCapacity " << boatCapacity  << endl;
        cout << "depth_costoff " << depth_cutoff  << endl;
    }
    problemSpecification.close();
    /*end of inputting the problemSpec file*/


    if(problem == "Pegs" && pegs_shape == 4){
        /*inputting the initialstate*/
        ifstream initialStateStream(string(argv[2])+".txt"); //InitialStatePegs4.txt
        if(!initialStateStream.is_open()){cout << "could not open initial state file"; return 0;}
        for (int i = 0; i < 7 ; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                initialStateStream >> initialStatePegs4[i][j];

            }
        }
        initialStateStream.close();

        /*inputting the goal state*/
        ifstream goalStateStream(string(argv[3])+".txt"); //GoalStatePegs4.txt
        if(!goalStateStream.is_open()){cout << "could not open goal state file"; return 0;}
        for (int i = 0; i < 7 ; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                goalStateStream >> goalStatePegs4[i][j];

            }
        }
        goalStateStream.close();

        if(VERBOSE){
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs 4" << endl;
            for (int i = 0; i < 7 ; ++i) {
                for (int j = 0; j < 7 ; ++j) {
                    cout << initialStatePegs4[i][j] << " ";

                }
                cout << endl;
            }
            cout << "Content of the goalState pegs 4" << endl;
            for (int i = 0; i < 7 ; ++i) {
                for (int j = 0; j < 7 ; ++j) {
                    cout << goalStatePegs4[i][j] << " ";

                }
                cout << endl;
            }

        }

    }



/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}