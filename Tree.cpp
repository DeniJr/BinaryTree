/*
Denilson Aparecido Gonçalves Junior - 2176481
Gabriel Hiroshy Sertorio Oda - 2178645
Carla Cristina Franco Bonfiglioli - 2104309
*/
#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

BinaryTree::BinaryTree(){
    root = NULL;
}
BinaryTree::~BinaryTree(){
    Clear(root);
}
void BinaryTree::Clear(TreePointer &r){
    /*
    Pre-Condição: Um Objeto BinaryTree deve ter sido criado.

    Pós-Condição: Apos chamado pelo destrutor, o método Clear deletará.
    todos os nós da árvore caso a mesma já não esteja vazia.

    Descrição: O método fará chamadas recursivas para visitação de todos
    os nós da árvore, após a recursão ocorrer para ambos os filhos, o nó
    será deletado e retorna á chamada recursiva anterior
    */

    if(r == NULL)
        return;
    if(r->LeftNode != NULL)
        Clear(r->LeftNode);
    if(r->RightNode != NULL)
        Clear(r->RightNode);
    TreePointer q = r;
    delete q;
    return;
}
void BinaryTree::Insert(string file){
    /*
    Pre-Condição: Um Objeto BinaryTree deve ter sido criada
    e um arquivo para leitura de entrada deve existir.

    Pos-Condição: Caso o Arquivo seja aberto com sucesso, a
    arvore será preenchida com os dados do arquivo, fechando-o
    após a conclusão do processo de inserção.

    Descrição: De inicio, o método verifica se o arquivo foi
    aberto, em seguida, ele cria as variáveis que receberão
    os dados do arquivo e uma variável booleana que será usada
    durante o processo de inserção para poupar processamento.
    Por fim, chama o método privado Insert (que será o real
    responsável pela criação dos nó) dentro de um laço,
    */

    ifstream arquivo(file, ios::in);
    if(arquivo.is_open()){
        string linha, chave1, chave2, chave3;
        bool found;
        while(getline(arquivo, linha)){
            found = false;
            stringstream FileEntry (linha);
            FileEntry >> chave1 >> chave2 >> chave3;
            if(chave1 != "X")
                Insert(root, chave1, chave2, chave3, found);
        }
        arquivo.close();
    }
    else{
        cout << "\nO Arquivo nao pode ser aberto";
        abort();
    }
}
void BinaryTree::Insert(TreePointer &r, string &chave1, string &chave2, string &chave3, bool &found){
    /*
    Pre-Condição: --

    Pos-Condição: A arvore será preenchida com os dados do
    arquivo, seguindo os parâmetros de entrada.

    Descrição: O Método começa verificando se a arvore está
    vazia, caso esteja, a raiz e suas subárvores serão criadas.
    Caso a árvore não esteja vazia, o algoritmo percorrerá
    recursivamente os nós da árvore até encontrar o nó cuja
    entrada é igual a chave1, e então criará suas subárvores
    utilizando chave2 e chave3. Ao encontrar o nó, a booleana
    found receberá true, fazendo com que todas as chamadas
    anteriores retornem, evitando novas chamadas desnecesárias.
    */

    if(r == NULL){
        r = new TreeNode;
        r->Entry = chave1;
        if(chave2 != "X"){
            r->LeftNode = new TreeNode;
            r->LeftNode->Entry = chave2;
        }
        if(chave3 !=  "X"){
            r->RightNode = new TreeNode;
            r->RightNode->Entry = chave3;
        }
        return;
    }
    else if (chave1 == r->Entry){
        found = true;
        if(chave2 != "X"){
            r->LeftNode = new TreeNode;
            r->LeftNode->Entry = chave2;
            r->LeftNode->LeftNode = NULL;
            r->LeftNode->RightNode = NULL;

        }
        else
            r->LeftNode = NULL;
        if(chave3 != "X"){
            r->RightNode = new TreeNode;
            r->RightNode->Entry = chave3;
            r->RightNode->LeftNode = NULL;
            r->RightNode->RightNode = NULL;
        }
        else
            r->RightNode = NULL;
        return;
    }
    else{
        if(r->LeftNode != NULL){
            Insert(r->LeftNode, chave1, chave2, chave3, found);

            if(found)
                return;
        }
        if(r->RightNode != NULL){
            Insert(r->RightNode, chave1, chave2, chave3, found);
            return;
        }
    }
    return;
}
void BinaryTree::Print(){
    /*
    Pre-Condição: Um Objeto BinaryTree deve ter sido criado e
    deve haver pelo menos um nó.

    Pós-Condição: Será impresso na tela todos os nós da árvore,
    o numero de nós e a quantidade de nós folhas.

    Descrição: Antes de qualquer ação, o método  verifica se a
    a árvore não está vazia, caso não esteja, ele cria os
    parâmetros necessários para o método privado Print e por final,
    imprime a quantidade de nós e nós folha
    */
    cout << "Conjunto de dados do arquivo:\n";
    if(root != NULL){
        int Nodes = 0;
        int Leaves = 0;
        Print(root, Nodes, Leaves);
        cout << Nodes << " " << Leaves << endl;
    }
    else{
        cout << "\nÁrvore vazia\n";
    }
}
void BinaryTree::Print(TreePointer &r, int &Nodes, int &Leaves){
    /*
    Pré-Condição: --

    Pós-Condição: Nó a nó, o método irá imprimir os dados
    conforme solicitados.

    Descrição: Cada chamada recursiva, o metodo incrementará a
    variável Nodes, enquanto Leaves será incrementada a cada nó
    folho encontrado. O método funciona em pré-ordem. processando
    o nó antes de realizar outra chamada recursiva
    */
    Nodes++;
    int num = 0;
    string sons;
    if(r->LeftNode != NULL){
        num++;
        sons += "E";
    }
    if(r->RightNode != NULL){
        num++;
        sons += "D";
    }
    if(sons == "")
        cout << r->Entry << " " << num << " F\n";
    else
        cout << r->Entry << " " << num << " " << sons << endl;
    if(r->LeftNode == NULL && r->RightNode == NULL){
        Leaves++;
        return;
    }
    if(r->LeftNode != NULL){
        Print(r->LeftNode, Nodes, Leaves);

    }
    if(r->RightNode != NULL)
        Print(r->RightNode, Nodes, Leaves);
    return;
}
void BinaryTree::PrintTree(){
    /*
    Pré-Condição: Um Objeto BinaryTree deve ter sido criado e
    deve haver pelo menos um nó.

    Pós-Condição: A estrutura será impressa em forma de árvore

    Descrição: Chama o método privado PrintTree caso a árvore
    não esteja vazia
    */
    cout << "Estrutura da arvore:\n";
    if(root != NULL){
        int spaces = 0;
        PrintTree( root, spaces);
    }
    else{
        cout << "\nÁrvore vazia\n";
    }
}
void BinaryTree::PrintTree(TreePointer &r, int spaces){
    /*
    Pré-Condição: --

    Pós-Condição: Imprime na tela a entrada do nó para aquela
    chamada recursiva

    Descrição: O método faz a impressão da entrada do nó
    utilizando identação para que a saída seja em forma de
    árvore
    */
    if(r->RightNode == NULL){
        for(int i = 0; i < spaces+1; i++)
            cout << "      ";
        cout << "X" << endl;
    }
    else
        PrintTree(r->RightNode, spaces+1);
    for(int i = 0; i < spaces; i++)
        cout << "      ";
    cout << r->Entry << endl;
    if(r->LeftNode == NULL){
        for(int i = 0; i < spaces+1; i++)
            cout << "      ";
        cout << "X" << endl;
    }
    else
        PrintTree(r->LeftNode, spaces+1);
}

