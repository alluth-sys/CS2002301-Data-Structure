//Problem: Priority Queue using Binary Heap
#include<iostream>
#include <utility> 
#include<vector>
#include<sstream>
using namespace std;
typedef pair<char,int> priority;

class MinHeap{
    private:
    vector<pair<char,int>> hvec;
    public: 
        int parent(int i) { return (i-1)/2; } //parent index
        int left(int i) { return (2*i + 1); } //left child index
        int right(int i) { return (2*i + 2); } //right child index
        void insertKey(priority key);
        void deleteKey(priority key);
        priority extractMin();
        void deleteKey(); 
        void MinHeapify(int i);
        int getHvecSize(){ return hvec.size();}

};
void MinHeap::deleteKey() 
{ 
    priority deletedNode = extractMin();
    cout << deletedNode.first;
} 

void MinHeap::MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < hvec.size() && hvec[l].second < hvec[i].second) 
        smallest = l; 
    if (r < hvec.size() && hvec[r].second < hvec[smallest].second) 
        smallest = r; 
    if (smallest != i) 
    { 
        priority temp;
        temp = hvec[i];
        hvec[i] = hvec[smallest];
        hvec[smallest] = temp;
        MinHeapify(smallest); 
    } 
} 

priority MinHeap::extractMin(){
    if (hvec.size() == 1) 
    {  
        hvec.pop_back();
        return hvec[0]; 
    } 
    priority root = hvec[0]; 
    hvec[0] = hvec[hvec.size()-1];
    hvec.pop_back();
    MinHeapify(0); 
    return root;
}

void MinHeap::insertKey(priority key){
    hvec.push_back(key);
    int i = hvec.size()-1;
    while(i != 0 && hvec[parent(i)].second > hvec[i].second){
        priority temp;
        temp = hvec[parent(i)];
        hvec[parent(i)] = hvec[i];
        hvec[i] = temp;
        i = parent(i);
    }
}

int main(){
    vector<priority> priorityQueue;
    MinHeap PQBH;
    string input;

    //process input
    getline(cin,input);
    stringstream inputss(input);
    while(getline(inputss,input,';')){
        stringstream ss(input);
        char element;
        int order;
        while(ss >> element >> order){
            priority temp;
            temp.first = element;
            temp.second = order;
            priorityQueue.push_back(temp);
        }
    }

    //insert key into MinHeap
    for(int i=0;i<priorityQueue.size();i++){
        PQBH.insertKey(priorityQueue[i]);
    }

    while(PQBH.getHvecSize()!=0){
        PQBH.deleteKey();
    }
}
