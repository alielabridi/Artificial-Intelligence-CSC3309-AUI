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
        /*min heap*/
        return (lhs->HeuristicValue > rhs->HeuristicValue);
    }
};
struct UCSComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        /*min heap*/
        return (lhs->pathcost > rhs->pathcost);
    }
};
struct AStarComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        /*min heap*/
        return ((lhs->HeuristicValue+lhs->pathcost) > (rhs->HeuristicValue+rhs->pathcost));
    }
};


class SearchEngine {
public:
    void BFS(Node* initialState,int n_nodes_to_expand_to_ask) {

        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }


        queue <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSet;
        int n_expension = 0;
        int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }

            node = frontier.front();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set*//*
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }
            }
            cout << "the children of the node expanded - END" << endl;


        }
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }

    void UCS(Node* initialState,int n_nodes_to_expand_to_ask) {

        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }


        priority_queue<Node*, vector<Node*>,UCSComparator> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSet;
        int n_expension = 0;
        int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }

            node = frontier.top();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected  << "and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set*//*
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }
            }
            cout << "the children of the node expanded - END" << endl;


        }
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }

    void DFS(Node* initialState,int n_nodes_to_expand_to_ask) {
        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }
        stack <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSet;
        int n_expension = 0;
        int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }
            node = frontier.top();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;

            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }
            frontier.pop();
            exploredSet.add(node);
            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                /*check that the sucessor is not in the frontier and explored set*/
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }

            }

            cout << "the children of the node expanded - END" << endl;

        }
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
    
        return;
    }




void Greedy(Node* initialState,int n_nodes_to_expand_to_ask) {

    if (initialState->goalStateTest()) {
        cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
        cout << "A solution found has been found" << endl;
        initialState->printSolution();
        return;
    }

    priority_queue<Node*, vector<Node*>,GreedyComparator> frontier;
    Node* node;
    frontier.push(initialState);
    ExploredSet exploredSet;
    int n_expension = 0;
    int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }    

            node = frontier.top();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;                
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            cout << "the children of the expended node( size: "<< successors.size() << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }
            }
            cout << "the children of the node expanded - END" << endl;


        }
        cout << "failure to find the solution" << endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;

            return;
    }


    void AStar(Node* initialState, int n_nodes_to_expand_to_ask) {
        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }
        priority_queue<Node*, vector<Node*>,AStarComparator> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSet;
        int n_expension = 0;
        int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }
            node = frontier.top();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }
            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }
            }
            cout << "the children of the node expanded - END" << endl;
        }
        cout << "failure to find the solution" << endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }

    /*extra credit search*/
    /*DLS definition with its global vars*/
    int n_expansion_DLS = 0;
    int loops_detected_DLS = 0;
    ExploredSet exploredSetDLS;
    void IDS(Node* initialState, int n_nodes_to_expand_to_ask){
        int MAX_depth = 10000;
        Node* nodeFound;
        for (int i = 0; i < MAX_depth ; ++i) {
            exploredSetDLS.clear();
            nodeFound = DLSrecursive(initialState, n_nodes_to_expand_to_ask, i);
            if(nodeFound != NULL){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expansion_DLS << "and the # of loops detected is " << loops_detected_DLS << " and the pathcost to solution " << nodeFound->pathcost << endl;
                nodeFound->printSolution();
                return;
            }
        }
        cout << "failure to find the solution" << endl;
        cout << "The number of nodes expanded is " << n_expansion_DLS << "and the # of loops detected is " << loops_detected_DLS << endl;
        return;
    }
    void DLS(Node* initialState, int n_nodes_to_expand_to_ask, int depth_cutoff){
        Node* nodeFound = DLSrecursive(initialState, n_nodes_to_expand_to_ask, depth_cutoff);
        if(nodeFound == NULL){
            cout << "failure to find the solution" << endl;
            cout << "The number of nodes expanded is " << n_expansion_DLS << "and the # of loops detected is " << loops_detected_DLS << endl;
        }
        else{
            cout << "A solution found has been found" << endl;
            cout << "The number of nodes expanded is " << n_expansion_DLS << "and the # of loops detected is " << loops_detected_DLS << " and the pathcost to solution " << nodeFound->pathcost << endl;
            nodeFound->printSolution();
        }

    }
    Node* DLSrecursive(Node* currentState, int n_nodes_to_expand_to_ask, int depth_cutoff){
        if(currentState->goalStateTest())
            return currentState;
        if(depth_cutoff == 0)
            return NULL;
        if(n_nodes_to_expand_to_ask != 0 && n_expansion_DLS != 0 && n_expansion_DLS % n_nodes_to_expand_to_ask == 0){
            int i;
            cout << "The number of nodes expanded is " << n_expansion_DLS << "and the # of loops detected is " << loops_detected_DLS <<"at depth " << depth_cutoff << endl;
            cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
            cin >> i;
            if(i == 0){
                cout << "The search has ended!" << endl;
                return NULL;
            }
        }
        if(depth_cutoff > 0){
            cout << endl << "the new expanded node # " << ++n_expansion_DLS << endl;
            exploredSetDLS.add(currentState);
            currentState->printState();
            cout << endl << "end - the new expanded node # " << n_expansion_DLS << endl;

            vector <Node*> successors(currentState->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expansion_DLS << "at depth " << depth_cutoff << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
                if(!exploredSetDLS.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    Node* nodeFound = DLSrecursive(successor,n_nodes_to_expand_to_ask, depth_cutoff-1);
                    if(nodeFound != NULL)
                        return nodeFound;
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected_DLS++;
                }
            }
            cout << "the children of the node expanded - END" << endl;
            
        }
        return NULL;
    }

};

#endif //ASG2_SEARCHENGINE_H
