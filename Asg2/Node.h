//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_NODE_H
#define ASG2_NODE_H

#include <vector>
using namespace std;
/*declare goal state global as to be accesible to everyone*/
vector<vector<char> > goalStatePegs4(7,vector<char>(7));
class Node {
    /*prev next */
public:
    Node *prev;
    virtual bool equals(Node* node)=0;
    virtual void printState()=0;
    virtual int getSize()=0;
    virtual bool goalStateTest()=0;
    virtual vector<Node*> successorFunction()=0;
    virtual char getValueState(int i, int j)=0;
};

#endif //ASG2_NODE_H
