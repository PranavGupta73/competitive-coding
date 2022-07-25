#include<bits/stdc++.h>
using namespace std;

int getParent(int num){
    int comp= ~(num) +1;
    int nd = comp & num;
    return num-nd;
}
int getNext(int num){
    int comp=~(num) +1;
    int nd=num & comp;
    return num + nd;
}
int sum(vector<int> fenwick,int index){
    int temp=index;
    int sum=0;
    while(temp!=0){
        sum+=fenwick[temp];
        temp=getParent(temp);
    }
    return sum;
}
void update(vector<int>& fenwick,vector<int>&v, int index, int val,int size){
    int change = val - v[index-1];
    v[index-1]=val;
    // cout<<"change"<<change<<endl;
    int temp=index;
    while(temp<=size){
        fenwick[temp]+=change;
        temp=getNext(temp);
    }
}
vector<int> createFenwickTree(vector<int> v,int size){
    vector<int> fenwick(size+1,0);
    int next=0;
    for(int i=0;i<=size;i++){
        next=i+1;
        while(next<=size){
            fenwick[next]+=v[i];
            next=getNext(next);
        }
    }
    return fenwick;
}
int main(){
    vector<int> v={3,2,-1,6,5,4,-3,3,7,2,3};
    int size=11;
    vector<int> fenwick = createFenwickTree(v,size);
    for(int i=0;i<=size;i++){
        cout<<fenwick[i]<<" ";
    }cout<<endl;

    cout<<sum(fenwick,5)<<endl;
    update(fenwick,v,3,0,size);
    for(int i=0;i<=size;i++){
        cout<<fenwick[i]<<" ";
    }cout<<endl;
    cout<<sum(fenwick,5)<<endl;
}
