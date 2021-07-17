#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class EDD{
private:
    string s1;
    string s2;
    vector<vector<int>> matrix;
    int update=-1;
    int len1;
    int len2;
public:
    
    void assign(string a,string b){
        s1=a;
        s2=b;
        update=0;
        len1=a.size();
        len2=b.size();
    }
    
    void compdist(){
        if(update==-1){//if it is called before assign then exception
            throw "strings not found!";
        }
        if(update==1){//if it is already 1 then no need to execute again
            return;
        }
        
        
        matrix.resize(len1+1);
        
        for(int i=0;i<len1+1;i++){
            matrix[i].resize(len2+1);
        }
        
        int x,y,z;
        for(int j=0;j<len2+1;j++){//if one length is zero then no of operations is lenght of second string
            matrix[0][j]=j;
        }
        for(int i=1;i<len1+1;i++){
           matrix[i][0]=i;
           for(int j=1;j<len2+1;j++){
               x=matrix[i][j-1]+1;//if n is inserted then it is effectively value of m and n-1
               y=matrix[i-1][j]+1;//if m is removed then it is effectively m-1 and n
               if(s1[i-1]==s2[j-1]){
                  z=matrix[i-1][j-1];//if both are same then it is effectively m-1 and n-1
               }
               else{
                  z=matrix[i-1][j-1]+1;//here m is replaced by n so m-1 and n-1 (+1) 
               }
               matrix[i][j]=min(x,min(y,z));//minimum of those three
           }
        }
        update=1;
        
        return;
    }
    
    int dist(){
        
        if(update==-1){//if it is called before assign then exception
            throw "strings not found!";
        }
        if(update==0){
            compdist();
        }
        
        return matrix[len1][len2];
    }
    void table(){

        if(update==-1){//if it is called before assign then exception
            throw  "strings not found!";
        }
        if(update==0){
            compdist();
        }
        
        for(int i=1;i<len1+1;i++){
            for(int j=1;j<len2+1;j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        return;
    }
    
};

int main() {
    int Queries;
    string s,a,b;
    EDD obj;
    cin>>Queries;
    while(Queries>0){
        cin>>s;
        if(s=="assign"){
            cin>>a;
            cin>>b;
            obj.assign(a,b);
        }
        if(s=="compdist"){
            try{
                obj.compdist();   
            }
             catch(const char* msg){
                cout<<msg<<endl;
            }
            
        }
        if(s=="table"){
            try{
                obj.table();
            }
             catch(const char* msg){
                cout<<msg<<endl;
            }
        }
        if(s=="dist"){
           try{
               cout<<obj.dist()<<endl;
           }
           catch(const char* msg){
                cout<<msg<<endl;
            }
            
        }
        Queries--;
    }
    return 0;
}

