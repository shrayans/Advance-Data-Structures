#include<iostream>
#include<string.h>
#include<deque>
#include <map>

using namespace std;

class LRU
{
	public:
		int capacity,count=0;
		deque<string> d;

		map<string,string> m;

		LRU(int n)
		{
			capacity=n;
			count=0;
			cout<<"All set \n";
		}

		string get(string);

		void set(string,string);

		void rearrange(string);


};

string LRU::get(string key)
{
	map<string, string>::iterator itr = m.find(key);

	if(itr!=m.end())
	{	
		string value=itr->second;

		rearrange(key);

		return value;
	}
	else
	{
		return "Not Found\n";
	}
}


void LRU::set(string key,string value)
{
	if(m.find(key)!=m.end())
	{
		auto itr=m.find(key);
		itr->second=value;
		rearrange(key);

	}else{
		
			if(count==capacity)
			{
				string f=d.front();
				map<string, string>::iterator itr = m.find(f);
				cout<<itr->first;

				m.erase(itr);

				d.pop_front();
				d.push_back(key);
				m.insert({key,value});

			}
			else
			{
				d.push_back(key);
				m.insert({key,value});
				count++;

				// for (	map<string, string>::iterator itr = m.find("1"); itr != m.end(); ++itr) { 
	   //      			cout << '\t' << itr->first 
	   //           							<< '\t' << itr->second << '\n';}
				// cout<<d.back()<<" "<<count<<"ram\n";
				// cout<<d.front()<<" front \n";
				// cout<<m.size()<<" size \n";
			}
	}
}

void LRU :: rearrange(string s)
{
	deque<string> temp;

	while( !d.empty() )
	{	
		if(d.front()!=s)
		{	
			temp.push_back( d.front() );
		}

		d.pop_front();

	}

	temp.push_back(s);
	d.clear();

	d=temp;
}


int main()
{

	LRU lru(3);


	lru.set("1","a");
	lru.set("2","b");
	lru.set("3","c");

	cout<<lru.d.back()<<" back\n";
	cout<<lru.d.front()<<" front \n";
	cout<<lru.m.size()<<" map size \n";

	lru.set("4","sita");
	cout<<lru.get("1")<<"\n";
	cout<<lru.d.back()<<" back\n";
	cout<<lru.d.front()<<" front \n";
	cout<<lru.m.size()<<" size \n";
	lru.set("3","d");

	lru.set("3","e");
	
	// cout<<lru.d.size()<<"\n";
	for(int i=0;i<3;i++)
	{
		cout<<lru.d[i]<<" \t";
	}

	return 0;
}
