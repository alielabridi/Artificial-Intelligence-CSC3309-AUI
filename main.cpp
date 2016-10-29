#include <iostream>
#include <fstream>
#include <string>

#define VERBOSE 1

using namespace std;
int main(int argc, char *argv[]){
    if(argc != 5)
        return 0;

    /*inputting the problemSpec*/
    /* Problem Specification File content
     * 1. problem
     * 2. strategy used
     * 3. modification (1-6 pegs board) or (#M #C #P)
     * 4. #of node to extend before asking if to continue
     * 5. depth cutoff
     */
    ifstream problemSpecification(argv[1]); //problemSpec.txt

    string problem;
    string strategy;
    int pegs_shape;
    int n_missionaries;
    int n_cannibals;
    int n_people;
    int n_nodes_to_expand;
    int depth_cutoff = 0;

    if (!problemSpecification.is_open()) cout << "problem specification file not open" << endl;

    getline(problemSpecification, problem);
    getline(problemSpecification,strategy);

    if(problem == "Pegs")//for the pegs
        problemSpecification >> pegs_shape;

        //MCP
    else if(problem == "MCP"){
        problemSpecification >> n_missionaries;
        problemSpecification >> n_cannibals;
        problemSpecification >> n_people;
    }
    problemSpecification >> n_nodes_to_expand;

    //look for the depth cutoff in case of IDA DLS IDS
    if(strategy == "IDS " || strategy == "IDA" || strategy == "DLS")
        problemSpecification >> depth_cutoff;

    if(VERBOSE){
        cout << "Problem " << problem  << endl;
        cout << "strategy " << strategy  << endl;
        cout << "pegs_shape " << pegs_shape  << endl;
        cout << "n_missionaries " << n_missionaries  << endl;
        cout << "n_cannibals " << n_cannibals  << endl;
        cout << "n_people " << n_people  << endl;
        cout << "depth_costoff " << depth_cutoff  << endl;
    }
    problemSpecification.close();
    /*end of inputting the problemSpec file*/




/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}