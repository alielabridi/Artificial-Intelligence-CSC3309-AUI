#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc != 4)
        return 0;

    /* Problem Specification File content
     * 1. problem
     * 2. strategy used
     * 3. modification (1-6 pegs board) or (#M #S #P)
     * 4. #of node to extend before asking if to continue
     */
    ifstream problemSpecification (argv[0]+".txt"); //problemSpec.txt
    ifstream heuristicFile (argv[1]+".txt"); //heuristic.txt
    ifstream goalStateFile (argv[2]+".txt"); // goalState.txt
    ifstream initialStateFile (argv[3]+".txt"); //initialState.txt


    problemSpecification.close();
    heuristicFile.close();
    goalStateFile.close();
    heuristicFile.close();
    return 0;
}