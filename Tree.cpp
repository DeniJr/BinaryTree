/*
Denilson Aparecido Gon�alves Junior - 2176481
Gabriel Hiroshy Sertorio Oda - 2178645
Carla Cristina Franco Bonfiglioli -�2104309
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
    Pre-Condi��o: Um Objeto BinaryTree deve ter sido criado.

    P�s-Condi��o: Apos chamado pelo destrutor, o m�todo Clear deletar�.
    todos os n�s da �rvore caso a mesma j� n�o esteja vazia.

    Descri��o: O m�todo far� chamadas recursivas para visita��o de todos
    os n�s da �rvore, ap�s a recurs�o ocorrer para ambos os filhos, o n�
    ser� deletado e retorna � chamada recursiva anterior
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
    Pre-Condi��o: Um Objeto BinaryTree deve ter sido criada
    e um arquivo para leitura de entrada deve existir.

    Pos-Condi��o: Caso o Arquivo seja aberto com sucesso, a
    arvore ser� preenchida com os dados do arquivo, fechando-o
    ap�s a conclus�o do processo de inser��o.

    Descri��o: De inicio, o m�todo verifica se o arquivo foi
    aberto, em seguida, ele cria as vari�veis que receber�o
    os dados do arquivo e uma vari�vel booleana que ser� usada
    durante o processo de inser��o para poupar processamento.
    Por fim, chama o m�todo privado Insert (que ser� o real
    respons�vel pela cria��o dos n�) dentro de um la�o,
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
    Pre-Condi��o: --

    Pos-Condi��o: A arvore ser� preenchida com os dados do
    arquivo, seguindo os par�metros de entrada.

    Descri��o: O M�todo come�a verificando se a arvore est�
    vazia, caso esteja, a raiz e suas sub�rvores ser�o criadas.
    Caso a �rvore n�o esteja vazia, o algoritmo percorrer�
    recursivamente os n�s da �rvore at� encontrar o n� cuja
    entrada � igual a chave1, e ent�o criar� suas sub�rvores
    utilizando chave2 e chave3. Ao encontrar o n�, a booleana
    found receber� true, fazendo com que todas as chamadas
    anteriores retornem, evitando novas chamadas desneces�rias.
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
    Pre-Condi��o: Um Objeto BinaryTree deve ter sido criado e
    deve haver pelo menos um n�.

    P�s-Condi��o: Ser� impresso na tela todos os n�s da �rvore,
    o numero de n�s e a quantidade de n�s folhas.

    Descri��o: Antes de qualquer a��o, o m�todo  verifica se a
    a �rvore n�o est� vazia, caso n�o esteja, ele cria os
    par�metros necess�rios para o m�todo privado Print e por final,
    imprime a quantidade de n�s e n�s folha
    */
    cout << "Conjunto de dados do arquivo:\n";
    if(root != NULL){
        int Nodes = 0;
        int Leaves = 0;
        Print(root, Nodes, Leaves);
        cout << Nodes << " " << Leaves << endl;
    }
    else{
        cout << "\n�rvore vazia\n";
    }
}
void BinaryTree::Print(TreePointer &r, int &Nodes, int &Leaves){
    /*
    Pr�-Condi��o: --

    P�s-Condi��o: N� a n�, o m�todo ir� imprimir os dados
    conforme solicitados.

    Descri��o: Cada chamada recursiva, o metodo incrementar� a
    vari�vel Nodes, enquanto Leaves ser� incrementada a cada n�
    folho encontrado. O m�todo funciona em pr�-ordem. processando
    o n� antes de realizar outra chamada recursiva
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
    Pr�-Condi��o: Um Objeto BinaryTree deve ter sido criado e
    deve haver pelo menos um n�.

    P�s-Condi��o: A estrutura ser� impressa em forma de �rvore

    Descri��o: Chama o m�todo privado PrintTree caso a �rvore
    n�o esteja vazia
    */
    cout << "Estrutura da arvore:\n";
    if(root != NULL){
        int spaces = 0;
        PrintTree( root, spaces);
    }
    else{
        cout << "\n�rvore vazia\n";
    }
}
void BinaryTree::PrintTree(TreePointer &r, int spaces){
    /*
    Pr�-Condi��o: --

    P�s-Condi��o: Imprime na tela a entrada do n� para aquela
    chamada recursiva

    Descri��o: O m�todo faz a impress�o da entrada do n�
    utilizando identa��o para que a sa�da seja em forma de
    �rvore
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

