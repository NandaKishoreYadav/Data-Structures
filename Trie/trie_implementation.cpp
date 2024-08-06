#include<bits/stdc++.h>
using namespace std;
struct TrieNode{
    TrieNode* child[26];
    bool isEnd;
    TrieNode(){
        isEnd=false;
        for(int i=0;i<26;i++){
            child[i]=NULL;
        }
    }
};
void insert(TrieNode* root,string &s){
    TrieNode* curr=root;
    for(int i=0;i<s.size();i++){
        int ind=s[i]-'a';
        if(curr->child[ind]==NULL)
        curr->child[ind]=new TrieNode();
        curr=curr->child[ind];
    }
    curr->isEnd=true;
}
bool search_key(TrieNode* root,string &s){
    TrieNode* curr=root;
    for(int i=0;i<s.size();i++){
        int ind = s[i] - 'a';
        if(curr->child[ind]==NULL)
        return false;
        curr=curr->child[ind];
    }
    return curr->isEnd;
}
bool isEmpty(TrieNode* root){
    for(int i=0;i<26;i++){
        if(root->child[i]!=NULL)return false;
    }
    return true;
}
TrieNode* delete_val(TrieNode* root,string &s,int i){
    if(root==NULL)return NULL;
    if(i==s.size()){
        root->isEnd=false;
        if(isEmpty(root)){
            delete(root);
            root=NULL;
        }
        return root;
    }
    int ind=s[i]-'a';
    root->child[ind]=delete_val(root->child[ind],s,i+1);
    if(isEmpty(root) and root->isEnd==false){
        delete(root);
        root=NULL;
    }
    return root;
}
int main(){
    TrieNode* root=new TrieNode();
    vector<string> arr={"geek","geeks","and","an","zoo","zebra"};
    // Inserting values in a Trie DataStructure
    for(int i=0;i<arr.size();i++){
        insert(root,arr[i]);
    }
    // Searching for geeks
    cout<<search_key(root,arr[1]);
    string s="a";
    // Searching for string not in Trie
    cout<<search_key(root,s);
    cout<<search_key(root,arr[5]);
    // Deleting an from Trie
    root = delete_val(root,arr[3],0);
    // Deleting geek from Trie
    root = delete_val(root,arr[0],0);
    // Searching geeks
    cout<<search_key(root,arr[1]);
    // Searching an
    cout<<search_key(root,arr[3]);

}
