#pragma once
#include <iostream>
using namespace std;

class ExternalNode
{
  private:
    int data;
    ExternalNode* down;
    ExternalNode* right;
  public:
    ExternalNode(int);
    void setDown(ExternalNode* input){down = input;}
    void setRight(ExternalNode* input){right = input;}
    void setData(int _data){data = _data;}
    ExternalNode* getDown(){return down;}
    ExternalNode* getRight(){return right;}
    int getData(){return data;}
};

ExternalNode::ExternalNode(int _data)
{
  data = _data;
  down = nullptr;
  right = nullptr;
}