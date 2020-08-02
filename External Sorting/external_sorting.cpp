#include <bits/stdc++.h>
#include <unistd.h>
#include <stdlib.h>
#define ll long long

#define RUN_SIZE 1000000

using namespace std;
typedef pair<int, int> pi;

void minHeapify(vector<pi> &a,int i) 
{ 
    int large = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  	int n=a.size();
    // If left child is larger than root 
    if (l < n && a[l].first < a[large].first) 
        large = l; 
  
    // If right child is larger than largest so far 
    if (r < n && a[r].first < a[large].first) 
        large = r; 
  
    // If largest is not root 
    if (large != i) 
    { 
        swap(a[i], a[large]); 

        minHeapify(a,large); 
    } 

} 

void build_min_heap(vector<pi> &a)
{	
	int size=a.size();
	cout<<a[0].first;
	for(int i=(size-1)/2; i>=0; i-- )
		minHeapify(a,i);
}


void merge (vector<int> &a , int start ,int mid, int end)
{

	int i=start;
	int j= mid+1;
	int k=0;

	int b[end-start+1];

	for(int p=start; p<=end ; p++)
	{
		if(i>mid)
			b[k++]=a[j++];
		else if (j>end)
			b[k++]=a[i++];
		else if (a[i]<a[j])
			b[k++]=a[i++];
		else
			b[k++]=a[j++];

	}

	for(i=start, k=0 ; i<=end;)
		a[i++]=b[k++];

}


void mergeSort(vector<int> &a, int start,int end)
{

	if(start<end)
	{
		int mid=(start+end)/2;

		mergeSort(a,start,mid);
		mergeSort(a,mid+1,end);

		merge(a,start,mid,end);

	}
}






int main(int argc, char ** argv)
{
	cout<<"ram\n";
  	char name[100]="file";

	FILE * fp = fopen ( argv[1]  , "rb" );
	size_t len = 0;
    ssize_t read;
	
	fseek ( fp , 0 , SEEK_END);
	int size = ftell ( fp );
	rewind ( fp );

	int num_of_chunks=0;

	int n;
	int data_readed=0;

	for(int i=0; ((size-data_readed)!=0) ;i++)
	{

		int num_readed=1;
		char * line = NULL;
		std::vector<int> v;

	    while (RUN_SIZE>=num_readed && ( (read = getline(&line, &len, fp)) != -1 ) ) 
	    {

	        int val;
	        val=atoi(line);
	        //cout<<val<<"\t";
	        v.push_back(val);
	        num_readed++;
	        data_readed+=read;

	    }

	    cout<<"\n i "<<i<<" data_readed "<<data_readed<<" "<<size;

	    //sort(v.begin(),v.end());

	    mergeSort(v,0, v.size()-1 );

		char create_file_name[256];
		sprintf(create_file_name,"%s_%d%s",name,i,".txt");
		
	    FILE *fp1 = fopen ( create_file_name , "wb" );

	    for(int i=0;i<v.size();i++)
	    {	    	
	    	fprintf(fp1, "%d\n",v[i] );

	    	//cout<<v[i]<<"\t";
	    }
	    
	    fclose(fp1);
	    cout<<"\n"<<create_file_name;
	    num_of_chunks++;
	}

	// n=40;
	n=num_of_chunks-1;

	cout<<"\nNUmber of num_of_chunks "<<num_of_chunks;

	FILE * rslt_fp=fopen ( argv[2]  , "wb" );

	int array_of_file[n+1]={0};
	priority_queue<pi, vector<pi>, greater<pi> > pq; 

	vector<pi> pqe;

	vector<FILE *> vector_file_pointer;



	for(int i=0;i<n+1;i++)
	{
		char * line=NULL;
		char create_file_name[256];
		sprintf(create_file_name,"%s_%d%s",name,i,".txt");

		cout<<"\nreading from "<<create_file_name;	

		FILE *fp1 = fopen ( create_file_name , "rb" );

		vector_file_pointer.push_back(fp1);

			if( (read = getline(&line, &len, fp1)) != -1 )
			{
		        int val;
	        	val=atoi(line);

	        	pq.push(make_pair(val,i));

	        	pqe.push_back(make_pair(val,i));

	        	//build_min_heap(pqe);
	        	cout<<"\n"<<val<<" "<<i<<" "<<pqe.size();
			}

	}

	build_min_heap(pqe);
	cout<<"\nprinting\n";
	// for(int i=0;i<pqe.size();i++)
 //    { 
 //        //cout << pq.top() << " "; 
 //        //pq.pop(); 
 //      	pair<int, int> top = pqe[i]; 
	// 	cout << top.first << " " << top.second<<"\n"; 
 //      	//pq.pop();
 //    }


	while(pqe.size()>0)
	//for(int i=0;i<200;i++)
	{

		pair<int,int> top1=pq.top();
		pq.pop();

		pair<int,int> top=pqe[0];		

		//cout<<"\ntop data "<<top.first<<" "<<top.second<<" ";
		char * line=NULL;
		char create_file_name[256];
		sprintf(create_file_name,"%s_%d%s",name,top.second,".txt");

		//cout<<" reading from "<<create_file_name;	

		FILE *fp1 = vector_file_pointer[top.second];
		//cout<<" array value "<<array_of_file[top.second]<<"\n";

		int num_of_lines=array_of_file[top.second];

		fprintf(rslt_fp, "%d\n",top.first );


		array_of_file[top.second]++;


		if( (read = getline(&line, &len, fp1)) != -1 )
		{
			int val;
			val=atoi(line);

			pq.push(make_pair(val,top.second));

			pqe[0].first=val;
	        //cout<<"\n"<< val<<" "<<array_of_file[top.second];
			minHeapify(pqe,0);
		}
		else
		{
			pqe.erase(pqe.begin());
			minHeapify(pqe,0);
			
		}

		//fclose(fp1);
		fflush(rslt_fp);
	}


	for(int i=0;i<n+1;i++)
	{
		fclose(vector_file_pointer[i]);
	}

	fclose(rslt_fp);
	fclose(fp);


}