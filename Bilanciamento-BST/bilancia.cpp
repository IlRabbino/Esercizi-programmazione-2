#include <iostream>
#include <fstream>
#include <cmath>
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

    Nodo<H> *search(H x, Nodo<H> *r){
        if(r){    
            if(x==r->getKey())
                return r;
            else if(x<r->getKey())
                return search(x, r->getLeft());
            else    
                return search(x, r->getRight());
        }
        return NULL;
    }

    Nodo<H> *minimo(Nodo<H> *r){
        if(!r || !r->getLeft())
            return r;
        else    
            return minimo(r->getLeft());
    }

    Nodo<H> *successore(Nodo<H> *r){
        if(r){
            if(r->getRight())
                return minimo(r->getRight());
            else{
                H x = r->getKey();
                do{
                    r = r->getParent();
                }while(r && x>r->getKey());
                if(r)
                    return r;
                else 
                    return NULL;
            }
        }
    }

    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = search(x, r);

        if(tmp->getLeft() && tmp->getRight()){
            Nodo<H> *s = successore(tmp);
            tmp->setKey(s->getKey());
            _canc(s->getKey(), s);
        }

        else{
            Nodo<H> *child = tmp->getLeft();
            if(!child)
                child = tmp->getRight();
            Nodo<H> *p = tmp->getParent();
            
            if(!p)
                root = child;
            else{
                if(x<p->getKey())
                    p->setLeft(child);
                else 
                    p->setRight(child);
            }

            if(child)
                child->setParent(p);
        }
    
    }

    int _nodi(Nodo<H> *r){
            if(r){
                if(r->getLeft() || r->getRight())
                    return _nodi(r->getLeft()) + _nodi(r->getRight())+1;
                else 
                    return 1;
            }
            return 0;
    }

    int _bilanciato(Nodo<H> *r){
        int dx = _nodi(r->getRight());
        int sx = _nodi(r->getLeft());
        return abs(dx-sx);
    }
public:
    BST(){root = NULL;}

    void add(H x){
        Nodo<H> *nuovo = new Nodo<H>(x);

        
        
        Nodo<H> *tmp = root;
        Nodo<H> *pre = NULL;

        while(tmp){
            pre = tmp;
            if(x<=tmp->getKey())
                tmp = tmp->getLeft();
            else 
                tmp = tmp->getRight();
        }

        nuovo->setParent(pre);

        if(!pre)
            root = nuovo;
        else{
            if(x<=pre->getKey())
                pre->setLeft(nuovo);
            else    
                pre->setRight(nuovo);
        }
    }

    void canc(H x){
        Nodo<H> *tmp = search(x, root);
        if(tmp)
            _canc(x, tmp);
    }

    int bilanciato(H x){
        Nodo<H> *tmp = search(x, root);    
        if(tmp)
            return _bilanciato(tmp);
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
        if(tipo=="int"){
            BST<int> *t = new BST<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(4, obj.length()-4);
                    int x = stoi(obj);
                    t->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    int x = stoi(obj);
                    t->canc(x);
                }
            }
            int k;
                in >> k;
            out << t->bilanciato(k) << endl;
        }
        else if(tipo=="double"){
            BST<double> *t = new BST<double>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(4, obj.length()-4);
                    double x = stod(obj);
                    t->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    double x = stod(obj);
                    t->canc(x);
                }
            }
            double k;
                in >> k;
            out << t->bilanciato(k) << endl;
        }
    }

    return 0;
}