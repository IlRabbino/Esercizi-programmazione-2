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

    void setKey(H key){this->key=key;}
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

    Nodo<H> * _rmin(Nodo<H> *r){
        if(!r || !r->getLeft())
            return r;
        else    
            return _rmin(r->getLeft());   
    }

    Nodo<H> *_successore(Nodo<H> *tmp){
        if(tmp){
            if(tmp->getRight())
                return _rmin(tmp->getRight());
            else{
                H x = tmp->getKey();
                do{
                    tmp = tmp->getParent();
                }while (tmp && tmp->getKey()<x);   

                if(tmp)
                    return tmp;         
            }

            return NULL;
        }
        return NULL;
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

    void add(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);
        if(root==NULL)
            root = nuovo;
        
        else{
            Nodo<H> *tmp = root;
            Nodo<H> *pre = NULL;

            while(tmp){
                pre = tmp;
                if(key<=tmp->getKey())
                    tmp = tmp->getLeft();
                else 
                    tmp = tmp->getRight();
            }

            nuovo->setParent(pre);
            if(key<=pre->getKey())
                pre->setLeft(nuovo);
            else 
                pre->setRight(nuovo);
        }
    }

    void canc(H key){
        Nodo<H> *tmp = _search(key, root);
        if(tmp){
            _canc(key, tmp);
        }
    }

    H successore(H key){
        Nodo<H> *tmp = _search(key, root);
        if(tmp){    
            Nodo<H> *r = _successore(tmp);
            if(r==NULL)
                return -1;
            return r->getKey();
        }
    }

    void print(){
        _inorder(root);
        cout << endl;
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
        int m;
            in >> m;
        
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
            for(int k=0; k<m; k++){
                int g;
                    in >> g;
                out << tree->successore(g) << " ";
            }
            out << endl;
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
            for(int k=0; k<m; k++){
                double g;
                    in >> g;
                out << tree->successore(g) << " ";
            }
            out << endl;
        }
    }
    return 0;
}