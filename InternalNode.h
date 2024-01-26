#pragma once
#include <iostream>
using namespace std;
#include "ExternalNode.h"

class InternalNode : public ExternalNode
{
  private:
    int row;
    int col;
    InternalNode* prev;
    InternalNode* up;
    InternalNode* down;
  public:
    InternalNode(int _data) : ExternalNode(_data) {prev = nullptr; up = nullptr;}
    void setPrev(InternalNode* input){prev = input;}
    void setUp(InternalNode* input){up = input;}
    void setRow(int _row){row = _row;}
    void setCol(int _col){col = _col;}
    InternalNode* getUp(){return up;}
    InternalNode* getPrev(){return prev;}
    int getRow(){return row;}
    int getCol(){return col;}
    int getData(){return ExternalNode::getData();}
    void setData(int data){ExternalNode::setData(data);}
};