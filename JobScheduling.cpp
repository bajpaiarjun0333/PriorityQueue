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
    
    //function to delete the max element

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
    
    //funtion to print the maximum value of the queue

    void printMax(){
        if(size<0){
            cout<<-1<<endl;
        }
        cout<<arr[0].first<<endl;
    }
    
    //funtion to insert the element in the queue

    void push(string val, int priority){
        size=size+1;
        if(size<30){
            //insert at any position then float up or down
            arr[size]=make_pair(val, priority);
            moveUp(size);
        }else{
            cout<<"Capacity exhausted"<<endl;
        }
    }
    
    //function whether queue is empty or not
    
    bool empty(){
        if(size==-1){
            return true;
        }
        return false;
    }
    
    //function returning the top element of the queue
    
    pair<string, int> top(){
        return arr[0];
    }
};

class Graph{
    public:
    
    //implementing graph as an adjacency list
    
    unordered_map<string, list<pair<string, int>>> adj;
    unordered_map<string, int> nodeWeight;
    
    
    int shortest(string source, int vertex, vector<string> nodes, string target){
        unordered_map<string, int> dist;
        
        //initializing all distances
        
        for(auto i:nodes){
            dist[i]=INT_MAX;
        }
        
        dist[source]=0;
        
        //instantiating the class priority queue
        
        PriorityQueue q;
        
        q.push(source,0);
       while(!q.empty()){
            pair<string, int> p=q.top();
            q.del();
            for(auto i: adj[p.first]){
              string node=i.first;
              int edge=i.second;
                if(dist[node]>dist[p.first]+nodeWeight[p.first]+edge){
                  dist[node]=dist[p.first]+nodeWeight[p.first]+edge;
                    q.push(node, dist[node]);
               }
            }
       }
      return dist[target];
    }
    
    //handling the input and also calling the shortest function function to generate the output
    void takeInput(){
        int vertex;
        int w, x, d;
        string u,v;
        string target;
        vector<string> sources; 
        cin>>vertex;
        vector<string> nodes;
        
        //taking inputs from the console
        
        for(int i=0;i<vertex;i++){
            cin>>v>>x>>d;
            nodes.push_back(v);
            nodeWeight[v]=x;
            if(d==0){
                sources.push_back(v);
            }
            for(int j=0;j<d;j++){
                cin>>u>>w;
                adj[u].push_back(make_pair(v,w));
            }
        }
        cin>>target;
        
        //to check which source gives the minimum time
        
        int mini=INT_MAX;
        for(auto s:sources){
            mini=min(mini,shortest(s,vertex,nodes,target));
        }
        cout<<mini+nodeWeight[target]<<endl;
    }
    
};



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Graph g;
    g.takeInput();
    
    return 0;
}
