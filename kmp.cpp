#include<bits/stdc++.h>
using namespace std;

vector<int> lpsf(string s)
{
    int n=s.length();
    vector<int> lps(n,0);
    int i=1;
    int j=0;

    while(i<n)
    {
        if(s[i]==s[j])
        {
            lps[i]=j+1;
            i++;
            j++;
        }
        else{
            if(j!=0)
            {
                j=lps[j-1];
            }
            else
            {
                lps[i]=0;
                i++;
            }
        }
    }
    return lps;
}

bool kmp(string txt, string ptr)
{
    int lentxt=txt.length();
    int lenptr=ptr.length();

    vector<int> lps=lpsf(ptr);
    int i=0;
    int j=0;

    while(i<lentxt)
    {
        if(txt[i]==ptr[j])
        {
            i++;
            j++;
        }
        else
        {
            if(j!=0) j=lps[j-1];
            else i++;
        }

        if(j==lenptr) return true;
    }
    return false;
}

int main(){
    string txt= "abcxabcdabcdabcy";
    string ptr="abcdabct";

    cout<<kmp(txt,ptr)<<endl;
}