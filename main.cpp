#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#define VERBOSE 1

using namespace std;
/*declare goal state global as to be accesible to everyone*/
char goalStatePegs4[7][7];
class Node{
    /*prev next */
public:
    Node* prev;
};
/*Node object representation*/
class NodePegs4: public Node{
public:
    char state[7][7];
    NodePegs4(){};
    NodePegs4(char state_[7][7]){
        /*copy matrix*/
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                state[i][j] = state_[i][j];
            }
        }
    }

    void printState(){
        cout << "---------START--------" << endl;
        for (int i = 0; i < 7 ; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                cout << state[i][j] << " ";

            }
            cout << endl;
        }
        cout << "---------FINISH--------" << endl;

    }

    bool goalStateTest(){
        for (int i = 0; i < 7 ; ++i) {
            for (int j = 0; j < 7; ++j) {
                if(goalStatePegs4[i][j] != state[i][j])
                    return false;
            }
        }
        return true;
    }
    vector<NodePegs4> successorFunction(){
        vector<NodePegs4> successorSet;
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                if( state[i][j] == '0' ){
                    /*check possibility to move blank up*/
                    if((i - 2 >= 0) && state[i-1][j] == '1' && state[i-2][j] == '1'  ){
                        NodePegs4 nodeUp(state);
                        nodeUp.state[i-1][j] = '0';
                        nodeUp.state[i-2][j] = '0';
                        nodeUp.state[i][j] = '1';
                        nodeUp.prev = this;
                        successorSet.push_back(nodeUp);
                    }
                    /*check possibility to move blank down*/
                    if((i + 2 <= 7) && state[i+1][j] == '1' && state[i+2][j] == '1'  ){
                        NodePegs4 nodeDown(state);
                        nodeDown.state[i+1][j] = '0';
                        nodeDown.state[i+2][j] = '0';
                        nodeDown.state[i][j] = '1';
                        nodeDown.prev = this;
                        successorSet.push_back(nodeDown);
                    }
                    /*check possibility to move blank right*/
                    if((j + 2 <= 7) && state[i][j+1] == '1' && state[i][j+2] == '1'  ){
                        NodePegs4 nodeRight(state);
                        nodeRight.state[i][j+1] = '0';
                        nodeRight.state[i][j+2] = '0';
                        nodeRight.state[i][j] = '1';
                        nodeRight.prev = this;
                        successorSet.push_back(nodeRight);
                    }
                    /*check possibility to move blank left*/
                    if((j - 2 <= 7) && state[i][j-1] == '1' && state[i][j-2] == '1'  ){
                        NodePegs4 nodeLeft(state);
                        nodeLeft.state[i][j-1] = '0';
                        nodeLeft.state[i][j-2] = '0';
                        nodeLeft.state[i][j] = '1';
                        nodeLeft.prev = this;
                        successorSet.push_back(nodeLeft);
                    }
                }

            }
        }

        return successorSet;
    }

};

class searchEngine{
public:
    void BST(NodePegs4 initialState){
        if(initialState.goalStateTest()){
            cout << "solution found";
            return;
        }
        queue<NodePegs4> frontier;
        frontier.push(initialState);
        vector<NodePegs4> explored;/*to be later transofrmed to a hashtable*/
        while (!frontier.empty()){
            NodePegs4 node = frontier.back();
            frontier.pop();
            explored.push_back(node);
            vector<NodePegs4> successors(node.successorFunction());
            for(NodePegs4 successor: successors){
                /*check that the sucessor is not in the frontier and explored set*/
                successor.printState();
                if(successor.goalStateTest()) {
                    cout << "found solution 1";
                    return;
                }
                vector<NodePegs4> children (successor.successorFunction());
                for(NodePegs4 child: children)
                    frontier.push(child);
                }

            }
        cout << "failure";
        return;
        }
};

int main(int argc, char *argv[]){
    if(argc != 5)
        return 0;

    char initialStatePegs4[7][7];


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
    ifstream problemSpecification("TextFiles/"+string(argv[1])+".txt"); //problemSpec.txt

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
        ifstream initialStateStream("TextFiles/"+string(argv[2])+".txt"); //InitialStatePegs4.txt
        if(!initialStateStream.is_open()){cout << "could not open initial state file"; return 0;}
        for (int i = 0; i < 7 ; ++i) {
            for (int j = 0; j < 7 ; ++j) {
                initialStateStream >> initialStatePegs4[i][j];

            }
        }
        initialStateStream.close();

        /*inputting the goal state*/
        ifstream goalStateStream("TextFiles/"+string(argv[3])+".txt"); //GoalStatePegs4.txt
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

    searchEngine search;
    NodePegs4 initialNode(initialStatePegs4);
    search.BST(initialNode);



/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}