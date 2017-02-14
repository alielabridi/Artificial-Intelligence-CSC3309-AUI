//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_NODE_H
#define ASG2_NODE_H

#include <vector>
#include <stack>
using namespace std;

/*declare goal state global as to be accesible to everyone*/
vector<vector<char> > goalStatePegs(9,vector<char>(9));
vector<int> goalStateMCP(3);
vector<int> problemSpecMCP(3);


class Node {
    /*prev next */
public:
    Node *prev = NULL;
    int pathcost = 0;
    int HeuristicValue =0; /*based on the total number of moves possible in a given state*/

    virtual bool equals(Node* node)=0;
    virtual void printState()=0;
    virtual bool goalStateTest()=0;
    virtual vector<Node*> successorFunction()=0;
    virtual int stepCost(int move)=0;

    void printSolution(){
        /*printing in reverse order to go from initial state to goal state*/
        stack <Node*> reversePrinting;
        Node *tempAddress = this;
        while(tempAddress != NULL){
            reversePrinting.push(tempAddress);
            tempAddress = tempAddress->prev;
        }
        cout << "the solution is: "<<endl;
        int count = reversePrinting.size();
        for (int i = 0; i < count; ++i) {
            reversePrinting.top()->printState();
            reversePrinting.pop();
        }
    }

};

#endif //ASG2_NODE_H
