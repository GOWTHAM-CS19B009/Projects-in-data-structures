#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<list>
#include<queue>
#include<utility>
#include<climits>
#include<bits/stdc++.h>
using namespace std;


template <class edgeWeight> 
    class undirectedGraph{
    private:
        vector<list<pair<int,edgeWeight> > > graph;
        int noOfVertices;
        vector<int> visitedArray;
    
    public:
        void createundirectedGraph(int v){//creates an vector of type lists which is of type pair
            noOfVertices=v;
            graph.resize(v);//creating graph of size v;
            visitedArray.resize(v);//visistedArray helps to know whether a vertex v is visited or not
            for(int i=0;i<v;i++){//initially each vertex is unvisited so initialized to zero
                visitedArray[i]=0;
            }
        
    }
    
void AddV(){
    
    noOfVertices++;//increasing count os noOfVertices
    graph.resize(noOfVertices);//resizing the graph
    visitedArray.resize(noOfVertices);//resizing the visited array
    visitedArray[noOfVertices-1]=0;//new vertex is unvisite so initialized to zero
    }

void AddE(int a,int b,edgeWeight w){
   if(a>=noOfVertices||b>=noOfVertices){//if a (or) b is greater than number of vertices then an error message is printed to error stream using "cerr" 
   cerr<<"!!!WRONGINPUT!!!"<<endl;
   return;
   }
   
   
      pair<int,edgeWeight> p1;
      pair<int,edgeWeight> p2;
      pair<int,edgeWeight> P;
      p1.first=b;
      p1.second=w;
      p2.first=a;
      p2.second=w;
       auto i=graph[a].begin();
      while(i!=graph[a].end()){//here we sort the list while taking the input according to the given conditions
        P=*i;
        if(p1.second>P.second){
        i++;
        }
        else if(p1.second==P.second && p1.first>P.first){
        i++;
        }
        else{
        break;
        }
     }
     graph[a].insert(i,p1);//find the position where it is to be inserted and use the insert fnction
    
   
   i=graph[b].begin();//simillarly do the above procedure for list graph[b].
   while(i!=graph[b].end()){
       P=*i;
       if(p2.second>P.second){
        i++;
        }
        else if(p2.second==P.second && p2.first>P.first){
        i++;
        }
        else
        break;
        }
         graph[b].insert(i,p2);
   
   }



void DelE(int a,int b){

    
    
    pair<int,edgeWeight> ptr;
    
   if(a>=noOfVertices||b>=noOfVertices){//if a (or) b is greater than number of vertices
           cerr<<"!!!WRONG INPUT!!!"<<endl;
           return;
       }
    int count=0;
    for(pair<int,edgeWeight>&P : graph[a]){//here we use count to find if there is b present in list graph[a] or not
        if(P.first==b){
            count++;
        }
    }
    if(count!=1){//if it is not present the we return error message to error stream
        cerr<<"!!!WRONG INPUT!!!"<<endl;
        return;
    }
    for(pair<int,edgeWeight>&P : graph[b]){//traverse through list graph[b] to find a and delete it
                
                if(P.first==a){
                graph[b].remove(P);
                break;
                }
          } 
     for(pair<int,edgeWeight>&P : graph[a]){//traversethrough list graph[a] to find b and delete it
         if(P.first==b){
             graph[a].remove(P);
             break;
         }
     }     
        
        
        
         
    

}

void BFS(int a){
 for(int i=0;i<noOfVertices;i++){//initiall every vertex is unvisited
 visitedArray[i]=0;
 }
 queue<int> Q;
 Q.push(a);
 visitedArray[a]=1;//put the given vertex in the queue and make it visited  
  int v;
 pair<int,edgeWeight> ptr;
 while(!Q.empty()){//while queue is not empty 
  v=Q.front();
  Q.pop();//pop the first vertex and 
  cout<<v<<" ";
  
 
  
  for(pair<int,edgeWeight>&ptr : graph[v]){
  //push the elements in the adjacency list and not visisted into the queue 
   v=ptr.first;
  
   if(visitedArray[v]==0){
     visitedArray[v]=1;
      Q.push(v);
    }
  }
 }
 cout<<endl;
}

vector<edgeWeight> SSP(int a){
 vector<edgeWeight> shrtstDist;
 priority_queue<pair<edgeWeight,int>> pQueue;
 shrtstDist.resize(noOfVertices);
 for(int i=0;i<noOfVertices;i++){//initially except a all vertices have dist=INT_MAX
  if(i!=a){
  shrtstDist[i]=INT_MAX;
  }
  else{
  shrtstDist[i]=0;
  }
 }
 pair<edgeWeight,int> P;
 P.first=shrtstDist[a];
 P.second=a;//push into the priority queue the vertex
 pQueue.push(P);
 
 while(!pQueue.empty()){//while priority queue is not empty
 P=pQueue.top();//pop the vertex and update the values of adjacent elements and push into the priority queue
 int v=P.second;
 pQueue.pop();
 for(pair<int,edgeWeight>&i : graph[v]){//condition for updating the distance value
 //d[x]>d[u]+w(u,x) then update
  if(shrtstDist[i.first]>shrtstDist[v]+i.second){
  shrtstDist[i.first]=shrtstDist[v]+i.second;
  P.first=shrtstDist[i.first];
  P.second=i.first;
  pQueue.push(P);
  
  }
 }
 }
 
 return shrtstDist;
}


};



int main() {
    int v;
    cin>>v;
    undirectedGraph<int> G;
    G.createundirectedGraph(v);
    int Queries;
    cin>>Queries;
    string s;
    int a,b,w;
    
    
    while(Queries>0){
        cin>>s;
        if(s=="ADDE"){
            cin>>a;
            cin>>b;
            cin>>w;
            G.AddE(a,b,w);
        }
        if(s=="ADDV"){
            G.AddV();
        }
        if(s=="DELE"){
            cin>>a>>b;
            G.DelE(a,b);
        }
        Queries--;
    }
    for(int i=0;i<2;i++){
        cin>>s;
        if(s=="BFS"){
            cin>>a;
            G.BFS(a);
            
        }
        if(s=="SSP"){
            cin>>b;
            vector<int> arr;
        
            arr=G.SSP(b);
            for(int i=0;i<int(arr.size());i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
    }
    
    return 0;
}

