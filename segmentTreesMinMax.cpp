#include<bits/stdc++.h>
using namespace std;

class SGTRee{
private: vector<int> seg;
public:
    SGTRee(int n){
        seg.resize(4*n);
    }
    void build(int ind,int low, int high, vector<int>& arr){
    if(low==high){
        seg[ind]=arr[low];
        return;
    }

    int mid=(low+high)/2;

    build(2*ind+1,low,mid,arr);
    build(2*ind+2,mid+1,high,arr);

    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
}

int query(int ind,int low, int high, int l, int r){
    //no overlap l r low high or low high l r
    if(r<low || high>l) return INT_MAX;
    //complete overlap l low high r
    if(low>=l && high<=r) return seg[ind];
    int mid=(low+high)/2;
    int left=query(2*ind+1,low,mid,l,r);
    int right=query(2*ind+2,mid+1,high,l,r);
    return min(left,right);
}

void update(int ind, int low, int high ,int i, int val){
    if(low==high){
        seg[ind]=val;
        return;
    }

    int mid=(low+high)/2;
    if(i<=mid) update(ind,low,mid,i,val);
    else update(ind,mid+1,high,i,val);

    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
}    

};