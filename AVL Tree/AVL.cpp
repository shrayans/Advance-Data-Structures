#include<stdio.h>
//#include<conio.h>
#include<iostream>
#include<bits/stdc++.h> 

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
int k1,k2,flag; 




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

AvlNode* search(AvlNode* root,int x)
{
	if(root==NULL)
		return root;
	if(root->data==x)
		return root;
	if(root->data > x)
	{
		return search(root->left,x);
	}
	return search(root->right,x);
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
		{	//LL 
			root=LeftRotation(root);
		}
		else
		{
			//LR
			AvlNode * child = RightRotation(root->left);
			root->left=child;
			root=LeftRotation(root);
		}
	}
	else
	{
		if(root->right->data < data)
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

	if(root->data==data){
		cout<<"\nAlready exist\n";return root;
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
			//cout<<"root"<<root->data<<" \n";
		 	root =perform_rotation(root,data);
		}

		return root;
	}

	if(root->data < data)
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

}






AvlNode * findMinSuccesors( AvlNode * root)
{
	if(root-> left ==NULL)
		return root;
	//if(root->left)
	return (findMinSuccesors(root->left));
}


AvlNode * perform_rotation_delete( AvlNode * root)
{
	AvlNode * x, *y,z;
	//z=root;

	if(findHeight(root->left) > findHeight(root->right))
	{
		y=root->left;
		if(findHeight(y->left) > findHeight(y->right) )
		{	//LL
			root=LeftRotation(root);
		}
		else
		{	//LR
			AvlNode * child = RightRotation(root->left);
			root->left=child;
			root=LeftRotation(root);
		}

	}
	else
	{
		y=root->right;
		if(findHeight(y->right)> findHeight(y->left))
		{
			//RR
			root=RightRotation(root);
		}
		else
		{	//RL
			AvlNode * child=LeftRotation(root->right);
			root->right=child;
			root=RightRotation(root);				
		}
	}
	return root;
}

AvlNode * deleteNode(AvlNode * root, int x)
{
	//cout<<"ram";

	if(root==NULL)
		return root;

	if(root->data > x)
	{
		AvlNode* child = deleteNode(root->left,x);

		root->left=child;
		root->size=findSize(root->left)+findSize(root->right)+1;
		root->h=max(findHeight(root->left),findHeight(root->right))+1;
		//printPreorder(root);cout<<"\n";

		if(check_balance(root))
		{
			//cout<<"root"<<root->data<<" \n";
		 	root =perform_rotation_delete(root);
		}

	}

	if(root->data < x)
	{
		AvlNode* child = deleteNode(root->right,x);
		root->right=child;
		root->h=max(findHeight(root->left),findHeight(root->right))+1;
		root->size=findSize(root->left)+findSize(root->right)+1;
		//printPreorder(root);cout<<"\n";
		
		if(check_balance(root))
		{
			//cout<<"root"<<root->data<<" \n";
		 	root =perform_rotation_delete(root);
		}

	}

	if(root->data == x)
	{
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			return NULL;
		}

		if(root->left!=NULL && root->right==NULL)
		{
			AvlNode * temp= root->left; 
			free(root);
			return temp;
		}
		if(root->left==NULL && root->right!=NULL)
		{
			AvlNode * temp= root->right; 
			free(root);
			return temp;			
		}

		AvlNode * temp= findMinSuccesors(root->right);
		cout<<" \t && "<<temp->data;
		root->data = temp->data;

		AvlNode * child = deleteNode(root->right,temp->data);

		root->right=child;

		root->h=max(findHeight(root->left),findHeight(root->right))+1;
		root->size=findSize(root->left)+findSize(root->right)+1;
		printPreorder(root);cout<<"\n";
		
		if(check_balance(root))
		{
			cout<<"root"<<root->data<<" \n";
		 	root =perform_rotation_delete(root);
		}


	}

	return root;

}
