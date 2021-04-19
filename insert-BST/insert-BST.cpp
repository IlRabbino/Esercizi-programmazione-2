#include <iostream>
#include <fstream>

using namespace std;

template<class H>
class Nodo{
private:
    H key;
    Nodo<H> *right, *left, *parent;
public:
    Nodo(H key){
        this->key = key;
        right = NULL;
        left = NULL;
        parent = NULL;
    }
    //set method
    void setKey(H key){this->key = key;}
    void setRight(Nodo<H> *right){this->right = right;}
    void setLeft(Nodo<H> *left){this->left = left;}
    void setParent(Nodo<H> *parent){this->parent=parent;}

    //get method
    Nodo<H> *getRight(){return right;}
    Nodo<H> *getLeft(){return left;}
    Nodo<H> *getParent(){return parent;}
    H getKey(){return key;}
};

template<class H>
class BST{
protected:
    Nodo<H> *root;

    void _preorder(ofstream &out, Nodo<H> *r){
        if(r){
            out << r->getKey() << " ";
            _preorder(out, r->getLeft());
            _preorder(out, r->getRight());
        }
    }

    void _inorder(ofstream &out, Nodo<H> *r){
        if(r){
            _inorder(out, r->getLeft());
            out << r->getKey() << " ";
            _inorder(out, r->getRight());
        }
    }

    void _postorder(ofstream &out, Nodo<H> *r){
        if(r){
            _postorder(out, r->getLeft());
            _postorder(out, r->getRight());
            out << r->getKey() << " ";
        }
    }
public:
    BST(){root = NULL;}

    void add(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);
        Nodo<H> *tmp = root;
        Nodo<H> *pre = NULL;
        while(tmp){
            pre = tmp;
            if(key>tmp->getKey())
                tmp = tmp->getRight();
            else 
                tmp = tmp->getLeft();
        }

        nuovo->setParent(pre);
        if(!pre)
            root = nuovo;
        else{    
            if(key>pre->getKey())
                pre->setRight(nuovo);
            else 
                pre->setLeft(nuovo);
        }
    }

    void print(ofstream &out, string s){
        if(s=="preorder"){
            _preorder(out, root);
        }
        if(s=="inorder"){
            _inorder(out, root);
        }
        if(s=="postorder"){
            _postorder(out, root);
        }
        out << endl;
    }
};

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");

    for(int i=0; i<100; i++){
        string tipo;
            in >> tipo;
            cout << tipo << endl;
        int n;
            in >> n;
        string stampa;
            in >> stampa;

        if(tipo=="int"){
            BST<int> *tree = new BST<int>();
            for(int j=0; j<n; j++){
                int x;
                    in >> x;
                tree->add(x);
            }
            tree->print(out, stampa);
            delete tree;
        }
        if(tipo=="double"){
            BST<double> *tree = new BST<double>();
            for(int j=0; j<n; j++){
                double x;
                    in >> x;
                tree->add(x);
            }
            tree->print(out, stampa);
            delete tree;
        }
        if(tipo=="char"){
            BST<char> *tree = new BST<char>();
            for(int j=0; j<n; j++){
                char x;
                    in >> x;
                tree->add(x);
            }
            tree->print(out, stampa);
            delete tree;
        }
        if(tipo=="bool"){
            BST<int> *tree = new BST<int>();
            for(int j=0; j<n; j++){
                int x;
                    in >> x;
                tree->add(x);
            }
            tree->print(out, stampa);
            delete tree;
        }
    }

    return 0;
}