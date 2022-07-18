#include<bits/stdc++.h>
using namespace std;

class ST{
public:
    vector<int> seg;
    vector<int> lazy;

    ST(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int ind, int low ,int high ,vector<int>& arr){
        // cout<<low<<" "<<high<<" ";
        if(high==low)
        {
            seg[ind]=arr[low];
            return;
        }

        int mid=(high+low)>>1;
        // cout<<mid<<endl;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);

        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }

    void update(int ind, int low ,int high, int l, int r, int val){

        //update prev remaining upates
        if(lazy[ind]!=0){
            seg[ind]+=(high-low+1)*lazy[ind];
            //propogate the lazy downwards

            if(low!=high){
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            
            lazy[ind]=0;
        }
        

        // no overlap l r low high or  low high l r
        if(r<low || high < l) return;

        // complete overlap l low high r
        if(low>=l && high<=r){
            seg[ind]+=(high-low+1)*val;
            if(low!=high){
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            return;
        }
        int mid=(high+low)>>1;
        update(2*ind+1,low,mid,l,r,val);
        update(2*ind+2,mid+1,high,l,r,val);

        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }

    int query(int ind ,int low ,int high ,int l , int r){
        //update prev remaining upates
        if(lazy[ind]!=0){
            seg[ind]+=(high-low+1)*lazy[ind];
            //propogate the lazy downwards

            if(low!=high){
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            
            lazy[ind]=0;
        }

        // no overlap l r low high or  low high l r
        if(r<low || high < l) return 0;

        // complete overlap l low high r
        if(low>=l && high<=r) return seg[ind];


        int mid=(high+low)>>1;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(ind,mid+1,high,l,r);

        return left+right;

    }
};

int main(){
    int n;
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;

        arr.push_back(x);
    }
    // cout<<arr.size()<<endl;

    ST st(n);
    st.build(0,0,n-1,arr);
    // for(auto i:st.seg){
    //     cout<<i<<" ";
    // }cout<<endl;
    int q;
    cin>>q;

    for(int i=0;i<q;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r;
            cin>>l>>r;
            cout<<st.query(0,0,n-1,l,r)<<endl;
        }else{
            int l,r,val;
            cin>>l>>r>>val;
            st.update(0,0,n-1,l,r,val);

        }
    }

}