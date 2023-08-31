#include <iostream>
#include<stdlib.h>
using namespace std;


int safe[9][9][10];
int table[9][9];
int empty = 0;
int mark[9][9];


void printTable();

bool put(int i, int j, int k){

    if(table[i][j] != 0 || safe[i][j][k] != 0)
        return false;


    table[i][j] = k;
    for (int l = 0; l < 9; l++) {
        safe[i][l][k]++;
        safe[l][j][k]++;


        mark[i][l]++;
        mark[l][j]++;
    }
//    cout << i << " /*/*/* " << j << endl;
    int f = (i / 3 ) * 3 ;
    int d = (j / 3) * 3 ;
    for (int l = f; l < f+3; l++) {
        for (int m = d; m < d+3; m++) {
            safe[l][m][k]++;

            mark[l][m]++;
//            cout << l << "   " << m << "  " << table[l][m] << "\t" << endl;
        }
    }

//    cout << " ------------" << endl;

//    printTable();
    return true;
}

void printTable() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << table[i][j] << " " ;
        }
        cout << endl;
    }


    cout << "-------------" << endl;
}


void pick(int i,int j ,int k){
    table[i][j] = 0;

    for (int l = 0; l < 9; l++) {
        safe[i][l][k]--;
        safe[l][j][k]--;

        mark[i][l]--;
        mark[l][j]--;
    }

    int f = (i / 3) * 3;
    int d = (j / 3) * 3 ;

    for (int l = f; l < f+3; l++) {
        for (int m = d; m < d+3; m++) {
            safe[l][m][k]--;

            mark[l][m]--;
        }
    }
}

void printSolve(){

    cout << endl << "this is a solve of your table " << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << table[i][j] << " " ;
        }

        cout << endl;
    }
}

bool findBestCandidate(int &x,int &y){

    int max_dec = -1;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(table[i][j] == 0 & max_dec < mark[i][j]){
                x = i;
                y = j;
                max_dec = mark[i][j];
            }
        }
    }


    if(max_dec == 9)
        return false;

    return true;

}


void BT(int level){
    if(level == empty){
        printSolve();
        exit(0);
    }

//    cout << level << "   "  <<  empty <<endl;

//    for (int i = 0; i < 9; i++) {
//        for (int j = 0; j < 9; j++) {
//            for (int k = 1; k <= 9; k++) {
//                if(put(i,j,k)){
//                    BT(level+1);
//                    pick(i,j,k);
//                }
//            }
//        }
//    }

    int x,y;
    if(findBestCandidate(x,y)){
        for (int k = 1; k <= 9; k++) {
            if(put(x,y,k)){
                    BT(level+1);
                    pick(x,y,k);
            }
        }
    }



}


void inputReader(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int u;
            cin >> u;
            put(i,j,u);
            if(u == 0)
                empty++;

        }
    }
}




int main()
{

    inputReader();

    BT(0);

}
