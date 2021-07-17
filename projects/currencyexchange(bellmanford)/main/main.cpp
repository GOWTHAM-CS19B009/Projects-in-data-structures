#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;

class coloursAndCurrencies
{
    private:
    int numCurrencies;
    int numColor;
    vector<int> colorCurrencies;
    vector<vector<int>> color;
    vector<vector<int>> currencies;
    vector<pair<double,pair<int,int>>> currenciesArray;
    bool increasingWeightCycle=false;
    public:
    void createColorMatrix(int C){//initializing the colour matrix with rows=coloumns=C;
        color.resize(C);
        numColor=C;
        for(int i=0;i<C;i++){
            color[i].resize(C);
        }
        for(int i=0;i<C;i++){//The colour matrix is used to tell whether two currencies can be exchanged or not(directly or indirectly)
            for(int j=0;j<C;j++){
                if(i==j){
                    color[i][j]=1;
                }
                else{
                    color[i][j]=0;
                }
            }
        }
    }
    
    void addEdgeColorMatrix(int a,int b){//if a,b are given it means they can be used to exchange so the value is 1
        color[a][b]=1;
        color[b][a]=1;
    }
    
    void updateColorCurrencies(int x){//updating the colour of each bag inintially
        int size=colorCurrencies.size();
        colorCurrencies.resize(size+1);
        colorCurrencies[size]=x;
    }
    
    void createCurrencyMatrix(int N){//create an adjacency matrix for each currencies,we make an edge if their is an direct transition possible.
        currencies.resize(N);
        for(int i=0;i<N;i++){
            currencies[i].resize(N);
        }
        numCurrencies=N;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                currencies[i][j]=INT_MAX;
            }
        }
    }
    
    void updateCurrencyMatrix(double rate,int i,int j){//updating the currency matrix and the array we store w.r.t the edges
        if(color[colorCurrencies[i]][colorCurrencies[j]]==1){
            currencies[i][j]=rate;
            int size=currenciesArray.size();
            currenciesArray.resize(size+1);
            currenciesArray[size].first=rate;
            currenciesArray[size].second.first=i;
            currenciesArray[size].second.second=j;
        }
    }
    
    double findTransferRate(int source,int destination){//finding the transfer rate such that we have maximum transaction currency.
        vector<double> cost;
        cost.resize(numCurrencies);//initially every vertex have a minimum transaction rate i.e, INT_MIN and source has one as the transaction rate with itself
        for(int i=0;i<numCurrencies;i++){
            cost[i]=INT_MIN;
        }
        cost[source]=1;
        //Example of Bellman-Ford Algorithm(some improvisation).
        for(int i=1;i<numCurrencies;i++){//here we are finding the transaction rate from the source we are making |v|-1 loops because in the worst case we have |v|-1 edges.between source vertex and destination.
            for(int j=0;j<currenciesArray.size();j++){
                float finalCost=currenciesArray[j].first;
               int x=currenciesArray[j].second.first;
               int y=currenciesArray[j].second.second;
                if(cost[x]!=INT_MIN&&cost[x]*finalCost>cost[y]){
                    cost[y]=cost[x]*finalCost;
                }
            }
        }//so after |v|-1 loops even if we are having mor eloop it is no use s
        for(int j=0;j<currenciesArray.size();j++){
            float finalCost=currenciesArray[j].first;
            int x=currenciesArray[j].second.first;
            int y=currenciesArray[j].second.second;
            if(cost[x]!=INT_MIN&&cost[x]*finalCost>cost[y]){
                increasingWeightCycle=true;
            }
        }//so here if we have transaction of x and y in between if we have more than 1 we can say that by repeated transactions we can increase the value and make it infinite

        return cost[destination];
    }
    
    void findFinalRate(int p,int q,int r){
        increasingWeightCycle=false;
        double answer=findTransferRate(p,q);
        
        if(answer==INT_MIN){//if our answer is INT_MIN we can say that the transaction from source to destinatioin is not possible
            cout<<"-1"<<endl;
            return;
        }
        
        if(increasingWeightCycle){//if we find a cycle of the above type return INF(infinity).
            cout<<"INF"<<endl;
            return;
        }
        //else return the value.
        cout<<fixed<<setprecision(3)<<answer*r<<endl;
        return;
        
    }
    
    
    
};
int main(){
    
    coloursAndCurrencies CAC;
    
    int C;
    cin>>C;
    int m;
    cin>>m;
    int a,b;
    double rate;
    vector<int> colour;
    CAC.createColorMatrix(C);
    for(int i=0;i<m;i++){
        cin>>a>>b;
        CAC.addEdgeColorMatrix(a,b);
    }
    int N;
    cin>>N;
    CAC.createCurrencyMatrix(N);
    int x;
    for(int i=0;i<N;i++){
        cin>>x;
        CAC.updateColorCurrencies(x);
    }
    
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>rate;
            CAC.updateCurrencyMatrix(rate,i,j);
        }
    }
    int Queries;
    cin>>Queries;
    int p,q,r;
    while(Queries>0){
        cin>>p>>q>>r;
        CAC.findFinalRate(p,q,r);
        Queries--;
    }
    return 0;
}
