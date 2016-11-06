//
// Created by Brandon on 11/4/2016.
//

#ifndef ASG2_MCPNODE_H
#define ASG2_MCPNODE_H

#include <iostream>
#include <vector>
#include <functional>	// for plus
#include <algorithm> // for transform
#include "Node.h"
using namespace std;

class NodeMCP : public Node {
public:
    /*  Represents the number of M & C NOT on the GOAL side of the river
        and what side the boat is on. state[2] = 1 means the boat is 
        on the wrong side. */
    vector<int> state;

    vector<int> travelOption1 = {2,0,1};
    vector<int> travelOption2 = {0,2,1};
    vector<int> travelOption3 = {1,1,1};
    vector<int> travelOption4 = {1,0,1};
    vector<int> travelOption5 = {0,1,1};


    int stepCost(int move){
        return 0;
    }
    vector<vector<int> > listOfTravelOptions = 
    {travelOption1, travelOption2, travelOption3, travelOption4, travelOption5};

    NodeMCP(){};

    NodeMCP(vector<int> state_):state(state_){};


    bool equals (Node* node){
			return (state == dynamic_cast<NodeMCP*>(node)->state);
    }

    void printState(){
        cout << "State: < ";
        for (int i = 0; i < state.size(); i++)
    		cout << state[i] << ",";
        cout << ">" << endl;
    }

    bool goalStateTest (){  // could be pretty wrong. Idk where we are storing the goal state 
        for (int i = 0; i < 3; i++)
            if (state[i] != goalStateMCP[i])
                return false;
        return true;
    }

    vector <Node* > successorFunction(){
        vector <Node* > successorSet;
        /*  Test which side boat (state[2]) is on
            then either add or subtract 
            (<1,0,1>, <2,0,1>, <0,1,1>, <0,2,1>, and <1,1,1>)
            then test if it is a valid move
            if it is, add new node to successor set*/

        // Boat is on the goal side of the river
        if(state[2] == 0)
        {
        	// Next states will be generated from vector addition
        	// Move boat, n missionaries, and n cannibal to the non goal side of river
        	
        	for (int i = 0; i < listOfTravelOptions.size(); i++)
        	{
        		vector<int> temp;
        		// Vector addition - add a travel option to the current state
				transform(state.begin(), state.end(),
        			listOfTravelOptions[i].begin(), back_inserter(temp), plus<int>());
				
        		// Check to see if the option was valid
        		for (int j = 0; j < state.size(); j++)
        		{
                    /*change 3 by goal state*/
                    if(j < 2 && temp[j] <= 3) {
                        // Add temp to the list of
                        NodeMCP* newNode = new NodeMCP(temp);
                        newNode->prev = this;
                        successorSet.push_back(newNode);
                    }

        		}
        	}
        }
        // Boat is on the goal side of the river
        else if(state[2] == 1)
        {
        	// Next states will be generated by vector subtraction
        	for (int i = 0; i < listOfTravelOptions.size(); i++)
            {
                vector<int> temp;
                // Vector subtraction - subtract a travel option to the current state
                transform(state.begin(), state.end(),
                    listOfTravelOptions[i].begin(), back_inserter(temp), minus<int>());
                
                // Check to see if the option was valid
                for (int j = 0; j < state.size(); j++)
                {
                    if(j < 2 && temp[j] >= 0)
                    {
                        // Add temp to the list of
                        NodeMCP* newNode = new NodeMCP(temp);
                        newNode->prev = this;
                        successorSet.push_back(newNode);

                    }
                }
            }
        }
        return successorSet;

    }
};

#endif // ASG2_MCPNODE_H