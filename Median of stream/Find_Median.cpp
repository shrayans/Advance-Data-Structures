#include <bits/stdc++.h>

using namespace std;

struct AvlNode 
{
    int data;
    struct AvlNode * right;
    struct AvlNode * left;
    int h;
    int lSize;
    int rSize;
    int size;
};
double k1,k2;
int flag;
void printPreorder(AvlNode* node) 
{ 
    if (node == NULL) 
        return; 
    cout << "( "<< node->data <<"|"<< node->h <<"|"<< node->size<< ") "; 
    printPreorder(node->left);  
    printPreorder(node->right); 
}  

void printInorder(AvlNode* node) 
{ 
    if (node == NULL) 
        return; 
    printInorder(node->left); 
    cout << node->data << " "; 
    printInorder(node->right); 
} 
int j=0;
int i=0;





AvlNode * createNode ( int data)
{
    AvlNode * node = new AvlNode();
    node->data=data;
    node->right=NULL;
    node->left=NULL;
    node->h=0;
    node->lSize=0;
    node->rSize=0;
    node->size=1;
    return node;
}

int findHeight(AvlNode* node)
{
    if(node==NULL)
        return -1;
    return node->h;
}

int findSize(AvlNode* node)
{
    if(node==NULL)
        return 0;
    return node->size;
}

bool check_balance(AvlNode * root)
{
    int lHeight , rHeight;

    if(root->right==NULL)
        rHeight=-1;
    else
        rHeight=root->right->h;

    if(root->left==NULL)
        lHeight=-1;
    else
        lHeight=root->left->h;
    //cout<<"\nroot-"<<root->data<<" lHeight=" <<lHeight <<" rHeight="<<rHeight<<"\n\n";
    if(abs(lHeight-rHeight)>1)
        return true;
    return false;
}


AvlNode* LeftRotation(AvlNode * root)
{
        //cout<<root->data;
    AvlNode * z=root;
    //cout<<z->data;
    AvlNode * y=root->left;
    //cout<<y->data;
    AvlNode * x= root->left->left;
    //cout<<root->data;
    root=y;
    z->left=root->right;
    root->right=z;

    if(x!=NULL)
    {
        x->h=max(findHeight(x->left),findHeight(x->right))+1;
        x->size=findSize(x->left)+findSize(x->right)+1;
    }
    
    z->h=max(findHeight(z->left),findHeight(z->right))+1;
    root->h=max( findHeight(root->left),findHeight(root->right) )+1;

    z->size=findSize(z->left)+findSize(z->right)+1;
    root->size=findSize(root->left)+findSize(root->right)+1;


    return root;
}


AvlNode* RightRotation(AvlNode * root)
{
    //cout<<root->data;
    AvlNode * z=root;
    //cout<<z->data;
    AvlNode * y=root->right;
    //cout<<y->data;
    AvlNode * x= root->right->right;
    //cout<<root->data;
    root=y;
    z->right=root->left;
    root->left=z;

    if(x!=NULL){
        x->h=max(findHeight(x->left),findHeight(x->right))+1;
        x->size=findSize(x->left)+findSize(x->right)+1;
    }

    z->h=max(findHeight(z->left),findHeight(z->right))+1;
    root->h=max( findHeight(root->left),findHeight(root->right) )+1;

    z->size=findSize(z->left)+findSize(z->right)+1;
    root->size=findSize(root->left)+findSize(root->right)+1;
    return root;
}




AvlNode* perform_rotation(AvlNode* root,int data)
{
    

    if(root->data > data)
    {
        if(root->left->data > data)
        {    //LL 
            root=LeftRotation(root);
        }
        else
        {
            //LRrightright
            AvlNode * child = RightRotation(root->left);
            root->left=child;
            root=LeftRotation(root);
        }
    }
    else
    {
        if(root->right->data <= data)
        {
            root=RightRotation(root);
        }
        else
        {
            AvlNode * child=LeftRotation(root->right);
            root->right=child;
            root=RightRotation(root);        
        }
    }

    return root;
}




AvlNode* insert(AvlNode * root,int data)
{
    if(root==NULL)
    {
        AvlNode * temp = createNode(data);
        return temp;
    }

    if(root->data > data)
    {
        AvlNode * child=insert(root->left,data);
        root->left=child;
        root->size=findSize(root->left)+findSize(root->right)+1;
        root->h=max(child->h+1,root->h);
        //printPreorder(root);cout<<"\n";

        if(check_balance(root))
        {
           // cout<<"root"<<root->data<<" \n";
             root =perform_rotation(root,data);
        }

        return root;
    }

    if(root->data <= data)
    {
        AvlNode * child=insert(root->right,data);
        root->right=child;
        root->h=max(child->h+1,root->h);
        root->size=findSize(root->left)+findSize(root->right)+1;

        
        if(check_balance(root))
        {
            //cout<<"root"<<root->data<<" \n";
             root =perform_rotation(root,data);
        }

        return root;
    }
    return root;
}



AvlNode * findLargest(AvlNode * root , int k)
{
    if(root==NULL)
        return root;

    int lSubSize = findSize(root->left);

    if(k==lSubSize+1){
        return root;
    }    
    else if (k > lSubSize)
    {
        return (findLargest(root->right,(k-lSubSize-1) ) );
    }
    else
    {
        return (findLargest(root->left , k) );
    }
}

void findMedian( AvlNode * root)
{
    int n=root->size;

    if(n==1){
       // cout<<"\nmedian "<< root->data;return;
       k1=(double)(root->data);return;
    }

    if(n==2)
    {
        if(root->left!=NULL){
           // cout<<"\nmedian "<< (root->data+root->left->data)/2;return;
           k1=(double)(root->data+root->left->data)/2;return;
        }
        //cout<<"\nmedian "<<(root->data+root->right->data)/2;
        k1=(double)(root->data+root->right->data)/2;
        return;
    }

    if(n==3){
        //cout<<"\nmedian "<< root->data;return;
        k1=(double)(root->data);return;
    }

    if(root->left->size==root->right->size){
       // cout<<"\nmedian "<<root->data;return;
        k1=(double)(root->data);return;
    }


    if(n%2 == 1)
    {
        AvlNode * temp=findLargest(root,(n/2)+1);
        k1=temp->data;
       // cout<<"\nmedian"<<k1;
    }
    else
    {
        AvlNode * temp=findLargest(root,(n/2));
        double a=temp->data;
        temp = findLargest(root,(n/2)+1);
        double b=temp->data;
        //cout<<"\nmedian"<<(float)((a+b)/2);
        k1=(double)((a+b)/2);
    }
} 





int main()
{
	AvlNode* root = NULL;
 	int n ;
	cin>>n;

 	while(n--)
 	{
 		int a;
 		cin>>a;
 		root=insert(root,a);
 		findMedian(root);
 		cout<<"Median:- "<< k1<<"\t"; printInorder(root); cout<<"\n";
 	}

    return 0;
}
