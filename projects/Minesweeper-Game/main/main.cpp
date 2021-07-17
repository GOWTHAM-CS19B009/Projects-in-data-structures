#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<climits>
using namespace std;

class mineSweeper{
    private:
    int sizeOfGrid;
    int numberOfMines;
    bool Won_lost=false;
    bool Won=false;
    int revealed=0;
    vector<vector<int>> minesBoard;
    public:
    void createBoard(int N,int M){//Creating a minesweeper Board of size N*N with M mines.
        sizeOfGrid=N;
        numberOfMines=M;
        minesBoard.resize(sizeOfGrid);
        for(int i=0;i<sizeOfGrid;i++){
            minesBoard[i].resize(sizeOfGrid);
        }
        for(int i=0;i<sizeOfGrid;i++){//Initially every block is empty and has a value of -INT_MIN
            for(int j=0;j<sizeOfGrid;j++){
                minesBoard[i][j]=-2;
            }
        }
    }
    
    void minePosUpdate(int minePos){//Keeping the mines in respective places from main.
        minesBoard[minePos/sizeOfGrid][minePos%sizeOfGrid]=-1;
    }
    
    void reveal_Neighbours(int pos1,int pos2){//given a position (pos1,pos2)
         int neighbour_mineCount=0;
         if(minesBoard[pos1][pos2]==-1){//Find whether it has mine or not,If there is a mine present it means user lost the match,so change the conditiona appropriately.
            Won_lost=true;
            Won=false;
            return;
        }
        
        if(minesBoard[pos1][pos2]>=0){//if repeated input is given simply return the function.
            return;
        }
        
        Won_lost=false;//if not a mine then check number of neighbour mines and assign the value at [pos1][pos2].
        for(int i=pos1-1;i<=pos1+1;i++){
            for(int j=pos2-1;j<=pos2+1;j++){
                if((i>=0&&i<=sizeOfGrid-1)&&(j>=0&&j<=sizeOfGrid-1)){
                    
                        if(minesBoard[i][j]==-1){
                            neighbour_mineCount++;
                        
                    }
                }
            }
        }
        
        minesBoard[pos1][pos2]=neighbour_mineCount;
        revealed++;//increment the revealed count by 1.
        
        if(minesBoard[pos1][pos2]==0){//if there are no mines present then reveal the neighbouring mines too recursively
             for(int i=pos1-1;i<=pos1+1;i++){
                 for(int j=pos2-1;j<=pos2+1;j++){
                     if((i>=0&&i<=sizeOfGrid-1)&&(j>=0&&j<=sizeOfGrid-1)){
                         
                             reveal_Neighbours(i,j);
                        
                     }
                 }
             }
        }
        //now check the revealed blocks are completed then change the conditions accordingly.
        if(revealed==sizeOfGrid*sizeOfGrid-numberOfMines){
            Won_lost=true;
            Won=true;
        }
        
        return;
        
        
    }
    
    bool returnWon_Lost(){
        return Won_lost;
    }
    
    void printMatrix(){
        cerr<<"*****************"<<endl;
        for(int i=0;i<sizeOfGrid;i++){
            for(int j=0;j<sizeOfGrid;j++){
                cerr<<minesBoard[i][j]<<" ";
            }
            cerr<<endl;
        }
        cerr<<"*****************"<<endl;
    }
   
    
    void returnResult_revealed(int pos1,int pos2){
         reveal_Neighbours(pos1,pos2);
        
        if(Won_lost){
            if(Won){
                cout<<"Won"<<endl;
            }
            else{
                cout<<"Lost"<<endl;
            }
        }
        else{
            cout<<revealed<<endl;
        }
        return;
    }
    
};

int main() {
    int N,M;
    mineSweeper mS;
    cin>>N>>M;
    int minePos;
    int pos1,pos2;
    mS.createBoard(N,M);
    for(int i=0;i<M;i++){
        cin>>minePos;
        mS.minePosUpdate(minePos);
    }
    while(!cin.eof()){
       cin>>pos1>>pos2;
     mS.returnResult_revealed(pos1,pos2);
        
     if(mS.returnWon_Lost()){
            break;
        }
    }
    return 0;
}

