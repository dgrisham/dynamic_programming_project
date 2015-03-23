#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct element {
    int distance;
    int parent;
};

void print_dist(vector< vector< element > > mat, int size) {
    for (int i=0; i<size; ++i){
        for (int j=0; j<size; ++j){
            cout << mat[i][j].distance << " ";
        }
        cout << endl;
    }
}

int match(char a, char b) {
    if (a == b)
        return 0;
    return 3;
}

int no_match(char a) {
    return 1;
}

int main(int argc, char** argv) {
    if (!(argc == 2)) {
        cerr << "\nCalled: 'exe_palindrome (string to check)'"
             "\n(e.g. exe_palindrome ACGTCGA \n\n" 
             "This program finds the longest non-contiguous palindrome\n"
             "located in the input string by finding the longest subsequence\n"
             "in the input string and the reversed input string.\n";
         return 1;
    }
    
    // read input string, store reversed version
    char* forwards = argv[1]; 
    char* backwards = new char;
    strcpy(backwards, forwards);
    reverse(backwards, backwards + strlen(backwards));
    cout << "\nInput string: " << forwards << endl;
    cout << "Inverted string: " << backwards << endl;

    int size = strlen(forwards)+1; // plus 1 to account for space before word
    typedef vector<element> mat_rows;
    typedef vector<mat_rows> matrix;
    matrix dist(size, mat_rows(size));

    // initialize rows
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (i==0) {
                dist[i][j].distance = j;
                dist[i][j].parent = 1;
            }
            else if (j==0) {
                dist[i][j].distance = i;
                dist[i][j].parent = 2;
            }
            else
                dist[i][j].distance = 0;
        }
    }
    
    int choice[3]; // 0 is match, 1 is insert, 2 delete
    for (int i=1; i<size; ++i) {
        for (int j=1; j<size; ++j) {
            // here forwards/backwards[i/j - 1] is -1 to accomodate for the
            // space before the string
            choice[0] = dist[i-1][j-1].distance + match(forwards[i-1], backwards[j-1]);
            choice[1] = dist[i][j-1].distance + no_match(forwards[i-1]);
            choice[2] = dist[i-1][j].distance + no_match(backwards[j-1]);
           
            dist[i][j].parent = 0; 
            dist[i][j].distance = choice[0]; 
            for (int k=0; k<3; ++k) {
                if (choice[k] < dist[i][j].distance) {
                    dist[i][j].distance = choice[k];
                    dist[i][j].parent = k;
                }
            }
        }
    }
    cout << endl;

    cout << "table of distances: " << endl;
    print_dist(dist,size);

    // traceback through matrix
    int pos[2]; // temporary position
    pos[0] = size-1;
    pos[1] = size-1;
    string palindrome;

    int prev_move = dist[pos[0]][pos[1]].parent; // next backstep we take


    cout << "\nbacktracing through the matrix: " << endl;
    cout << "(1 moves left, 2 moves up, 0 (match) moves up-left)" << endl;
    while (!(pos[0] <= 1 && pos[1] <= 1)) {
        cout << "move is: " << prev_move << " from location " << pos[0] << " "  
             << pos[1] << endl;
        if (prev_move == 0){
            palindrome.push_back(forwards[pos[0]-1]);
            pos[0] = pos[0] - 1;
            pos[1] = pos[1] - 1;
            prev_move = dist[pos[0]][pos[1]].parent; 
        } else if (prev_move == 1){
            pos[0] = pos[0];
            pos[1] = pos[1] - 1;
            prev_move = dist[pos[0]][pos[1]].parent; 
        } else { 
            pos[0] = pos[0] - 1;
            pos[1] = pos[1];
            prev_move = dist[pos[0]][pos[1]].parent; 
        }
    }

    if (prev_move == 0) {
        palindrome.push_back(forwards[pos[0]-1]);
    }

    cout << "move is: " << prev_move << " from location " << pos[0] << " "
         << pos[1] << endl << endl;
    cout << "final palindrome: " << palindrome << endl;
    cout << "length: " << palindrome.length() << endl;

    return 0;
}
