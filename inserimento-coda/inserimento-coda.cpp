//Inserimento-coda by Paolo Rabbito

#include <iostream>
#include <fstream>
using namespace std;

template<class H>
class Nodo{
private:
    H key;
    Nodo<H> *next;
public:
    Nodo(H key){
        this->key = key;
        next =  NULL;
    }

    H getKey(){return key;}
    Nodo<H> *getNext(){return next;}

    void setNext(Nodo<H> *next){this->next = next;}
};

template<class H>
class Coda{
private:
    Nodo<H> *head;
public:
    Coda(){
        head = NULL;
    }

    void add(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);

        if(head){
            Nodo<H> *tmp = head;
            while(tmp->getNext()){
                tmp = tmp->getNext();
            }

            tmp->setNext(nuovo);
        }

        else{
            head = nuovo;
        }
    }

    void print(ofstream &out){
        Nodo<H> *tmp = head;
        while(tmp){
            out << tmp->getKey() << " ";
            tmp = tmp->getNext();
        }
        out << endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i=0; i<100; i++){
        string tipo;
        in >> tipo;
        int n;
        in >> n;
        cout << tipo << endl;
        if(tipo=="int"){
            Coda<int> *x = new Coda<int>();
            for(int j=0; j<n; j++){
                int k;
                in >> k;
                x->add(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="double"){
            Coda<double> *x = new Coda<double>();
            for(int j=0; j<n; j++){
                double k;
                in >> k;
                x->add(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="char"){
            Coda<char> *x = new Coda<char>();
            for(int j=0; j<n; j++){
                char k;
                in >> k;
                x->add(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="bool"){
            Coda<bool> *x = new Coda<bool>();
            for(int j=0; j<n; j++){
                bool k;
                in >> k;
                x->add(k);
            }
            x->print(out);
            delete x;
        }
    }

    return 0;
}