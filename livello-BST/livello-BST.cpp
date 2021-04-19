//Livelli-BST by Paolo Rabbito
#include<iostream>
#include<fstream>
using namespace std;

inline int massimo(int a, int b) {return a>b?a:b;}

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

    void _inorder(Nodo<H> *r){
        if(r){
            _inorder(r->getLeft());
            cout << r->getKey() << " ";
            _inorder(r->getRight());
        }
    }

    Nodo<H> *search(H x, Nodo<H> *r){
        if(r){
            if(x==r->getKey())
                return r;
            else if(x<r->getKey())
                return search(x, r->getLeft());
            else
                return search(x, r->getRight());
        }
    }

    Nodo<H> *minimo(Nodo<H> *r){
        if(!r || !r->getLeft())
            return r;
        else 
            return minimo(r->getLeft());
    }

    Nodo<H> *successivo(Nodo<H> *r){
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
            Nodo<H> *s = successivo(tmp);
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

    int _altezza(Nodo<H> *r){
        if(!r)
            return 0;
        int s = _altezza(r->getLeft());
        int d = _altezza(r->getRight());
        return 1+massimo(d, s);
    }

    int _level(int level, Nodo<H> *r){
        if(level==0)
            return 1;
        else{
            return _level(level-1, r->getLeft()) + _level(level-1, r->getRight());
        }
        
    }
public:
    BST(){root = NULL;}

    BST<H> *add(H key){
        Nodo<H> *tmp = root;
        Nodo<H> *pre =  NULL;

        while(tmp){
            pre = tmp;
            if(key<=tmp->getKey())
                tmp = tmp->getLeft();
            else 
                tmp = tmp->getRight();
        }

        Nodo<H> *nuovo = new Nodo<H>(key);
        nuovo->setParent(pre);

        if(pre){
            if(key<=pre->getKey())
                pre->setLeft(nuovo);
            else 
                pre->setRight(nuovo);
        }
        else{
            root = nuovo;
        }

        return this;
    }

    BST<H> *canc(H x){
        Nodo<H> *tmp = search(x, root);
        if(tmp)
            _canc(x, tmp);
        return this;
    }

    int altezza(){
        return _altezza(root);
    }

    void print(){
        _inorder(root);
        cout << endl;
    }

    int level(int x){
        return _level(x, root);
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    for(int i=0; i<100; i++){
        string tipo;
            in >> tipo;
            //cout << tipo << endl;
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
            int level = t->altezza();
            out << t << " ";
            for(int j=0; j<level; j++){
                out << t->level(j) << " ";
            }
            out << endl;
            //delete t;
        }
        if(tipo=="double"){
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
            int level = t->altezza();
            out << t << " ";
            for(int j=0; j<level; j++){
                out << t->level(j) << " ";
            }
            out << endl;
            //delete t;
        }
    }
    return 0;
}