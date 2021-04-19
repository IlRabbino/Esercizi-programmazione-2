#include <iostream>
#include <fstream>
using namespace std;

template<class H>
class Nodo{
private:
    H key;
    Nodo<H> *next, *prev;
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

    H getKey(){return key;}
    Nodo<H> *getNext(){return next;}
    Nodo<H> *getPrev(){return prev;}

    void setKey(H key){this->key=key;}
    void setNext(Nodo<H> *next){this->next = next;}
    void setPrev(Nodo<H> *prev){this->prev = prev;}
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

    void push(Nodo<H> *nuovo){
        if(head->getNext()==tail){
            head->setNext(nuovo);
            tail->setPrev(nuovo);
            nuovo->setPrev(head);
            nuovo->setNext(tail);
        }

        else{
            Nodo<H> *tmp = head->getNext();
            while(tmp->getNext()!=tail){
                tmp = tmp->getNext();
            }
            tmp->setNext(nuovo);
            tail->setPrev(nuovo);
            nuovo->setNext(tail);
            nuovo->setPrev(tmp);
        }
    }

    Nodo<H> *pop(){
        if(head->getNext()!=tail){
            Nodo<H> *tmp = tail->getPrev();
            Nodo<H> *p = tmp->getPrev();
            p->setNext(tail);
            tail->setPrev(p);
            return tmp;
        }
    }

    bool isEmpty(){
        if(head->getNext()!=tail)
            return false;
        return true;
    }
};

template<class H>
class Coda{
private:
    Pila<H> *inbox, *outbox;
public:
    Coda(){
        inbox = new Pila<H>();
        outbox = new Pila<H>();
    }

    void enqueue(H x){
        Nodo<H> *nuovo = new Nodo<H>(x);
        inbox->push(nuovo);
    }

    void dequeue(){
        if(outbox->isEmpty()){
            while(!inbox->isEmpty()){
                outbox->push(inbox->pop());
            }
        }
        delete outbox->pop();
        while(!outbox->isEmpty())
            inbox->push(outbox->pop());
    }

    void print(ofstream &out){
        if(outbox->isEmpty()){
            while(!inbox->isEmpty()){
                outbox->push(inbox->pop());
            }
        }
        while(!outbox->isEmpty()){
            out << outbox->pop()->getKey() << " ";
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
            cout << tipo<< endl;
        int n;
            in >> n;
        if(tipo=="int"){
            Coda<int> *coda = new Coda<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(1, obj.length()-1);
                    int x = stoi(obj);
                    coda->enqueue(x);
                }
                else{
                    coda->dequeue();
                }
            }
            coda->print(out);
            delete coda;
        }

        if(tipo=="double"){
            Coda<double> *coda = new Coda<double>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(1, obj.length()-1);
                    double x = stod(obj);
                    coda->enqueue(x);
                }
                else{
                    coda->dequeue();
                }
            }
            coda->print(out);
            delete coda;
        }

        if(tipo=="bool"){
            Coda<int> *coda = new Coda<int>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    obj = obj.substr(1, obj.length()-1);
                    int x = stoi(obj);
                    coda->enqueue(x);
                }
                else{
                    coda->dequeue();
                }
            }
            coda->print(out);
            delete coda;
        }

        if(tipo=="char"){
            Coda<char> *coda = new Coda<char>();
            for(int j=0; j<n; j++){
                string obj;
                    in >> obj;
                if(obj[0]=='i'){
                    char x = obj[1];
                    coda->enqueue(x);
                }
                else{
                    coda->dequeue();
                }
            }
            coda->print(out);
            delete coda;
        }
    }
    return 0;
}