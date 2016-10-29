#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char *argv[]){
    if(argc != 5)
        return 0;

    /* Problem Specification File content
     * 1. problem
     * 2. strategy used
     * 3. modification (1-6 pegs board) or (#M #C #P)
     * 4. #of node to extend before asking if to continue
     */
    ifstream problemSpecification(argv[1]); //problemSpec.txt
/*    ifstream heuristicFile(argv[1]); //heuristic.txt
    ifstream goalStateFile(argv[2]); // goalState.txt
    ifstream initialStateFile(argv[3]); //initialState.txt*/

    /*inputting the problemSpec*/
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

    problemSpecification.close();
    /*end of inputting the problemSpec file*/

    cout << "+" << problem << "+" << endl;
    cout << "+" << strategy << "+" << endl;
    cout << "+" << pegs_shape << "+" << endl;
    cout << "+" << n_nodes_to_expand << "+" << endl;

/*    initialStateFile.close();
    goalStateFile.close();
    heuristicFile.close();*/
    return 0;
}