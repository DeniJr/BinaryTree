
#include "Tree.h"
#include <iostream>
#include <string>
int main(){
    string file;
    cout << "Digite o nome do arquivo que deseja ler, seguido de \".tree\":";
    cin >> file;
    BinaryTree Tree;
    Tree.Insert(file);
    Tree.Print();
    cout << endl;
    Tree.PrintTree();
    return 0;
}
