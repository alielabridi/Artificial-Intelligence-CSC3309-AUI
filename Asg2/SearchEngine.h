//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_SEARCHENGINE_H
#define ASG2_SEARCHENGINE_H

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "ExploredSet.h"
#include "Node.h"

struct GreedyComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        return (lhs->HeuristicValue < rhs->HeuristicValue);
    }
};
struct AStarComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        return ((lhs->HeuristicValue+lhs->pathcode) < (rhs->HeuristicValue+rhs->pathcode));
    }
};


class SearchEngine {
public:
    /*void BFS(Node* initialState) {

        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }


        queue <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;*//*to be later transofrmed to a hashtable*//*
        int n_expension = 0;
        while (!frontier.empty()) {


            node = frontier.front();
            *//*cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;*//*
            if(node->goalStateTest()){
                cout << "solution found"<< n_expension << endl;
                return;
            }
            cout << "it went here1 " << endl;

            frontier.pop();
            exploredSetBFS.add(node);
            cout << "it went here2" << endl;

            vector <Node*> successors(node->successorFunction());
            //cout << endl << "THE CHILDREN NODE" << endl;
            for (Node* successor: successors) {
                *//*check that the sucessor is not in the frontier and explored set*//*
                if(!exploredSetBFS.exists(successor)){
                    frontier.push(successor);
                    //successor->printState();
                }
                cout << "it went here3 " << endl;
            }
            //cout << "THE CHILDREN NODE -- END" << endl;


        }
        cout << "failure to find the solution"<< n_expension << endl;
        return;
    }*/


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
            cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;

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
        cout << "path cost to reach solution " << node->pathcode << endl;
        while(node != NULL){
            node->printState();
            node = node->prev;
            steps++;
        }
        cout << "the steps are " << steps << endl;
        return;
    }




    void Greedy(Node* initialState) {

    if (initialState->goalStateTest()) {
        cout << "solution found";
        return;
    }

    priority_queue<Node*, vector<Node*>,GreedyComparator> frontier;
    Node* node;
    frontier.push(initialState);
    ExploredSet exploredSetBFS;
        int n_expension = 0;
        while (!frontier.empty()) {


            node = frontier.top();
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
                //check that the sucessor is not in the frontier and explored set
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


    void AStar(Node* initialState) {

        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }

        priority_queue<Node*, vector<Node*>,AStarComparator> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;
        int n_expension = 0;
        while (!frontier.empty()) {


            node = frontier.top();
            cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;
            if(node->goalStateTest()){
                return;
            }
            frontier.pop();
            exploredSetBFS.add(node);

            vector <Node*> successors(node->successorFunction());
            //cout << endl << "THE CHILDREN NODE" << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
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


};

#endif //ASG2_SEARCHENGINE_H
