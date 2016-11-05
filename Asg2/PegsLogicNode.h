//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_PEGSLOGICNODE_H
#define ASG2_PEGSLOGICNODE_H

#include <iostream>
#include "Node.h"
using namespace std;

/*Node object representation*/
class NodePegs : public Node {
public:
    vector<vector<char> > state;
    int size;

    char getValueState(int i, int j){
        return state[i][j];
    }
    int getSize(){return size;}
    
    NodePegs() {};

    NodePegs(int size,vector<vector<char> > state_):state(size, std::vector<char>(size)) {
        this->size = size;
        /*copy matrix*/
        state = state_;
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
    PegsTriangleNode(int size, vector< vector<char> > state_):NodePegs(size,state_){};
    PegsTriangleNode(){};
    /*we only need to overload the successor function for the triangle*/
};
#endif //ASG2_PEGSLOGICNODE_H
