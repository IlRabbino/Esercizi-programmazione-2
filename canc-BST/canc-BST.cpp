#include<iostream>
#include<fstream>
using namespace std;

template<class H>
class Nodo{
private:
    Nodo<H> *left, *right, *parent;
    H key;
public:
    Nodo(H key){
        this->key = key;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    void setKey(H key){this->key = key;}
    void setLeft(Nodo<H> *left){this->left = left;}
    void setRight(Nodo<H> *right){this->right = right;}
    void setParent(Nodo<H> *parent){this->parent = parent;}

    H getKey(){return key;}
    Nodo<H> *getLeft(){return left;}
    Nodo<H> *getRight(){return right;}
    Nodo<H> *getParent(){return parent;}
};

template<class H>
class BST{
private:
    Nodo<H> *root;

    void _inorder(ofstream& out, Nodo<H> *r){
        if(r){
            _inorder(out, r->getLeft());
            out << r->getKey() << " ";
            _inorder(out, r->getRight());
        }
    }

    void _preorder(ofstream& out, Nodo<H> *r){
        if(r){
            out << r->getKey() << " ";
            _preorder(out, r->getLeft());
            _preorder(out, r->getRight());
        }
    }

    void _postorder(ofstream& out, Nodo<H> *r){
        if(r){
            _postorder(out, r->getLeft());
            _postorder(out, r->getRight());
            out << r->getKey() << " ";
        }
    }

    Nodo<H> *_search(H x, Nodo<H> *r){
        if(r){
                if(x==r->getKey())
                    return r;
                else if(x<r->getKey())
                    return _search(x, r->getLeft());
                else 
                    return _search(x, r->getRight());
            }
    }

    Nodo<H> *_min(Nodo<H> *r){
        if(!r->getLeft())
            return r;
        else 
            return _min(r->getLeft());
    }

    Nodo<H> *_succ(Nodo<H> *r){
        if(r->getRight())
            return _min(r->getRight());
        else{
            H x = r->getKey();
            do
            {
                r = r->getParent();
            } while (r && r->getKey()<x);
            if(r)
                return r;
        }
        return NULL;
    }

    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = _search(x, r);

        if(tmp->getLeft() && tmp->getRight()){
            Nodo<H> *s = _succ(tmp);
            tmp->setKey(s->getKey());
            _canc(s->getKey(), s);
        }

        else{
            Nodo<H> *child = tmp->getLeft();
            if(!child)
                child = tmp->getRight();
            Nodo<H> *p = tmp->getParent();
            if(p){
                if(x<p->getKey())
                    p->setLeft(child);
                else 
                    p->setRight(child);
            }
            else
                root = child;
            
            if(child)
                child->setParent(p);
        }
    }
public:
    BST(){root = NULL;}

    BST<H> *add(H x){
        Nodo<H> *tmp = root;
        Nodo<H> *pre = NULL;

        while(tmp){
            pre = tmp;
            if(x<=tmp->getKey())
                tmp = tmp->getLeft();
            else 
                tmp = tmp->getRight();
        }

        Nodo<H> *nuovo = new Nodo<H>(x);
        nuovo->setParent(pre);

        if(!pre)
            root = nuovo;
        else{
            if(x<pre->getKey())
                pre->setLeft(nuovo);
            else    
                pre->setRight(nuovo);
        }

        return this;
    }
    
    BST<H> *canc(H x){
        Nodo<H> *r = _search(x, root);
        _canc(x, r);
        return this;
    }

    void print(ofstream& out, string stampa){
        if(stampa=="inorder")
            _inorder(out, root);
        else if(stampa=="preorder")
            _preorder(out, root);
        else 
            _postorder(out, root);

        out << endl;
    }
};

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");

    for(int i=0; i<100; i++){
        string tipo;
            in >> tipo;
        int n;
            in >> n;
        string stampa;
            in >> stampa;
        cout << tipo << endl;

        if(tipo=="int"){
            BST<int> *tree = new BST<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(4, obj.length()-4);
                    int x = stoi(obj);
                    tree->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    int x = stoi(obj);
                    tree->canc(x);
                }
            }
            tree->print(out, stampa);
            delete tree;
        }

        else if(tipo=="double"){
            BST<double> *tree = new BST<double>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(4, obj.length()-4);
                    double x = stod(obj);
                    tree->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    double x = stod(obj);
                    tree->canc(x);
                }
            }
            tree->print(out, stampa);
            delete tree;
        }

        else if(tipo=="char"){
            BST<char> *tree = new BST<char>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                
                if(obj[0]=='i'){
                    char x = obj[4];
                    tree->add(x);
                }
                else{
                    char x = obj[5];
                    tree->canc(x);
                }
            }
            tree->print(out, stampa);
            delete tree;
        }

        else if(tipo=="bool"){
            BST<char> *tree = new BST<char>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                
                if(obj[0]=='i'){
                    char x = obj[4];
                    tree->add(x);
                }
                else{
                    char x = obj[5];
                    tree->canc(x);
                }
            }
            tree->print(out, stampa);
            delete tree;
        }
    }

    return 0;
}