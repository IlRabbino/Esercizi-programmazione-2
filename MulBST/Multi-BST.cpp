#include <iostream>
#include <fstream>
using namespace std;

template<class H>
class Nodo{
private:
    Nodo<H> *left, *right, *parent;
    H key;
    int mul;
public:
    Nodo(H key){
        this->key = key;
        left = NULL;
        right = NULL;
        parent = NULL;
        mul = 1;
    }

    void incMul(){mul++;}
    void decMul(){mul--;}

    void setMul(int mul){this->mul = mul;}
    void setKey(H key){this->key = key;}
    void setLeft(Nodo<H> *left){this->left = left;}
    void setRight(Nodo<H> *right){this->right = right;}
    void setParent(Nodo<H> *parent){this->parent = parent;}

    H getKey(){return key;}
    Nodo<H> *getLeft(){return left;}
    Nodo<H> *getRight(){return right;}
    Nodo<H> *getParent(){return parent;}
    int getMul(){return mul;}
};

template<class H>
class BST{
private:
    Nodo<H> *root;

    void _inorder(Nodo<H> *r, ofstream &out){
        if(r){
            _inorder(r->getLeft(), out);
            for(int i=0; i<r->getMul(); i++)
                out << r->getKey() << " ";
            _inorder(r->getRight(), out);
        }
    }

    void _preorder(Nodo<H> *r, ofstream &out){
        if(r){
            for(int i=0; i<r->getMul(); i++)
                out << r->getKey() << " ";
            _preorder(r->getLeft(), out);
            _preorder(r->getRight(), out);
        }
    }

    void _postorder(Nodo<H> *r, ofstream &out){
        if(r){
            _postorder(r->getLeft(), out);
            _postorder(r->getRight(), out);
            for(int i=0; i<r->getMul(); i++)
                out << r->getKey() << " ";
        }
    }

    Nodo<H> *search(H x, Nodo<H> *r){
        if(r){
            if(x==r->getKey())
                return r;
            if(x<r->getKey())
                return search(x, r->getLeft());
            else 
                return search(x, r->getRight());
        }
    }

    Nodo<H> *min(Nodo<H> *r){
        if(!r || !r->getLeft())
            return r;
        else 
            return min(r->getLeft());
    }

    Nodo<H> *succ(Nodo<H> *r){
        if(r){
            if(r->getRight())
                return min(r->getRight());
            else{
                H x = r->getKey();
                do{
                    r = r->getParent();
                }while(r && x>r->getKey());

                if(r)
                    return r;
                return NULL;
            }
        }
    }

    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = search(x, r);

        if(tmp->getMul()==1){
            if(tmp->getLeft() && tmp->getRight()){
                Nodo<H> *s = succ(tmp);
                tmp->setKey(s->getKey());
                tmp->setMul(s->getMul());
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
            delete tmp;
        }
        else 
            tmp->decMul();
    }
public:
    BST(){root = NULL;}

    BST<H> *add(H x){
        Nodo<H> *nuovo = new Nodo<H>(x);
        Nodo<H> *tmp = root;
        Nodo<H> *pre = NULL;

        while(tmp){
            pre = tmp;
            if(x<tmp->getKey()){
                tmp = tmp->getLeft();
            }
            else if(x>tmp->getKey())
                tmp = tmp->getRight();
            else if(x==tmp->getKey()){
                tmp->incMul();
                delete nuovo;
                return this;
            }
        }

        nuovo->setParent(pre);

        if(pre){
            if(x<pre->getKey())
                pre->setLeft(nuovo);
            else 
                pre->setRight(nuovo);
        }
        else 
            root = nuovo;

        return this;
    }

    void canc(H x){
        Nodo<H> *tmp = search(x, root);
        if(tmp)
            _canc(x, tmp);
    }

    void print(string stampa, ofstream &out){
        if(stampa=="inorder")
            _inorder(root, out);
        else if(stampa=="preorder")
            _preorder(root, out);
        else if(stampa=="postorder")
            _postorder(root, out);
        
        out << endl;
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
        string stampa;
            in >> stampa;
        
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
            t->print(stampa, out);
            delete t;
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
            t->print(stampa, out);
            delete t;
        }
    }

    return 0;
}