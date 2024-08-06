#include<bits/stdc++.h>
using namespace std;

int n=4;
int arr[4]={10,20,30,40};

int tree[16]; // Take 4*n for segment tree size instead of 2 * 2^(ceil(log2(n))) - 1

// Always Pass st=0 and se=n-1 i.e, segment start and segment end
// si is the index of the segment tree array
int createSegTree(int ss,int se,int si){
    if(ss==se){
        tree[si] = arr[ss];
        return arr[ss];
    }
    int mid=(ss+se)/2;
    tree[si]=createSegTree(ss,mid,2*si+1)+createSegTree(mid+1,se,2*si+2);
    return tree[si];
}

// Range Query
// here qs is the starting index of query and qe is ending index
int get_sum(int qs,int qe,int ss,int se,int si){
    // Contidion for the query range is out of segment
    if(qe<ss or qs>se)return 0;
    // Condition for the query range completely within the segment
    if(qs<=ss and qe>=se)return tree[si];
    int mid = (ss+se)/2;
    return get_sum(qs,qe,ss,mid,2*si+1)+get_sum(qs,qe,mid+1,se,2*si+2);
}

// Update Query
// here ss=0, se=n-1, i=index at which updation takes place
// si=index of the tree array, diff = new_val-arr[i]
void update(int ss,int se,int i,int si,int diff){
    if(i<ss or i>se)return;
    tree[si]+=diff;
    if(se>ss){
        int mid=(ss+se)/2;
        update(ss,mid,i,2*si+1,diff);
        update(mid+1,se,i,2*si+2,diff);
    }
}

int main(){    
    createSegTree(0,n-1,0);
    cout<<get_sum(0,2,0,n-1,0)<<endl; // 60
    cout<<get_sum(1,3,0,n-1,0)<<endl; // 90
    cout<<get_sum(0,3,0,n-1,0)<<endl; // 100
    // Updating index 1 to 25
    update(0,n-1,1,0,25-arr[1]);
    // Updating index 1 to 25
    update(0,n-1,0,0,15-arr[0]);
    cout<<get_sum(0,1,0,n-1,0)<<endl; // 40
    cout<<get_sum(1,2,0,n-1,0)<<endl; // 55
}