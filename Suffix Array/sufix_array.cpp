#include <bits/stdc++.h>
#include <iostream> 
#include <cstring> 
#include <algorithm> 
using namespace std; 


class suffix_data
{
	public:
		int index;
		int currRank;
		int nextRank;
};

int cmp(suffix_data obj1, suffix_data obj2) 
{ 
	 //return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):(a.rank[0] < b.rank[0] ?1: 0); 

	 if(obj1.currRank < obj2.currRank)
	 {
	 	return 1;
	 }
	 else if(obj1.currRank > obj2.currRank )
	 {
	 	return 0;
	 }
	 else if(obj1.currRank==obj2.currRank)
	 {
	 	if(obj1.nextRank<obj2.nextRank)
	 	{
	 		return 1;
	 	}
	 	else
	 	{
	 		return 0;
	 	}
	 }
} 


void buildSA(string s , vector<int> &result)
{	

	vector<suffix_data> v;

	int size=s.size();
	
	for(int i=0;i<size;i++)
	{	
		suffix_data obj;
		obj.index=i;
		obj.currRank=s[i]-97;
		if((i+1)<size)
			obj.nextRank=s[i+1]-97;
		else
			obj.nextRank=-1;

		v.push_back(obj);
	}

	sort(v.begin(), v.end(), cmp);



	for(int i=4;i<2*size;i*=2)
	{

		v[0].currRank=0;
		int last_rank=1;

		int array[size];

		array[v[0].index]=0;

		int last_currRank=v[0].currRank;
		int last_nextRank=v[0].nextRank;

		for(int start=1;start<v.size();start++)
		{
			if((v[start].currRank==last_currRank) && (v[start].nextRank==last_nextRank))
			{
				last_currRank=v[start].currRank;
				last_nextRank=v[start].nextRank;

				v[start].currRank=v[start-1].currRank;
			}
			else
			{
				last_currRank=v[start].currRank;
				last_nextRank=v[start].nextRank;

				v[start].currRank=last_rank++;
			}

			array[v[start].index]=start;
		}


		for(int j=0;j<size;j++)
		{	
			int temp=i/2;
			
			if(v[j].index+temp < size)
			{	
				int ind=v[j].index+temp;
				v[j].nextRank=v[ array[ind] ].currRank;
			}
			else
			{
				v[j].nextRank=-1;
			}
		}
		sort(v.begin(), v.end(), cmp);


	}

	// cout<<" ";
	for(int k=0;k<v.size();k++)
	{
		//cout<<v[k].index<<" " << v[k].currRank <<" "<<v[k].nextRank<<"\n";
		result.push_back(v[k].index);
	}
	//cout<<"\n";
}



int main()
{
	int n;
	cin>>n;
	string input_string;
	cin>>input_string;
	n= input_string.size()-1;
	//cout<<input_string.size();
	std::vector<int> result;
	//buildSA(input_string,result);

	// for(int i=0;i<result.size();i++)
	// 	cout<<result[i]<<" ";

	input_string= input_string+input_string;

	buildSA(input_string,result);

	// for(int i=0;i<result.size();i++)
	// 	cout<<result[i]<<" ";

	cout<<"\n";

	for(int i=0;i<result.size();i++)
	{
		if(result[i]<=n)
		{
			for(int j=0;j<=n;j++)
				cout<<input_string[result[i]+j];
			break;
		}	
	}

	cout<<"\n";

	
}
	
	
