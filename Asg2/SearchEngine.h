//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_SEARCHENGINE_H
#define ASG2_SEARCHENGINE_H

#include <iostream>
#include <queue>
#include <stack>
#include "ExploredSet.h"
#include "Node.h"

class SearchEngine {
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
            /*cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;*/
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
        int n_expension = 0;
        while (!frontier.empty()) {
            node = frontier.top();
            /*cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;*/
            if(node->goalStateTest()){
                cout << "solution found" << endl;
                goto solution;
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
        solution:
        int steps = 0;
        while(node != NULL){
            node->printState();
            node = node->prev;
            steps++;
        }
        cout << "the steps are " << steps << endl;
        return;
    }


};

#endif //ASG2_SEARCHENGINE_H
