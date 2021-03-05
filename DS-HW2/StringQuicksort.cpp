#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void swap(vector<string>& ARR,int LOC, int toBeSwaped){
    string temp;
    temp = ARR[toBeSwaped];
    ARR[toBeSwaped] = ARR[LOC];
    ARR[LOC] = temp;
}

int partition(vector<string>& ARR,int BEG,int END){
    //initialize step
    int links = BEG;
    int rechts = END;
    int loc = BEG;
    int flag = 0;

    while(flag == 0){
        while(ARR[loc]<= ARR[rechts] && loc != rechts){
            rechts --;
        }
        if(loc == rechts){
            flag = 1;
        }
        else if(ARR[loc] > ARR[rechts]){
            swap(ARR,loc,rechts);
            loc = rechts;
        }

        if(flag == 0){
             while(ARR[loc] >= ARR[links] && loc != links){
                links++;
            }
            if(loc == links){
                flag = 1;
            }
            else if(ARR[loc] < ARR[links]){
                swap(ARR,loc,links);
                loc = links;
            }
        }
    }
    return loc;
}

void quicksort(vector<string>& ARR,int BEG,int END){
    if(BEG < END){
        int location = partition(ARR,BEG,END);
        quicksort(ARR,BEG,location-1);
        quicksort(ARR,location+1,END);
    }
}

void printSortedList(vector<string>& ARR){
    for(int i=0;i<ARR.size();i++){
        if(i==ARR.size()-1){
            cout << ARR[i];
        }
        else{
            cout << ARR[i] << " ";
        }
    }
}
  

int main(){
    string input;
    vector<string> data;

    //input
    getline(cin,input);
    stringstream ss(input);
    while(ss >> input){
        data.push_back(input);
    }
    quicksort(data,0,data.size()-1);
    printSortedList(data);
    
}
