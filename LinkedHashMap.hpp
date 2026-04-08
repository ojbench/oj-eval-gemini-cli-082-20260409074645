#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;
struct Node{
    Node* next=nullptr;
    Node* timePre=nullptr;
    Node* timeNext=nullptr;

    int key=0;
    string value;
};

struct Data{
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap{
public:
    int len;
    Node** array;
    Node* beg;
    Node* current;
    vector<Data> (*forEachMethod)(const LinkedHashMap&);

    LinkedHashMap(int _len_,bool forEachByTime){
        len=_len_;
        beg=new Node();
        current=beg;
        array=new Node*[len];
        for(int i=0;i<len;i++)
            array[i]=nullptr;
        if(forEachByTime)
            forEachMethod=traverseByTime;
        else
            forEachMethod=traverseByIndex;
    }

    ~LinkedHashMap(){
        for(int i=0;i<len;i++){
            Node* p = array[i];
            while(p){
                Node* tmp = p;
                p = p->next;
                delete tmp;
            }
        }
        delete beg;
        delete[] array;
    }

    void insert(int key,string value){
        Node* p = new Node();
        p->key = key;
        p->value = value;
        
        p->next = array[key];
        array[key] = p;
        
        current->timeNext = p;
        p->timePre = current;
        current = p;
    }

    void remove(int key,string value){
        Node* p = array[key];
        Node* pre = nullptr;
        while(p){
            if(p->value == value){
                if(pre) pre->next = p->next;
                else array[key] = p->next;
                
                p->timePre->timeNext = p->timeNext;
                if(p->timeNext) p->timeNext->timePre = p->timePre;
                else current = p->timePre;
                
                delete p;
                return;
            }
            pre = p;
            p = p->next;
        }
    }

    vector<string> ask(int key)const{
        vector<string> res;
        Node* p = array[key];
        while(p){
            res.push_back(p->value);
            p = p->next;
        }
        return res;
    }

    vector<Data> forEach()const{
        return forEachMethod(*this);
    }
};

vector<Data> traverseByTime(const LinkedHashMap& obj){
    vector<Data> res;
    Node* p = obj.beg->timeNext;
    while(p){
        Data d;
        d.key = p->key;
        d.value = p->value;
        res.push_back(d);
        p = p->timeNext;
    }
    return res;
}

vector<Data> traverseByIndex(const LinkedHashMap& obj){
    vector<Data> res;
    for(int i=0;i<obj.len;i++){
        Node* p = obj.array[i];
        while(p){
            Data d;
            d.key = p->key;
            d.value = p->value;
            res.push_back(d);
            p = p->next;
        }
    }
    return res;
}

#endif //FINAL_SRC_HPP
