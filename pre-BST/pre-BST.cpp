//Predecessore-BST by Paolo Rabbito
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

    Nodo<H> *_search(H key, Nodo<H> *r){
        if(r){
            if(key==r->getKey())
                return r;
            else if(key<r->getKey())
                return _search(key, r->getLeft());
            else 
                return _search(key, r->getRight());
        }
    }

    Nodo<H> *_rmin(Nodo<H> *r){
        if(!r || !r->getLeft()){
            return r;
        }
        return _rmin(r->getLeft());
    }

    Nodo<H> *_rmax(Nodo<H> *r){
        if(!r || !r->getRight()){
            return r;
        }
        return _rmax(r->getRight());
    }

    Nodo<H> *_successore(Nodo<H> *r){
        if(r->getRight())
            return _rmin(r->getRight());
        else{
            H x = r->getKey();
            do{
                r = r->getParent();
            }while(r && r->getKey()<x);
            if(r)
                return r;
            return NULL;
        }
        
    }


    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = _search(x, r);

        if(tmp->getLeft() && tmp->getRight()){
            Nodo<H> *s = _successore(tmp);
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
    BST(){root=NULL;}

    BST<H> *add(H key){
        Nodo<H> *tmp = root;
        Nodo<H> *pre = NULL;
        while(tmp){
            pre = tmp;
            if(key<=tmp->getKey())
                tmp = tmp->getLeft();
            else 
                tmp = tmp->getRight();
        }

        Nodo<H> *nuovo = new Nodo<H>(key);
        nuovo->setParent(pre);

        if(!pre)
            root = nuovo;
        else{
            if(key<=pre->getKey())
                pre->setLeft(nuovo);
            else    
                pre->setRight(nuovo);
        }

        return this;
    }

    BST<H> *canc(H key){
        Nodo<H> *tmp = _search(key, root);
        if(tmp)
            _canc(key, tmp);
        return this;
    }

    Nodo<H> *precedente(H x){
        Nodo<H> *tmp = _search(x, root);   
        if(tmp->getLeft())
            return _rmax(tmp->getLeft());
        else{
            H y = tmp->getKey();
            do{
                tmp = tmp->getParent();
            }while(tmp && tmp->getKey()>=y);
            if(tmp)
                return tmp;

        }
        return NULL;
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
        int m;
            in >> m;
        cout << tipo << endl;
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
                else if(obj[0]=='c'){
                    obj = obj.substr(5, obj.length()-5);
                    int x = stoi(obj);
                    t->canc(x);
                }
            }

            for(int j=0; j<m; j++){
                int k;
                    in >> k;
                Nodo<int> *pre = t->precedente(k);
                if(!pre)
                    out << -1 << " ";
                
                else  
                    out << pre->getKey() << " ";
            }

            out << endl;
            delete t;
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
                else if(obj[0]=='c'){
                    obj = obj.substr(5, obj.length()-5);
                    double x = stod(obj);
                    t->canc(x);
                }
            }

            for(int j=0; j<m; j++){
                double k;
                    in >> k;
                Nodo<double> *pre = t->precedente(k);
                if(!pre)
                    out << -1 << " ";
                
                else  
                    out << pre->getKey() << " ";
            }

            out << endl;
            delete t;
        }
    }
    return 0;
}