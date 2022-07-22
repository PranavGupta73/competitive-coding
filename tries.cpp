#include <bits/stdc++.h>
using namespace std;
struct Node{
    Node* links[26];
    bool flag;
    
    bool containsKey(char ch){
        if(links[ch-'a']!=NULL) return true;
        else return false;
    }
    
    void put(char ch, Node* node)
    {
//         cout<<ch<<endl;
        links[ch-'a']=node;
    }
    
    Node* get(char ch){
        return links[ch-'a'];
    }
    
    void setFlag() {
        flag=true;
    }
        
    bool getFlag() {
        return flag;
    }
        
};


class Trie {

public:

    Node* root;
    //Initialize your data structure here

    Trie() {
        root=new Node();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* node= root;
        for(int i=0;i<word.length();i++)
        {
            if(!(node->containsKey(word[i])))
            {
                node->put(word[i],new Node());
            }
                node = node->get(word[i]);
            
        }
        node->setFlag();
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* node=root;
        for(int i=0;i<word.length();i++){
            if(node->containsKey(word[i])){
                node = node->get(word[i]);
            }else
                return false;
        }
        return node->getFlag();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        Node* node=root;
        for(int i=0;i<word.length();i++){
            if(node->containsKey(word[i])){
                node = node->get(word[i]);
            }else
                return false;
        }
        return true;
    }
};