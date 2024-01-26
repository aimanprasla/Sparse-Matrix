#pragma once
#include <iostream>
using namespace std;
#include "InternalNode.h"


class SparseMatrix
{
  private:
    ExternalNode* head;
  public:
    SparseMatrix operator+(const SparseMatrix& rhs)
    {
      int rows = getNumRows();
      int cols = getNumCols();
      SparseMatrix temp(rows, cols);
      ExternalNode* tempcurrent = temp.getHead();
      ExternalNode* thiscurrent = getHead();
      ExternalNode* rhscurrent = rhs.head;
      while(tempcurrent->getDown() != nullptr)
        {
          tempcurrent = tempcurrent->getDown();
          thiscurrent = thiscurrent->getDown();
          rhscurrent = rhscurrent->getDown();
          InternalNode* tempcurrent2 = (InternalNode*) tempcurrent;
          InternalNode* thiscurrent2 = (InternalNode*) thiscurrent;
          InternalNode* rhscurrent2 = (InternalNode*) rhscurrent;
          while(tempcurrent2->getRight() != nullptr)
            {
              tempcurrent2 = (InternalNode*) tempcurrent2->getRight();
              thiscurrent2 = (InternalNode*) thiscurrent2->getRight();
              rhscurrent2 =  (InternalNode*) rhscurrent2->getRight();
              temp.addValue(thiscurrent2->getRow(), thiscurrent2->getCol(), thiscurrent2->getData() + rhscurrent2->getData());
            }
        }
      return temp;
    }

  
    SparseMatrix operator*(SparseMatrix& rhs)
    {
      int sum = 0;
      int count = 0;
      int rows = getNumRows();
      int cols = rhs.getNumCols();
      SparseMatrix temp(rows, cols);
      ExternalNode* tempcurrent = temp.getHead();
      ExternalNode* thiscurrent = getHead();
      while (thiscurrent->getDown() != nullptr)
      {
        tempcurrent = tempcurrent->getDown();
        thiscurrent = thiscurrent->getDown();
        InternalNode* tempcurrent2 = (InternalNode*) tempcurrent;
        InternalNode* thiscurrent2 = (InternalNode*) thiscurrent;
        InternalNode* temprhscurrent = (InternalNode*) rhs.head;
        InternalNode* rhscurrent2 = (InternalNode*) temprhscurrent;
        for(int a = 0; a < cols; a++)
          {
            temprhscurrent = (InternalNode*) temprhscurrent->getRight();
            rhscurrent2 = (InternalNode*) temprhscurrent;
            while(thiscurrent2->getRight() != nullptr)
              {
                thiscurrent2 = (InternalNode*) thiscurrent2->getRight();
                rhscurrent2 = (InternalNode*) rhscurrent2->getDown();
                sum = sum + rhscurrent2->getData() * thiscurrent2->getData();
              }
            thiscurrent2 = (InternalNode*) thiscurrent;
            tempcurrent2 = (InternalNode*) tempcurrent2->getRight();
            temp.addValue(tempcurrent2->getRow(), tempcurrent2->getCol(), sum);
            sum = 0;
          }
      }
      return temp;
    }
    SparseMatrix transpose();
    SparseMatrix(int, int);
    void addValue(int, int, int);
    void Print(ostream &out);
    ExternalNode* getHead(){return head;}
    int getNumRows();
    int getNumCols();
};

SparseMatrix::SparseMatrix(int nRows, int nCols)
{
  
  head = new ExternalNode(-1);
  //creates external row pointers
  for(int a = 0; a < nRows; a++)
    {
      ExternalNode* temp = new ExternalNode(a);
      if (head->getDown() == nullptr) 
      {
        head->setDown(temp);
      }
      else 
      {
        ExternalNode* current = head;
        while(current->getDown() != nullptr)
          current = current->getDown();
        current->setDown(temp);
      }
    }
  //creates external column pointers
  for(int a = 0; a < nCols; a++) 
    {
      ExternalNode* temp = new ExternalNode(a);
      if (head->getRight() == nullptr) 
      {
        head->setRight(temp);
      }
      else 
      {
        ExternalNode* current = head;
        while(current->getRight() != nullptr)
          current = current->getRight();
        current->setRight(temp);
      }
    }
  //makes internal node values of zero in the matrix and sets the left and right pointers
  ExternalNode* currentRow = head;
  for(int a = 0; a < nRows; a++)
    {
      currentRow = currentRow->getDown();
      InternalNode* current = (InternalNode*) currentRow;
      for(int b = 0; b < nCols; b++)
        {
          InternalNode* temp = new InternalNode(0);
          temp->setRow(a);
          temp->setCol(b);
          current->setRight(temp);
          temp->setPrev(current);
          current = (InternalNode*) current->getRight();
        }
    }
  //sets the up and down pointers
  ExternalNode* currentRow2 = head;
  ExternalNode* nextRow = head->getDown();
  for(int a = 0; a < nRows; a++)
    {
      InternalNode* current = (InternalNode*) currentRow2;
      InternalNode* nextcurrent = (InternalNode*) nextRow;
      for(int b = 0; b < nCols; b++)
        {
          current = (InternalNode*) current->getRight();
          nextcurrent = (InternalNode*) nextcurrent->getRight();
          current->setDown(nextcurrent);
          nextcurrent->setUp(current);
        }
      currentRow2 = currentRow2->getDown();
      nextRow = currentRow2->getDown();
    }
}

int SparseMatrix::getNumRows()
{
  ExternalNode* temp = head;
  int rows = 0;
  while(temp->getDown() != nullptr)
    {
      rows++;
      temp = temp->getDown();
    }
  return rows;
}
int SparseMatrix::getNumCols()
{
  ExternalNode* temp = head;
  int cols = 0;
  while(temp->getRight() != nullptr)
    {
      cols++;
      temp = temp->getRight();
    }
  return cols;
}

void SparseMatrix::Print(ostream &out)
{
  ExternalNode* temp2 = head;
  while(temp2->getDown() != nullptr)
    {
      temp2 = temp2->getDown();
      ExternalNode* current = temp2;
      while(current->getRight() != nullptr)
        {
          if(current->getRight()->getRight() == nullptr)
          {
            current = current->getRight();
            out << current->getData();
          }
          else
          {
            current = current->getRight();
            out << current->getData() << ", ";
          }
            
      }
      out << endl;
    }
}
//adds values inside internal node
void SparseMatrix::addValue(int row, int col, int value)
{
  InternalNode* current = (InternalNode*) head;
  for(int a = -1; a < row; a++)
    {
      current = (InternalNode*) current->getDown();
    }
  InternalNode* currentCol = current;
  for(int a = -1; a < col; a++)
    {
      currentCol = (InternalNode*) currentCol->getRight();
    }
  currentCol->setData(value);
}
SparseMatrix SparseMatrix::transpose()
{
  int rows = getNumRows();
  int cols = getNumCols();
  //reverse the order of the rows and cols
  SparseMatrix temp(cols, rows);
  ExternalNode* col = this->head;
  while(col->getRight() != nullptr)
    {
      col = col->getRight();
      InternalNode* row = (InternalNode*) col;
      while(row->getDown() != nullptr)
        {
          row = (InternalNode*) row->getDown();
          temp.addValue(row->getCol(), row->getRow(), row->getData());
        }
    }
  return temp;
}
