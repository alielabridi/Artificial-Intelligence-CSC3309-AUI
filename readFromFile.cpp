#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc != 4)
        return 0;

    /* Problem Specification File content
     * 1. problem
     * 2. strategy used
     * 3. modification (1-6 pegs board) or (#M #C #P)
     * 4. #of node to extend before asking if to continue
     */
    ifstream problemSpecification (argv[0]+".txt"); //problemSpec.txt
    ifstream heuristicFile (argv[1]+".txt"); //heuristic.txt
    ifstream goalStateFile (argv[2]+".txt"); // goalState.txt
    ifstream initialStateFile (argv[3]+".txt"); //initialState.txt


    /*inputting the problemSpec*/
    string problem;
    string strategy;
    int pegs_shape;
    int n_missionaries;
    int n_cannibals;
    int n_people
    int n_nodes_to_expand;
    problemSpecification >> problem;
    problemSpecification >> strategy;
    if(problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;

    //MCP
    else if(problem == "MCP"){
        problemSpecification >> n_missionaries;
        problemSpecification >> n_cannibals;
        problemSpecification >> n_people;
    }
    problemSpecification >> n_nodes_to_expand;

    problemSpecification.close();
    /*end of inputting the problemSpec file*/

    heuristicFile.close();
    goalStateFile.close();
    heuristicFile.close();
    return 0;
}