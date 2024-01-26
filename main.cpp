#include "ArgumentManager.h"
#include "InternalNode.h"
#include "SparseMatrix.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream fin("input1.txt");   // am.get("input"));
  ofstream fout("testoutput.txt"); //am.get("output"));

  char operation;
  int numRows, numCols;
  int row, col, value;
  string line;
  fin >> operation;
  if(operation == '+' || operation == '*') //if user wants addition or multiplication create 2 matrices
  {
    fin >> numRows >> numCols;
    fin.ignore();
    SparseMatrix matrix(numRows, numCols);
    while(getline(fin, line)){
      if(line.length() == 0){
        break;
      }
      stringstream st(line);
      st >> row >> col >> value;
      matrix.addValue(row, col, value);
    }
    //^^^^^^created first matrix and printed it with the externalnodes
    
    int numRows2, numCols2;
    fin >> numRows2 >> numCols2;
    SparseMatrix matrix2(numRows, numCols);
    fin.ignore();
    while(getline(fin, line)){
      if (line.length() == 0){
        break;
      }
      stringstream st(line);
      st >> row >> col >> value;
      matrix2.addValue(row, col, value);
    }
    //^^^^^^created second matrix and printed it with the externalnodes
    
    if (operation == '+')//if statement for addition
    {
      if(numRows != numRows2 || numCols != numCols2)
      {
        fout << "Invalid Matrix Operation" << endl;
        exit(0);
      }
      else  
      {
        SparseMatrix matrix3 = matrix + matrix2;
        matrix3.Print(fout);
      }
    }
    else if (operation == '*')//else for multiplication
    {
      if (numCols != numRows2)
      {
        fout << "Invalid Matrix Operation" << endl;
        exit(0);
      }
      else 
      {
        SparseMatrix matrix3 = matrix * matrix2;
        matrix3.Print(fout);
      }
    }
  }
  else //if user wants transpose only one matrix is created
  {
    fin >> numRows >> numCols;
    fin.ignore();
    SparseMatrix matrix(numRows, numCols);
    while(getline(fin, line)){
      if(line.length() == 0){
        break;
      }
      stringstream st(line);
      st >> row >> col >> value;
      matrix.addValue(row, col, value);
    }
    SparseMatrix matrix2 = matrix.transpose();
    matrix2.Print(fout);
  }
  
  return 0;
}