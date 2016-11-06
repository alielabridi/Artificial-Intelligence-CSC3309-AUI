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

    vector<vector<char>> state;
    int size;

    NodePegs() {};

    NodePegs(int size,vector<vector<char> > state_):state(size, std::vector<char>(size)) {
        this->size = size;
        /*copy matrix*/
        state = state_;
        HeuristicValue = totalPossibleMovesHeuristic();
    }




    int totalPossibleMovesHeuristic(){
        int count = 0;
        for (int i = 0; i < size ; ++i) {
            for (int j = 0; j < size ; ++j) {
                if (state[i][j] == '1') {

                    /*check possibility to move blank down*/
                    if ((i + 2 < size) && state[i + 1][j] == '1' && state[i + 2][j] == '0') {
                        count++;
                    }

                    /*check possibility to move blank right*/
                    if ((j + 2 < size) && state[i][j + 1] == '1' && state[i][j + 2] == '0') {
                        count++;
                    }
                    /*check possibility to move blank left*/
                    if ((j - 2 >= 0) && state[i][j - 1] == '1' && state[i][j - 2] == '0') {
                        count++;
                    }
                    /*check possibility to move blank up*/
                    if ((i - 2 >= 0) && state[i - 1][j] == '1' && state[i - 2][j] == '0') {
                        count++;
                    }

                }
            }
        }
        return count;

    }

    int stepCost(int move){
        /*returns the step cost for every move
         * 1 => down
         * 2 =>right
         * 2 => left
         * 3 => up
         * */
        switch(move){
            case 1:
                return 1;
            case 2:
                return 1;
            case 3:
                return 1;
            case 4:
                return 1;
            default:
                return 0;
        }
    }

    bool equals(Node* node){
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (dynamic_cast<NodePegs *>(node)->state[i][j] != state[i][j])
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
                if (goalStatePegs[i][j] != state[i][j])
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
                        nodeDown->pathcode = pathcode + stepCost(1);
                        successorSet.push_back(nodeDown);
                    }

                    /*check possibility to move blank right*/
                    if ((j + 2 < size) && state[i][j + 1] == '1' && state[i][j + 2] == '1') {
                        NodePegs* nodeRight = new NodePegs(size,state);
                        nodeRight->state[i][j + 1] = '0';
                        nodeRight->state[i][j + 2] = '0';
                        nodeRight->state[i][j] = '1';
                        nodeRight->prev = this;
                        nodeRight->pathcode = pathcode + stepCost(2);
                        successorSet.push_back(nodeRight);
                    }
                    /*check possibility to move blank left*/
                    if ((j - 2 >= 0) && state[i][j - 1] == '1' && state[i][j - 2] == '1') {
                        NodePegs* nodeLeft = new NodePegs(size,state);
                        nodeLeft->state[i][j - 1] = '0';
                        nodeLeft->state[i][j - 2] = '0';
                        nodeLeft->state[i][j] = '1';
                        nodeLeft->prev = this;
                        nodeLeft->pathcode = pathcode +  stepCost(3);
                        successorSet.push_back(nodeLeft);
                    }
                    /*check possibility to move blank up*/
                    if ((i - 2 >= 0) && state[i - 1][j] == '1' && state[i - 2][j] == '1') {
                        NodePegs* nodeUp = new NodePegs(size,state);
                        nodeUp->state[i - 1][j] = '0';
                        nodeUp->state[i - 2][j] = '0';
                        nodeUp->state[i][j] = '1';
                        nodeUp->prev = this;
                        nodeUp->pathcode = pathcode +  stepCost(4);
                        successorSet.push_back(nodeUp);
                    }

                }

            }
        }

        return successorSet;
    }

};

class PegsTriangleNode: public NodePegs{
public:

    PegsTriangleNode(int size, vector< vector<char> > state_):NodePegs(size,state_){};
    PegsTriangleNode(){};
    /*we only need to overload the successor function for the triangle*/
    int stepCost(int move){
        /*returns the step cost for every move
         * 1 => down
         * 2 =>right
         * 3 => left
         * 4 => up
         * 5 => up-right
         * 6=> down-left
         * */
        switch(move){
            case 1:
                return 1;
            case 2:
                return 1;
            case 3:
                return 1;
            case 4:
                return 1;
            case 5:
                return 1;
            case 6:
                return 1;
            default:
                return 0;
        }
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
                        nodeDown->pathcode = pathcode + stepCost(1);
                        successorSet.push_back(nodeDown);
                    }

                    /*check possibility to move blank right*/
                    if ((j + 2 < size) && state[i][j + 1] == '1' && state[i][j + 2] == '1') {
                        NodePegs* nodeRight = new NodePegs(size,state);
                        nodeRight->state[i][j + 1] = '0';
                        nodeRight->state[i][j + 2] = '0';
                        nodeRight->state[i][j] = '1';
                        nodeRight->prev = this;
                        nodeRight->pathcode = pathcode + stepCost(2);
                        successorSet.push_back(nodeRight);
                    }
                    /*check possibility to move blank left*/
                    if ((j - 2 >= 0) && state[i][j - 1] == '1' && state[i][j - 2] == '1') {
                        NodePegs* nodeLeft = new NodePegs(size,state);
                        nodeLeft->state[i][j - 1] = '0';
                        nodeLeft->state[i][j - 2] = '0';
                        nodeLeft->state[i][j] = '1';
                        nodeLeft->prev = this;
                        nodeLeft->pathcode = pathcode +  stepCost(3);
                        successorSet.push_back(nodeLeft);
                    }
                    /*check possibility to move blank up*/
                    if ((i - 2 >= 0) && state[i - 1][j] == '1' && state[i - 2][j] == '1') {
                        NodePegs* nodeUp = new NodePegs(size,state);
                        nodeUp->state[i - 1][j] = '0';
                        nodeUp->state[i - 2][j] = '0';
                        nodeUp->state[i][j] = '1';
                        nodeUp->prev = this;
                        nodeUp->pathcode = pathcode +  stepCost(4);
                        successorSet.push_back(nodeUp);
                    }
                    /*check the possibility to move blank Up and Right */
                    if ((i - 2 >= 0) && (j + 2 < size) && state[i - 1][j+1] == '1' && state[i - 2][j+2] == '1') {
                        NodePegs* nodeUpRight = new NodePegs(size,state);
                        nodeUpRight->state[i - 1][j+1] = '0';
                        nodeUpRight->state[i - 2][j+2] = '0';
                        nodeUpRight->state[i][j] = '1';
                        nodeUpRight->prev = this;
                        nodeUpRight->pathcode = pathcode +  stepCost(5);
                        successorSet.push_back(nodeUpRight);
                    }
                    /*check the possibility to move blank Down and Left */
                    if ((i + 2 < size) && (j - 2 >= 0) && state[i + 1][j-1] == '1' && state[i + 2][j-2] == '1') {
                        NodePegs* nodeDownLeft = new NodePegs(size,state);
                        nodeDownLeft->state[i + 1][j-1] = '0';
                        nodeDownLeft->state[i + 2][j-2] = '0';
                        nodeDownLeft->state[i][j] = '1';
                        nodeDownLeft->prev = this;
                        nodeDownLeft->pathcode = pathcode + stepCost(6);
                        successorSet.push_back(nodeDownLeft);
                    }
                    /*Down Right and Up Left are not allowed in this puzzle*/

                }

            }
        }

        return successorSet;
    }

};

#endif //ASG2_PEGSLOGICNODE_H
