#include <bits/stdc++.h>
#define ll long long
using namespace std;

string binary_string;

struct Trie_Node
{
	struct Trie_Node * left ;
	struct Trie_Node * right ;
	bool isWord=false;
};

struct Trie_Node *newNode() 
{ 
    struct Trie_Node *temp =  (struct Trie_Node *)malloc(sizeof(struct Trie_Node)); 
    //temp->key = item; 
    temp->left = NULL;
    temp->right = NULL; 
    return temp; 
} 
   
void convert_to_binary(ll n)
{
	 for (int c = 39; c >= 0; c--)
	 {
	    int k = n >> c;
	 
	    if (k & 1)
	      binary_string+="1";
	    else
	      binary_string+="0"; //printf("0");
	 }	
}   

ll convert_to_decimal()
{
  	//string num = binary_string; 
    ll dec_value = 0; 
  
    // Initializing base value to 1, i.e 2^0 
    ll base = 1; 
  
    ll len = binary_string.size(); 
 
  //    for (ll i = len ; i >= 0; i--) { 
		// cout<<binary_string[i]<<" "<<i<<"\n";
  //   } 

    for (ll i = len - 1; i >= 0; i--) { 
        if (binary_string[i] == '1') 
        {
        	//cout<<"i "<<i;
            dec_value += base; 
        }

        base = base * 2; 
    } 
  
    return dec_value; 	
}




struct Trie_Node * insert (struct Trie_Node* root)
{
	if(root==NULL)
	{
		struct Trie_Node * temp = newNode();
		root=temp;
		//cout<<"\ncheck0";
	}

	struct Trie_Node * root1 = root;

	for(int i=0;i<40;i++)
	{
		//root=root1;

		if(binary_string[i]=='0')
		{
			//root=root->left;
			if(root->left==NULL)
			{
				//cout<<"moving 0 left "<<i<<"\n";
				struct Trie_Node * temp = newNode();
				root->left=temp;
				//root=temp;
			}
			root=root->left;
		}
		else
		{
			//root=root->right;
			if(root->right==NULL)
			{
				//cout<<"moving 1 right "<<i<<"\n";
				struct Trie_Node * temp = newNode();
				root->right=temp;
				//root=temp;
			}
			root=root->right;
		}
	}


	return root1;
}

void find_max(struct Trie_Node * root)
{

	string rslt="";

	for(int i=0;i<40;i++)
	{

		if(binary_string[i]=='0')
		{
			if(root->right!=NULL)
			{
				//cout<<"c 1.a "<<binary_string[i]<<" "<<i<<"\n";
				rslt+="1";
				root=root->right;
			}
			else
			{
				//cout<<"c 1.b "<<binary_string[i]<<" "<<i<<"\n";
				rslt+="0";
				root=root->left;
			}
		}
		else
		{
			if(root->left!=NULL)
			{
				//cout<<"c 2.a "<<binary_string[i]<<" "<<i<<"\n";
				rslt+="0";
				root=root->left;
			}
			else
			{
				//cout<<"c 2.b "<<binary_string[i]<<" "<<i<<"\n";
				rslt+="1";
				root=root->right;
			}
		}

	}



	//cout<<"\n"<<rslt;

	binary_string=rslt;

}

int main ()
{
	ll n,q;
	cin>>n;
	cin>>q;

	ll array[n];
	ll query[q];
	struct  Trie_Node * root=NULL;

	for(int i=0;i<n;i++)
	{
		cin>>array[i];
	}

	for(int i=0;i<q;i++)
		cin>>query[i];

	for(int i=0;i<n;i++)
	{
//		cin>>array[i];
		binary_string="";
		convert_to_binary(array[i]);
		//cout<<array[i]<<" "<<binary_string<<"\n";

		root=insert(root);

	}	

	for(int i=0;i<q;i++)
	{
		ll x;
		x=query[i];
		binary_string="";
		convert_to_binary(x);
		//cout<<"\n"<<binary_string<<"\n";	
		find_max(root);
		ll rslt=convert_to_decimal();

		cout<<(rslt^x)<<"\n";//<<" " << rslt <<" " <<x;
	}
}


// 0000000000000000000000000000000000000011
// 0000000000000000000000000000000000000001
// 0000
// 0000
// 0000
// 0000
// 0000
// 0000
// 0000
// 0000
// 0000
// 0100