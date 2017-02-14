//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_EXPLOREDSET_H
#define ASG2_EXPLOREDSET_H

#include "Node.h"
class ExploredSet{
public:
    vector<Node *> Vec;

    void add(Node * node){
        Vec.push_back(node);
    }
    bool exists(Node * node){
        for(Node * V : Vec){
            if(V->equals(node))
                return true;
        }
        return false;
    }
    int size(){
        return Vec.size();
    }
    void clear(){
        Vec.clear();
    }
};

#endif //ASG2_EXPLOREDSET_H
