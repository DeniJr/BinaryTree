/*
Denilson Aparecido Gonçalves Junior - 2176481
Gabriel Hiroshy Sertorio Oda - 2178645
Carla Cristina Franco Bonfiglioli - 2104309
*/
#include <string>
using namespace std;
#ifndef TREE_H
#define TREE_H

class BinaryTree{
public:
    BinaryTree();
    ~BinaryTree();
    void Insert(string file);
    void Print();
    void PrintTree();
private:
    struct TreeNode{
        string Entry;
        TreeNode *LeftNode = NULL, *RightNode = NULL;
    };
    typedef TreeNode *TreePointer;
    TreePointer root;
    void Clear(TreePointer &r);
    void Insert(TreePointer &r, string &chave1, string &chave2, string &chave3, bool &found);
    void Print(TreePointer &r, int &Nodes, int &NoSonNodes);
    void PrintTree(TreePointer &r, int spaces);
};
#endif
