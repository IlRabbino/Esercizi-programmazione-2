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

    H _peso(Nodo<H> *r){
        if(r)
            return _peso(r->getLeft()) + _peso(r->getRight()) + r->getKey();
        else 
            return 0;
    }
    
    Nodo<H> *_min(Nodo<H> *r){
        if(!r || !r->getLeft())
            return r;
        else 
            return _min(r->getLeft());
    }

    Nodo<H> *_succ(Nodo<H> *r){
        if(r){
            if(r->getRight())
                return _min(r->getRight());
            else{
                Nodo<H> *tmp = r;
                H x = r->getKey();
                do{
                    tmp = tmp->getParent();
                }while(tmp && x>=tmp->getKey());

                if(tmp)
                    return tmp;
                return NULL;
            }
        }
        return NULL;
    }

    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = search(x, r);
        
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
    BST(){root= NULL;}

    void add(H x){
        Nodo<H> *nuovo = new Nodo<H>(x);
        if(root == NULL)
            root = nuovo;
        else{
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

    H peso(H x){
        Nodo<H> *tmp = search(x, root);
        if(tmp){
            return _peso(tmp);
        }
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
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
                    int x = atoi(obj.c_str());
                    t->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    int x = atoi(obj.c_str());
                    t->canc(x);
                }
            }
            int w;
                in >> w;
            out << t->peso(w) << endl;
        }

        else{
            BST<double> *t = new BST<double>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(4, obj.length()-4);
                    double x = atof(obj.c_str());
                    t->add(x);
                }
                else{
                    obj = obj.substr(5, obj.length()-5);
                    double x = atof(obj.c_str());
                    t->canc(x);
                }
            }
            double w;
                in >> w;
            out << t->peso(w) << endl;
        }
    }
    return 0;
}