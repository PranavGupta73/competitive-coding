#include<bits/stdc++.h>
using namespace std;

void buildZ(vector<int>& z, string str)
{
    int l=0;
    int r=0;

    int n=str.length();

    for(int i=1;i<n;i++)
    {
        // i doenst lie between l and r
        // z doesnt exist 
        if(i>r)
        {
            l=i;
            r=i;
            while(r<n && str[r-l]==str[r])
            {
                r++;
            }
            z[i]=r-l;
            r--;
        }
        else
        {
            int k=i-l;
            if(z[k]<=r-i)
            {
                // i lie between l and r
                // z is already existing
                z[i]=z[k];
            }
            else
            {
                // some part of z is already included
                // we have to further start matching
                l=i;
                while(r<n && str[r-l]==str[r])
                {
                    r++;
                }
                z[i]=r-l;
                r--;
            }
        }

    }
}

void searchString(string txt, string pat)
{
    string str=pat+"$"+txt;
    int n=str.length();
    vector<int> z(n,0);
    buildZ(z,str);

    for(int i=0;i<n;i++)
    {
        if(z[i]==pat.length())
        {
            cout<<i-pat.length()-1<<endl;
        }
    }
}

int main(){
    string txt;
    string pat;
    cin>> txt>>pat;
    searchString(txt,pat);
    return 0;
}