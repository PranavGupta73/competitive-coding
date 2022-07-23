#include<bits/stdc++.h>
using namespace std;
int main(){

    /*

        We are given 2^n values and we have to find the sum of all subsets of a given value.
        26 = 11010 means that a2,a4,a5 are present in the set(1 based index).

    */
    int n;
    cin>>n;

    int f[1<<n]; //1<<n represents 2^n
    for(int i=0;i<(1<<n);i++){
        cin>>f[i];
    }

    int h[1<<n]; //ans of method 1
    int l[1<<n]; //ans of method 2.1
    int m[1<<n]; //ans of method 2.2
    int o[1<<n]; //ans of method 3

    //Method 1: brute force (time complexity : 4^n)
    // for(int t=0;t<(1<<n);t++)
    // {
    //     h[t]=0;
    //     for(int x=0;x<(1<<n);x++){
    //         //we have to check if x is a subset of t.
    //         if((t&x)==x) //t&x == x means that x is a subset of t.
    //         {
    //             h[t]+=f[x];
    //         }
    //     }
    // }
    //Method 1 ends


    //Method 2.1: only go to subsets of t. (Time complexity: 3^n)

    //the subsets are traveled in increasing order.
    // for(int t=0;t<(1<<n);t++)
    // {
    //     l[t]=0;
    //     int x=0;
    //     cout <<t<<":";
    //     do
    //     {
    //         l[t]+=f[x];
    //         cout<<x<<" ";
            
    //     }while(x=(x-t)&t);
    //     cout<<endl;
    // }

    //method 2.2: the subsets are traveled in decreasing order.(Time complexity: 3^n)
    // for(int t=0;t<(1<<n);t++)
    // {
    //     m[t]=0;
    //     int x=0;
    //     cout <<t<<":";
    //     for( int x=t; x>0 ; x=(x-1)&t )
    //     {
    //         m[t]+=f[x];
    //         cout<<x<<" ";
            
    //     }
    //     m[t]+=f[0];
    //     cout<<0<<" ";
    //     cout<<endl;
    // }
    //Method 2 ends

    //Method 3 : DP (Time Complexity :n*2^n)
    //dp[t][i] stores the sum for value t if only first i bits are allowed to be masked. 
    //eg . dp[26][3] (11010)= f(11010)+f(11000) i.e. only bits in first 3 places can be masked.

    /*
        2 possible cases: 
        ith bit is off: dp[t][i] = dp[t][i-1]
        ith bit is on: dp[t][i] = dp[t][i-1](keeping the ith bit on always) + dp[t^(1<<i)][i-1](keeping the ith bit off always) 

        t ^ (1<<i) removes the ith bit from t. 
    */

   int dp[1<<n][n+1];
   for(int t=0;t<(1<<n);t++)
   {
    dp[t][0] = f[t];
   }

    for(int t=0;t<(1<<n);t++)
    {
        for(int i=1;i<=n;i++)
        {
            if(t&(1<<(i-1))) //1 based indexing for i.
            {
                dp[t][i] = dp[t][i-1] + dp[t^(1<<(i-1))][i-1];
            }
            else
            {
                dp[t][i]=dp[t][i-1];
            }
        }
    }
    for(int t=0;t<(1<<n);t++)
    {
        o[t]=dp[t][n];
    }
    //method 3 ends.

    for(int i=0;i<(1<<n);i++)
    {
        cout<<o[i]<<" ";
    }cout<<endl;

}