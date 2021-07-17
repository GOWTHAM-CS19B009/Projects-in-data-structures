#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include<climits>
#include <algorithm>
using namespace std;

class BLOOMBRAIN{
    private:
    int* seraphic;
    int* occupy;
    int totalRooms;
    long long int inversion_Count(int* arr,int low,int high);
    long long int common_Count(int* arr,int low,int high);
    int subArraySum(int* arr,int low,int high);
    int crossSum(int* arr,int low,int high);
    public:
    BLOOMBRAIN(int n);
    long long int update(int* a);
    void leave(int idx);
    void join(int s);
    int occupied();
    int play();
    ~BLOOMBRAIN();
};    
    BLOOMBRAIN::BLOOMBRAIN(int n){//occupy tells whether romm is empty or not and seraphic stores the value of seraphics
        occupy=new int[n];
        for(int i=0;i<n;i++){
            occupy[i]=1;
        }
        seraphic=new int[n];
        totalRooms=n;
    }
   
    
  long long int BLOOMBRAIN::update(int* a){//the function tells the no of inversion pairs present in the array
        
        for(int i=0;i<totalRooms;i++){
            seraphic[i]=a[i];
        }
        
        int* temp=new int[occupied()];//we take the effective array where we take the seraphic value where there are people i.e, non empty rooms
        int i=0;
        int k=0;
        while(i<totalRooms){
            if(occupy[i]==1){
                temp[k]=seraphic[i];
                k++;
                i++;
            }
            else{
                i++;
            }
        }
        
        long long int count=inversion_Count(temp,0,occupied()-1);
        delete[] temp;
        return count;
    }
   
    
    
  long long int BLOOMBRAIN::inversion_Count(int *arr,int low,int high){
        long long int count;
        int mid=(high+low)/2;
        if(low==high){//if it is single element then count is zero
            count=0;
        }
        else{//else it is sum of inversion pair count in first half and second half and the cross over part
            count=inversion_Count(arr,low,mid)+inversion_Count(arr,mid+1,high)+common_Count(arr,low,high);
        }
        return count;
    }
   
    
  long long int BLOOMBRAIN::common_Count(int* arr,int low,int high){//the common count is calculated as follows
        int* temp=new int[high-low+1];
        long long int count=0;
        int mid=(high+low)/2;
        int i=low;
        int j=mid+1;
        int k=0;
        while(i<=mid&&j<=high){//we sort the two half arrays in to temporary array and while sorting if any element in first half is greater is greater than the second half of elements we add them to count
            if(arr[i]<=arr[j]){
                temp[k++]=arr[i++];
            }
            else{
                temp[k++]=arr[j++];
                count=count+mid+1-i;
            }
        }
        while(i<=mid){//we add the remaiing elements of the half
            temp[k++]=arr[i++];
        }
        while(j<=high){
            temp[k++]=arr[j++];
        }
        for(int i=0;i<high-low+1;i++){
            arr[low+i]=temp[i];
        }
        delete[] temp;
        return count;
    }
    
    
   void BLOOMBRAIN::leave(int idx){
        seraphic[idx]=0;//empties the room
        occupy[idx]=0;
    }
   
    
    void BLOOMBRAIN::join(int s){//joins a person of seraphic value s at right most empty place
        int i;
        for(i=totalRooms-1;i>=0;i--){
            if(seraphic[i]==0){
                break;
            }
        }
        seraphic[i]=s;
        occupy[i]=1;
    }
    
    
    int BLOOMBRAIN::occupied(){//it returns number of available members in total rooms
        int count=0;
        for(int i=0;i<totalRooms;i++){
            if(occupy[i]==1)
                count++;
        }
        return count;
    }
    
    
    int BLOOMBRAIN::play(){/*returns the minimum value for guru whch is maximum sum of all sub arrays of seraphics*/
        int sum=subArraySum(seraphic,0,totalRooms-1);
        return sum;
    }
    
    
    int BLOOMBRAIN::subArraySum(int* arr,int low,int high){//the sum of maximum sub array
        int mid=low+(-low+high)/2;
        int sum;
        if(low==high){
            sum=arr[low];
        }
       else{
        int sum1=subArraySum(arr,low,mid);/*if the middle elememt is not inclded it is either sum of maximum sub array of left half of the array*/
        int sum2=subArraySum(arr,mid+1,high);/*or it is the sum of maximum sub array in right half*/
        int sum3=crossSum(arr,low,high);/*if mid is included it is found using crossSum*/
        if(sum1>sum2&&sum1>sum3){/*Out of these three the maximum one is the maximum value sum of original array*/
            sum=sum1;
        }
        else if (sum2>sum3){
            sum=sum2;
        }
        else{
            sum=sum3;
        }  
       } 
        return sum;
    }
    
    
    int BLOOMBRAIN::crossSum(int* arr,int low,int high){/*find the crossSum*/
        int leftSum=INT_MIN;
        int rightSum=INT_MIN;
        int mid=(low+high)/2;
        int sum=0;
        for(int i=mid;i>=low;i--){/*finding the left sum start from mid and update the sum if added element increases the value*/
            sum=sum+arr[i];
            if(sum>leftSum){
                leftSum=sum;
            }
        }
        sum=0;
        for(int i=mid+1;i<=high;i++){/*simillarly for right half */
            sum=sum+arr[i];
            if(sum>rightSum){
                rightSum=sum;
            }
        }
        
        
        int temp=leftSum+rightSum;/*now compare which is big left or right or sum of both and returnthe value it is the croeeSum value*/
        if(leftSum>rightSum&&leftSum>temp){
            sum=leftSum;
        }
        else if(rightSum>temp){
            sum=rightSum;
        }
        else{
            sum=temp;
        }
        return sum;
    }
    
    BLOOMBRAIN::~BLOOMBRAIN(){
        delete[] seraphic;
        delete[] occupy;
    }



int main() {
    
    int n;
    cin>>n;
    BLOOMBRAIN b(n);
    int Queries;
    cin>>Queries;
    string str;
    int* arr=new int[n];
    int s;
    int idx;
    
    while(Queries>0){
        cin>>str;
        if(str=="update"){
            for(int i=0;i<n;i++){
                cin>>arr[i];
            }
            cout<<b.update(arr)<<endl;
        }
        if(str=="join"){
            cin>>s;
            b.join(s);
        }
        if(str=="leave"){
            cin>>idx;
            b.leave(idx);
        }
        if(str=="occupied"){
            cout<<b.occupied()<<endl;
        }
        if(str=="play"){
            cout<<b.play()<<endl;
        }
        Queries--;
    }
    return 0;
}

