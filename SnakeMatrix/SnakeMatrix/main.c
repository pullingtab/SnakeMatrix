//
//  main.c
//  SnakeMatrix
//
//  Created by 爽 张 on 16/1/8.
//  Copyright © 2016年 爽 张. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // boolean value solution of c99

typedef unsigned int** SnakeMatrix;
#define MATRIX(n) unsigned int (*)[n];

SnakeMatrix initSnakeMatrix(int n);
void destroySnakeMatrix(SnakeMatrix sm, int n);
void createMatrix(SnakeMatrix sm, int n);
void printMatrix(SnakeMatrix sm, int n);

int main(int argc, const char * argv[]) {
    
    int n = 0;
    
    // get n
    printf("input n:\n");
    scanf("%d", &n);
    
    // allocate memory
    SnakeMatrix sm = initSnakeMatrix(n);
    
    // create a snake matrix
    createMatrix(sm, n);
    
    // print the matrix
    printMatrix(sm, n);
    
    // release memory
    destroySnakeMatrix(sm, n);
    
    return 0;
}

SnakeMatrix initSnakeMatrix(int n){
    SnakeMatrix sm = NULL;
    sm = (SnakeMatrix)malloc(n*sizeof(unsigned int*));
    for (int i=0; i<n; ++i) {
        sm[i] = malloc(n*sizeof(unsigned int));
    }
    return sm;
}

void destroySnakeMatrix(SnakeMatrix sm, int n){
    for (int i=0; i<n; ++i) {
        free(sm[i]);
    }
    free(sm);
}

bool isInsideMatrix(const int n, const unsigned int i, const unsigned int j){
    if (i<0) // always false
        return false;
    if (i>=n)
        return false;
    if (j<0) // always false
        return false;
    if (j>=n)
        return false;
    
    return true;
}

void fillCurrentLine(SnakeMatrix sm, const int n, unsigned int i, unsigned int j, const int turnCount, const int startNum){
    // increasement
    int increase = turnCount%2==1?1:-1;
    // the number that is filled in the cell
    int fillNum = startNum;

    // fill the first cell
    sm[i][j] = fillNum;
    // move to next cell
    i = i+1;
    j = j-1;
    // update the fill-number
    fillNum = fillNum + increase;
    
    // fill the rest of the line
    while (isInsideMatrix(n, i, j)) {
        // fill current cell
        sm[i][j] = fillNum;
        // move to next cell
        i = i+1;
        j = j-1;
        // update the fill-number
        fillNum = fillNum + increase;
    }
}

void createMatrix(SnakeMatrix sm, int n){
    // fill the first row, and their fellow-line
    for (int i=0; i<n; ++i) {
        int turnCount = i+1;
        int fillNum = 0;
        
        // calculate fill-number
        if(i==0)
            fillNum = 1;
        else if (turnCount%2==0)
            fillNum = sm[0][i-1] + (i+1)*2-2;
        else if (turnCount%2==1)
            fillNum = sm[0][i-1] + 1;
        
        // fill the cell and its fellow-line
        fillCurrentLine(sm, n, 0, i, turnCount, fillNum);
    };
    
    // fill the last column, and their fellow-line
    for (int i=1; i<n; ++i) {
        int turnCount = n+i;
        int fillNum = 0;
        
        // calculate fill-number
        if (turnCount%2==1)
            fillNum = sm[i-1][n-1] + 1;
        else if (turnCount%2==0)
            fillNum = sm[i-1][n-1] + (n-i-1)*2+2;
        
        // fill the cell and its fellow-line
        fillCurrentLine(sm, n, i, n-1, turnCount, fillNum);
    };
}

void printMatrix(SnakeMatrix sm, int n){
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            // calculate the maximum length of the numbers in the matrix
            char strNum[100];
            sprintf(strNum, "%d", n*n);
            unsigned long len = strlen(strNum);
            
            // make format string
            // eg: n = 10
            //     %3u
            //     n = 7
            //     %2u
            //     n = 3
            //     %1u
            char formatStr[5];
            sprintf(formatStr, "%%%luu ",len);
            
            printf(formatStr, sm[i][j]);
        }
        printf("\n");
    };
}