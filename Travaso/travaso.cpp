#include <iostream>
#include<fstream>
using namespace std;

template<class H>
class Nodo{
private: 
    Nodo<H> *next, *prev;
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
    void setKey(H key){this->key = key;}
    void setNext(Nodo<H> *next){this->next = next;}
    void setPrev(Nodo<H> *prev){this->prev = prev;}

    H getKey(){return key;}
    Nodo<H> *getNext(){return next;}
    Nodo<H> *getPrev(){return prev;}
};

template<class H>
class Coda{
private:
    Nodo<H> *head;
public:
    Coda(){head = NULL;}

    void enqueue(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);
        if(!head)
            head = nuovo;
        else{
            Nodo<H> *tmp = head;
            while(tmp->getNext())
                tmp = tmp->getNext();
            tmp->setNext(nuovo);
        }
    }

    void dequeue(){
        if(head){
            Nodo<H> *tmp = head;
            head = head->getNext();
            delete tmp;
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

template<class H>
class Pila{
private:
    Nodo<H> *head, *tail;
public:
    Pila(){
        head = new Nodo<H>();
        tail = new Nodo<H>();
        head->setNext(tail);
        tail->setPrev(head);
    }

    void push(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);
        if(head->getNext()==tail){
            head->setNext(nuovo);
            nuovo->setPrev(head);
            tail->setPrev(nuovo);
            nuovo->setNext(tail);
        }

        else{
            Nodo<H> *tmp = head->getNext();
            while(tmp->getNext()!=tail){
                tmp = tmp->getNext();
            }
            tmp->setNext(nuovo);
            nuovo->setPrev(tmp);
            tail->setPrev(nuovo);
            nuovo->setNext(tail);
        }
    }

    void pop(){
         Nodo<H> *tmp = tail->getPrev();
        tmp->getPrev()->setNext(tail);
        tail->setPrev(tmp->getPrev());
        delete tmp;
    }

    void print(ofstream &out){
        Nodo<H> *tmp = tail->getPrev();
        while(tmp!=head){
            out << tmp->getKey() << " ";
            tmp = tmp->getPrev();
        }
        out << endl;
    }

    void travasa(Coda<H> *x){
        Nodo<H> *tmp = tail->getPrev();
        while(tmp!=head){
            x->enqueue(tmp->getKey());
            tmp = tmp->getPrev();
            this->pop();
        }
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
            Coda<int> *c = new Coda<int>();
            Pila<int> *p = new Pila<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                    
                if(obj=="pop")
                    p->pop();
                if(obj=="dequeue")
                    c->dequeue();
                if(obj=="travasa")
                    p->travasa(c);
                if(obj[0]=='e'){
                    obj = obj.substr(2, obj.length()-2);
                    int x = stoi(obj);
                    c->enqueue(x);
                }
                if(obj[0]=='p' && obj[1]==':'){
                    obj = obj.substr(2, obj.length()-2);
                    int x = stoi(obj);
                    p->push(x);
                }
            }
            c->print(out);
            delete c;
            delete p;
        }

        if(tipo=="double"){
            Coda<double> *c = new Coda<double>();
            Pila<double> *p = new Pila<double>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj=="pop")
                    p->pop();
                if(obj=="dequeue")
                    c->dequeue();
                if(obj=="travasa")
                    p->travasa(c);
                if(obj[0]=='e'){
                    obj = obj.substr(2, obj.length()-2);
                    double x = stod(obj);
                    c->enqueue(x);
                }
                if(obj[0]=='p' && obj[1]==':'){
                    obj = obj.substr(2, obj.length()-2);
                    double x = stod(obj);
                    p->push(x);
                }
                
            }
            c->print(out);
            delete c;
            delete p;
        }

        if(tipo=="bool"){
            Coda<int> *c = new Coda<int>();
            Pila<int> *p = new Pila<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj=="pop")
                    p->pop();
                if(obj=="dequeue")
                    c->dequeue();
                if(obj=="travasa")
                    p->travasa(c);
                if(obj[0]=='e'){
                    obj = obj.substr(2, obj.length()-2);
                    int x = stoi(obj);
                    c->enqueue(x);
                }
                if(obj[0]=='p' && obj[1]==':'){
                    obj = obj.substr(2, obj.length()-2);
                    int x = stoi(obj);
                    p->push(x);
                }
            }
            c->print(out);
            delete c;
            delete p;
        }

        if(tipo=="char"){
            Coda<char> *c = new Coda<char>();
            Pila<char> *p = new Pila<char>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj=="pop")
                    p->pop();
                if(obj=="dequeue")
                    c->dequeue();
                if(obj=="travasa")
                    p->travasa(c);
                if(obj[0]=='e'){
                    char x = obj[2];
                    c->enqueue(x);
                }
                if(obj[0]=='p' && obj[1]==':'){
                    char x = obj[2];
                    p->push(x);
                }
            }
            c->print(out);
            delete c;
            delete p;
        }
    }
    return 0;
}