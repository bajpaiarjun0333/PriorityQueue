#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class PriorityQueue{
    public:
    vector<pair<string, int>> arr;
    int size=-1;
    PriorityQueue(){
        arr.resize(30);
    }

    //index of the parent
    int parent(int i){
        return (i-1)/2;
    }

    //index of left child
    int leftChild(int i){
        return 2*i+1;
    }
    
    //index of right child
    int rightChild(int i){
        return 2*i+2;
    }

    //function to print the status of the priority queue
    void printStatus(){
        //first sort and then print it
        if(size<0){
            cout<<-1<<endl;
            return;
        }
        int temp_size=size;
        for(int i=0;i<=temp_size;i++){
            pair<string, int> ans=del();
            cout<<ans.second<<" "<<ans.first<<endl;
        }
        size=temp_size;
        reverse(arr.begin(),arr.begin()+size+1);
    }

    //function to check if element is in correct position after delete or not
    void moveDown(int i){
        //we need to find correct place for i
        int index=i;
        int left_index=leftChild(i);
        int right_index=rightChild(i);
        int priority=arr[i].second;
        if(left_index<=size && arr[left_index].second<priority){
            index=left_index;
            priority=arr[left_index].second;
        }
        if(right_index<=size && arr[right_index].second<priority){
            index=right_index;
        }
        if(index!=i){
            swap(arr[i],arr[index]);
            moveDown(index);
        }
    }

    //function to refix the heap property
    void moveUp(int i){
        while(i>0 && arr[parent(i)].second>arr[i].second){
            swap(arr[i],arr[parent(i)]);
            i=parent(i);
        }
    }

    pair<string, int> del(){
        if(size<0){
            //cout<<-1<<endl;
            return make_pair("-1",0);
        }
        //cout<<arr[0].first<<endl;
        pair<string, int> p=arr[0];
        swap(arr[0],arr[size]);
        size=size-1;
        if(size>0){
            moveDown(0);    
        }
        return p;
    }

    void printMax(){
        if(size<0){
            cout<<-1<<endl;
        }
        cout<<arr[0].first<<endl;
    }

    void insert(string val, int priority){
        size=size+1;
        if(size<30){
            //insert at any position then float up or down
            arr[size]=make_pair(val, priority);
            moveUp(size);
        }else{
            cout<<"Capacity exhausted"<<endl;
        }
    }  
};


int main() {
    //priority queue - using min heap
    PriorityQueue q;
    int input;
    cin>>input;
    string val;
    int priority;
    while(input!=5){
        if(input==1){
            cin>>val>>priority;
            q.insert(val,priority);
        }else if(input==2){
            cout<<q.del().first<<endl;
        }else if(input==3){
            q.printStatus();
        }else if(input==4){
            q.printMax();
        }
        cin>>input;
    }
    return 0;
}
