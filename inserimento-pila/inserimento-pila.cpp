//inserimento-pila by Paolo Rabbito

#include <iostream>
#include <fstream>
using namespace std;

template<class H>
class Nodo{
private:
    Nodo<H> *next;
    Nodo<H> *prev;
    H key;
public:
    Nodo(H key){
        this->key = key;
        next = NULL;
        prev = NULL;
    }

    Nodo(){
        next = NULL;
        prev = NULL;
    }

    void setNext(Nodo<H> *next){this->next = next;}
    void setPrev(Nodo<H> *prev){this->prev = prev;}

    H getKey(){return key;}
    Nodo<H> *getNext(){return next;}
    Nodo<H> *getPrev(){return prev;}
};

template<class H>
class Pila{
private:
    Nodo<H> *head;
    Nodo<H> *tail;
public:
    Pila(){
        head = new Nodo<H>();
        tail = new Nodo<H>();
        head->setNext(tail);
        tail->setPrev(head);
    }

    void push(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);

        if(head->getNext()!=tail){
            Nodo<H> *tmp = tail;
            tmp = tmp->getPrev();
            tmp->setNext(nuovo);
            nuovo->setNext(tail);
            tail->setPrev(nuovo);
            nuovo->setPrev(tmp);
        }

        else{
            head->setNext(nuovo);
            tail->setPrev(nuovo);
            nuovo->setPrev(head);
            nuovo->setNext(tail);
        }
    }

    void print(ofstream &out){
        Nodo<H> *tmp = tail->getPrev();
        while(tmp!=head){
            out << tmp->getKey() << " ";
            tmp = tmp->getPrev();
        }
        out << endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i=0; i<100; i++){
        int n;
        string tipo;
        in >> tipo;
        in >> n;
        cout << tipo << endl;
        if(tipo=="int"){
            Pila<int> *x = new Pila<int>();
            for(int j=0; j<n; j++){
                int k;
                in >> k;
                x->push(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="double"){
            Pila<double> *x = new Pila<double>();
            for(int j=0; j<n; j++){
                double k;
                in >> k;
                x->push(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="char"){
            Pila<char> *x = new Pila<char>();
            for(int j=0; j<n; j++){
                char k;
                in >> k;
                x->push(k);
            }
            x->print(out);
            delete x;
        }

        if(tipo=="bool"){
            Pila<bool> *x = new Pila<bool>();
            for(int j=0; j<n; j++){
                bool k;
                in >> k;
                x->push(k);
            }
            x->print(out);
            delete x;
        }
    }

    return 0;
}