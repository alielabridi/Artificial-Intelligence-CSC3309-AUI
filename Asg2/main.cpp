#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

#define VERBOSE 1

using namespace std;
/*declare goal state global as to be accesible to everyone*/
vector<vector<char>> goalStatePegs4(7,vector<char>(7));

class Node {
    /*prev next */
public:
    Node *prev;
    virtual bool equals(Node* node)=0;
    virtual void printState()=0;
    virtual bool goalStateTest()=0;
    virtual vector<Node*> successorFunction()=0;
    virtual char getValueState(int i, int j)=0;
};

/*Node object representation*/
class NodePegs : public Node {
public:
    vector<vector<char>> state;
    int size;/*represents the size of the matrix for every pegs game*/

    char getValueState(int i, int j){
        return state[i][j];
    }
    NodePegs() {};

    NodePegs(int size,vector<vector<char>> state_):state(size, std::vector<char>(size)) {
        this->size = size;
        /*copy matrix*/
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                state[i][j] = state_[i][j];
            }
        }
    }

    bool equals(Node* node){
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (node->getValueState(i,j) != state[i][j])
                    return false;
            }
        }
        return true;
    }
    void printState() {
        cout << "---------START--------" << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << state[i][j] << " ";

            }
            cout << endl;
        }
        cout << "---------FINISH--------" << endl;

    }

    bool goalStateTest() {
        /*to be modified for the array goalstate*/
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (goalStatePegs4[i][j] != state[i][j])
                    return false;
            }
        }
        return true;
    }

    vector <Node *> successorFunction() {
        vector <Node*> successorSet;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (state[i][j] == '0') {

                    /*check possibility to move blank down*/
                    if ((i + 2 < size) && state[i + 1][j] == '1' && state[i + 2][j] == '1') {
                        NodePegs* nodeDown = new NodePegs(size,state);
                        nodeDown->state[i + 1][j] = '0';
                        nodeDown->state[i + 2][j] = '0';
                        nodeDown->state[i][j] = '1';
                        nodeDown->prev = this;
                        successorSet.push_back(nodeDown);
                    }

                    /*check possibility to move blank right*/
                    if ((j + 2 < size) && state[i][j + 1] == '1' && state[i][j + 2] == '1') {
                        NodePegs* nodeRight = new NodePegs(size,state);
                        nodeRight->state[i][j + 1] = '0';
                        nodeRight->state[i][j + 2] = '0';
                        nodeRight->state[i][j] = '1';
                        nodeRight->prev = this;
                        successorSet.push_back(nodeRight);
                    }
                    /*check possibility to move blank left*/
                    if ((j - 2 >= 0) && state[i][j - 1] == '1' && state[i][j - 2] == '1') {
                        NodePegs* nodeLeft = new NodePegs(size,state);
                        nodeLeft->state[i][j - 1] = '0';
                        nodeLeft->state[i][j - 2] = '0';
                        nodeLeft->state[i][j] = '1';
                        nodeLeft->prev = this;
                        successorSet.push_back(nodeLeft);
                    }
                    /*check possibility to move blank up*/
                    if ((i - 2 >= 0) && state[i - 1][j] == '1' && state[i - 2][j] == '1') {
                        NodePegs* nodeUp = new NodePegs(size,state);
                        nodeUp->state[i - 1][j] = '0';
                        nodeUp->state[i - 2][j] = '0';
                        nodeUp->state[i][j] = '1';
                        nodeUp->prev = this;
                        successorSet.push_back(nodeUp);
                    }

                }

            }
        }

        return successorSet;
    }

};

class PegsTriangleNode: public NodePegs{
    PegsTriangleNode(int size, vector< vector<char>> state_):NodePegs(size,state_){};
    PegsTriangleNode(){};
    /*we only need to overload the successor function for the triangle*/
};

class ExploredSet{
public:
    vector<Node *> Vec;
    void add(Node * node){Vec.push_back(node);}
    bool exists(Node * node){
        for(Node * V : Vec){
            if(V->equals(node))
                return true;
        }
        return false;
    }
};

class searchEngine {
public:
    void BFS(Node* initialState) {

        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }
        

        queue <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;/*to be later transofrmed to a hashtable*/
        int n_expension = 0;
        while (!frontier.empty()) {
            

            node = frontier.front();
            cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;
            if(node->goalStateTest()){
                cout << "solution found"<< n_expension << endl;
                return;
            }
            frontier.pop();
            exploredSetBFS.add(node);
            vector <Node*> successors(node->successorFunction());
            //cout << endl << "THE CHILDREN NODE" << endl;
            for (Node* successor: successors) {
                /*check that the sucessor is not in the frontier and explored set*/
                if(!exploredSetBFS.exists(successor)){
                    frontier.push(successor);
                    //successor->printState();
                }
            }
            //cout << "THE CHILDREN NODE -- END" << endl;


        }
        cout << "failure to find the solution"<< n_expension << endl;
        return;
    }


    void DFS(Node* initialState) {
        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }
        stack <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;/*to be later transofrmed to a hashtable*/
        while (!frontier.empty()) {
            node = frontier.top();
            node->printState();
            if(node->goalStateTest()){
                cout << "solution found" << endl;
                return;
            }
            frontier.pop();
            exploredSetBFS.add(node);
            vector <Node*> successors(node->successorFunction());
            for (Node* successor: successors) {
                /*check that the sucessor is not in the frontier and explored set*/
                if(!exploredSetBFS.exists(successor))
                    frontier.push(successor);
            }

        }
        cout << "failure to find the solution" << endl;
        return;
    }


};

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


    if (problem == "Pegs" && pegs_shape == 4) {
        /*inputting the initialstate*/
        ifstream initialStateStream("TextFiles/" + string(argv[2]) + ".txt"); //InitialStatePegs4.txt
        if (!initialStateStream.is_open()) {
            cout << "could not open initial state file";
            return 0;
        }
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
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
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                goalStateStream >> goalStatePegs4[i][j];

            }
        }
        goalStateStream.close();

        if (VERBOSE) {
            /*print the content of the goal state and initial state*/
            cout << "Content of the initialState pegs 4" << endl;
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    cout << initialStatePegs4[i][j] << " ";

                }
                cout << endl;
            }
            cout << "Content of the goalState pegs 4" << endl;
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    cout << goalStatePegs4[i][j] << " ";

                }
                cout << endl;
            }

        }

    }


    cout << endl << endl<< endl << endl << "--------------------------------------------" << endl << endl << "    START OF SEARCH"<< endl;
    searchEngine search;
    NodePegs initialNode(7,initialStatePegs4);
    
    search.BFS(&initialNode);



/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}