//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_NODE_H
#define ASG2_NODE_H

#include <vector>
using namespace std;
/*declare goal state global as to be accesible to everyone*/
vector<vector<char> > goalStatePegs(9,vector<char>(9));
vector<int> goalStateMCP(3);

class Node {
    /*prev next */
public:
    Node *prev = NULL;
    int pathcode = 0;
    int HeuristicValue =0; /*based on the total number of moves possible in a given state*/

    virtual bool equals(Node* node)=0;
    virtual void printState()=0;
    virtual bool goalStateTest()=0;
    virtual vector<Node*> successorFunction()=0;
    virtual int stepCost(int move)=0;
};

#endif //ASG2_NODE_H
