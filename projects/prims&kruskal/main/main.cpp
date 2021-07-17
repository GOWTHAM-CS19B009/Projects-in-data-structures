#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<list>
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> Pair;
typedef pair<int,pair<int,int>> dPair;

    class undirectedGraph{
    protected:
        vector<list<Pair>> graph;
        int noOfVertices;
        int condition;
        
    
    public:
        void createundirectedGraph(int v){//creates an vector of type lists which is of type pair
            noOfVertices=v;
            graph.resize(v);//creating graph of size v;
            condition=0;
    }
    
void AddV(){
    
    noOfVertices++;//increasing count os noOfVertices
    graph.resize(noOfVertices);//resizing the graph
    condition=0;
    }

void AddE(int a,int b,int w){
   if(a>=noOfVertices||b>=noOfVertices){//if a (or) b is greater than number of vertices then an error message is printed to error stream using "cerr" 
   cerr<<"!!!WRONGINPUT!!!"<<endl;
   return;
   }
   
   
      Pair p1;
      Pair p2;
      Pair P;
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
        condition=0;
   }



void DelE(int a,int b){

    
    
    Pair ptr;
    
   if(a>=noOfVertices||b>=noOfVertices){//if a (or) b is greater than number of vertices
           cerr<<"!!!WRONG INPUT!!!"<<endl;
           return;
       }
    int count=0;
    for(pair<int,int>&P : graph[a]){//here we use count to find if there is b present in list graph[a] or not
        if(P.first==b){
            count++;
        }
    }
    if(count!=1){//if it is not present the we return error message to error stream
        cerr<<"!!!WRONG INPUT!!!"<<endl;
        return;
    }
    condition=0;
    for(Pair&P : graph[b]){//traverse through list graph[b] to find a and delete it
                
                if(P.first==a){
                graph[b].remove(P);
                break;
                }
          } 
     for(Pair&P : graph[a]){//traversethrough list graph[a] to find b and delete it
         if(P.first==b){
             graph[a].remove(P);
             break;
         }
     }     
}


};


class MST : public undirectedGraph{
    private:
    vector<list<Pair>> variableTree;
    int numVertices;
    vector<int> parentArr;
    public:
void createTree(int v){//creates a tree of size number of vertices
    variableTree.resize(v);
    numVertices=v;
    }
    
void addEdgeInTree(int u,int v,int w){//function to add the edges into the tree
        Pair P;
        P.first=v;
        P.second=w;
        variableTree[u].push_back(P);
        P.first=u;
        variableTree[v].push_back(P);
    }
    
int Prims(int v){
    if(v>=noOfVertices){
        throw "!!!Enter a valid vertex!!!";
    }
    for(int i=0;i<numVertices;i++){
        variableTree[i].clear();
    }//first clear the old tree
    
    
    createTree(noOfVertices);//create the new empty tree of size number of vertices

    vector<int> parentArray(noOfVertices,-1);//stores the parent of the vertex
    vector<int> weightArray(noOfVertices,INT_MAX);//stores the weight of the edge between vertex and its parent
    vector<int> pushStateArray(noOfVertices,false);//checks whether the vertex is already the part of MST or not
    priority_queue<Pair,vector<Pair>,greater<Pair>> pQueue;
   
    weightArray[v]=0;
    
   pQueue.push(make_pair(weightArray[v],v));//first we push the source vertex into the priority queue
    
    
    while(!pQueue.empty()){//until the queue is empty
        int x=pQueue.top().second;//pop the element 
        pQueue.pop();
        pushStateArray[x]=true;//make it's value to true
        Pair p;
        for(auto it=graph[x].begin();it!=graph[x].end();it++){//push the elements which are not already part of MST and weight is affected by v and adjacent to v
            p=*it;
            int y=p.first;
            int w=p.second;
            if(pushStateArray[y]==false&&weightArray[y]>w){
                weightArray[y]=w;
                pQueue.push(make_pair(weightArray[y],y));
                parentArray[y]=x;
            }
        }
        }
    
        int cost=0;
    //after completion of the loop we have all weights in weightArray and parents of each vertex in parentArray
    //use weightarray to find the cost of MST    
    for(int i=0;i<noOfVertices;i++){
           cost=cost+weightArray[i];
            
        }
    
        int i=0;
    //use both the arrays to add the elements in adjacency list using addEdgeInTree function
        while(i<noOfVertices){
            if(i!=v){
                addEdgeInTree(i,parentArray[i],weightArray[i]);
            }
            i++;
        }

        condition=1;
        return cost;
    
    }
    
    
int findParent(int a){//it is used for kruskals algoirithm to find the effective parent of the vertex
        while(parentArr[a]!=a){
            a=parentArr[a];
        }
    return a;
}

void updateParent(int u,int v){//it is used to update the new points and edges and update the effective parent of the tree
        int x=findParent(u);
        int y=findParent(v);
        parentArr[x]=y;
    }
    
    
    
int Kruskal(){
    for(int i=0;i<numVertices;i++){
        variableTree[i].clear();
    }
    
    
    createTree(noOfVertices);
    int cost=0;
    
    parentArr.resize(noOfVertices);
    priority_queue<dPair,vector<dPair>,greater<dPair>> pQueue;
    Pair P;
    dPair p;
    Pair Q;
    //initially each vertex is parent of its own
    for(int i=0;i<noOfVertices;i++){
        parentArr[i]=i;
    }//bring the vertices of the graph into the priority queue
    for(int i=0;i<noOfVertices;i++){
        for(auto it=graph[i].begin();it!=graph[i].end();it++){
            P=*it;
            if(P.first>i){
                Q.first=i;
                Q.second=P.first;
                p.first=P.second;
                p.second=Q;
                pQueue.push(p);
            }
        }
    }
    while(!pQueue.empty()){//while the queue is not empty
        p=pQueue.top();
        Q=p.second;
        pQueue.pop();//pop the element check whether they have the both same effective parent or not if same then  donot add because they form a cycle else add
        if(findParent(Q.first)!=findParent(Q.second)){
            
            addEdgeInTree(Q.first,Q.second,p.first);
            cost=cost+p.first;
        }//if not same then add the edge and vertex into the tree and update the parents
        updateParent(Q.first,Q.second);
    }
    
    condition=1;
    return cost;
}    
    
void DisplayTree(){//we display the tree following the conditions given above,we add the vertices into a priority queue and pop one by one and print
    
    priority_queue<dPair,vector<dPair>,greater<dPair>> pQueue;
    Pair p,P;
    dPair Q;//first traverse through the tree and keep the elements in the graph if only the first vertex is lesser than the second vertex
    for(int i=0;i<noOfVertices;i++){
        for(auto it=variableTree[i].begin();it!=variableTree[i].end();it++){
           p=*it;
            if(p.first>i){
                P.first=i;
                P.second=p.first;
                Q.first=p.second;
                Q.second=P;
                pQueue.push(Q);
            }
        }
    }
    dPair x;
    
    while(!pQueue.empty()){//print the tree poping one by one in priority queue
        x=pQueue.top();
        pQueue.pop();
        cout<<x.second.first<<" "<<x.second.second<<" "<<x.first<<endl;
    }
    return;
}

    

void TreeUptodate(){
if(condition==0){//if we are doing any changes to the graph then we are not up do date so we take a variable "condition" and make it false ,if we rae performing any prims or kruskals then  we have tree upto date so make it true.
cout<<"NO"<<endl;
return;
}
cout<<"YES"<<endl;
}


};





int main() {
    MST tree;
    int n;
    int a,b,v,w;
    cin>>n;
    tree.createundirectedGraph(n);
    tree.createTree(0);
    int Queries;
    cin>>Queries;
    string s;
    while(Queries>0){
        cin>>s;
        if(s=="ADDV"){
            tree.AddV();
        }
        if(s=="ADDE"){
            cin>>a>>b>>w;
            tree.AddE(a,b,w);
        }
        if(s=="DELE"){
            cin>>a>>b;
            tree.DelE(a,b);
        }
        if(s=="Prims"){
            cin>>v;
            try{
                cout<<tree.Prims(v)<<endl;
            }
            catch(const char* msg){
                cerr<<msg<<endl;
            }
            
        }
        if(s=="Kruskal"){
            cout<<tree.Kruskal()<<endl;
        }
        if(s=="TreeUptodate"){
            tree.TreeUptodate();
        }
        if(s=="DisplayTree"){
            tree.DisplayTree();
        }
        
        
        Queries--;
    }
    return 0;
}

