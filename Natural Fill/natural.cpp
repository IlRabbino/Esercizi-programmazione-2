#include <iostream>
#include <fstream>
using namespace std;

template<class H>
class Nodo{
private:
    Nodo<H> *left, *right, *parent;
    H key;
public:
    Nodo(H key){
        this->key = key;
        left = right = parent = NULL;
    }

    void setKey(H key){this->key = key;}
    void setLeft(Nodo<H> *left){this->left =left;}
    void setRight(Nodo<H> *right){this->right = right;}
    void setParent(Nodo<H> *parent){this->parent = parent;}

    H getKey(){return key;}
    Nodo<H> *getLeft() {return left;}
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
                }while (r && x>r->getKey());
                
                if(r)
                    return r;
                return NULL; 
            }
        }
    }

    void _canc(H x, Nodo<H> *r){
        Nodo<H> *tmp = search(x, r);

        if(tmp->getLeft() && tmp->getRight()){
            Nodo<H> *s = succ(tmp);
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

    void inorder_fill(H *array, int &i, Nodo<H> *r){
        if(r){
            inorder_fill(array, i, r->getLeft());
            r->setKey(array[i]);
            i++;
            inorder_fill(array, i, r->getRight());
        }
    }

    void _postorder(Nodo<H> *r, ofstream &out){
        if(r){
            _postorder(r->getLeft(), out);
            _postorder(r->getRight(), out);
            out << r->getKey() << " ";
        }
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

        if(pre){
            if(x<=pre->getKey())
                pre->setLeft(nuovo);
            else 
                pre->setRight(nuovo);
        }
        else 
            root = nuovo;
    }

    void canc(H x){
        Nodo<H> *tmp = search(x, root);
        if(tmp)
            _canc(x, tmp);
    }

    void NaturalFill(H *array, int &i){
        inorder_fill(array, i, root);
    }

    void print(ofstream &out){
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
        
        if(tipo=="int"){
            BST<int> *t = new BST<int>();
            int array[n];

            for(int j=0; j<n; j++){
                int x;
                    in >> x;
                t->add(x);
            }
            for(int j=0; j<n; j++){
                int x;
                    in >> x;
                array[j] = x;
            }

            int i = 0;
            t->NaturalFill(array, i);
            t->print(out);
        }

        if(tipo=="double"){
            BST<double> *t = new BST<double>();
            double array[n];

            for(int j=0; j<n; j++){
                double x;
                    in >> x;
                t->add(x);
            }
            for(int j=0; j<n; j++){
                double x;
                    in >> x;
                array[j] = x;
            }
            int i = 0;
            t->NaturalFill(array, i);
            t->print(out);
        }
    }
    return 0;
}