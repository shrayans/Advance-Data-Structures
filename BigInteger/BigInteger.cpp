#include<iostream>

using namespace std;

class BigInteger
{
	public:
		int *num = new int[2000];
		


		string snum;
		int n;
		BigInteger(string s)
		{
			if(!s.compare("0") )
			{
				//cout<<"yeah\n";
				n=0;
				snum="0";
				return;
			}

			for( int i=0;i<2000;i++)
				num[i]=0;

			int size=s.size();
			n=size;
		
			//cout<<"\t \t \t"<<s<<"\n";
			
			for(int i=0,j=n-1 ; i<n ; j--,i++){
				num[i]=s[j]-48;
			}
			snum=s;
		}

      friend ostream &operator<<( ostream &output, const BigInteger &D );

      BigInteger add(BigInteger);

      BigInteger sub(BigInteger);

      BigInteger mul(BigInteger);

      BigInteger fact(int);

      BigInteger power(BigInteger , BigInteger);

      BigInteger divide2(BigInteger);

};


ostream & operator << (ostream &out, const BigInteger &c) 
{ 
    //out << c.snum;
    for(int i=c.n-1;i>=0;i--)
    	out<<c.num[i];
    return out; 
} 

BigInteger BigInteger :: power(BigInteger x, BigInteger y)
{
		cout<<y<<"\n";
		if (y.n == 0) 
		{
			BigInteger b("1");
        	return b; 
		}

		if(y.n==1 &&  y.snum[0]=='1')
			return x;

 	    else if (y.num[y.n-1] % 2 == 0) 
	    {
	    	BigInteger temp=temp.divide2(y);
	    	BigInteger part1=power(x,temp);
	    	BigInteger part2=power(x,temp);
	        return part1.mul(part2); 
	    }
	    else
	    {
	    	BigInteger temp=temp.divide2(y);
	    	//BigInteger temp2=power(x, temp).mul( power(x, temp) );

	    	BigInteger part1=power(x,temp);
	    	BigInteger part2=power(x,temp);

	    	part1=part1.mul(part2);


	        return x.mul(part1) ;
	    }
}


BigInteger BigInteger :: divide2(BigInteger x)
{
	int * rslt=new int[2000];
	int carry=0,i,j;
    for( i=x.n-1,j=0;i>=0;i--)
    {	//cout<<i<<" ";
    	int m=1;

    	int a= x.num[i]+(carry*10);

    	if(a==0)
    	{
    		rslt[j]=0;
    		j++;
    		continue;
    	}
    	else if(a<2)
    	{
    		carry=1;
    		rslt[i]=0;
    		j++;
    		continue;
    	}
    	
    	while(a>=m*2)
    		m++;
    	m--;
    	rslt[j]=m;
    	//cout<<m<<" \t"<<j;
    	j++;
    	carry=a-(m*2);

    }
    int start=0;
    if(rslt[0]==0)
    	start=1;
    string s = "";

    //cout<<"\n"<<j<<" "<<start;

    for(;start<j;start++)
    {
    	s=s+(char)(rslt[start]+48);		
    }
    //cout<<s<<"  str\n";
    BigInteger a(s);
    return a;
}



BigInteger BigInteger :: fact(int N)
{
	BigInteger f("1");
  
    for (int i = 2; i <= N; i++) {
    	//cout<<i;
    	BigInteger temp(to_string(i));
    	cout<<f<<"*"<<temp<<"=";
        f = f.mul(temp);
        cout<<f<<"\t\n"; 
    }
  
    return f; 
}

// mul fun uses add fun to multiply

BigInteger BigInteger :: mul (BigInteger b)
{
	//cout<<"\n";
	BigInteger rsltBigInteger("0");

	//cout<<this->snum<<" "<<b<<"\n";

	for(int i=0;i<this->n;i++)
	{
		int * rslt = new int[2000];
		int k,j;
		int carry=0;

		for(k=0;k<i;k++)
			rslt[k]=0;

		for(j=0;j<b.n;j++,k++)
		{

			int sum=(this->num[i]*b.num[j])+carry;
			rslt[k]=sum%10;
			carry=sum/10;

		}

		if(carry>0)
			rslt[k++]=carry;

		string rsltString="";

		for(int a=k-1;a>=0;a--)
		{
			rsltString=rsltString+(char)(rslt[a]+48);		
		}
		// cout<<" \t"<<rsltString<<"\n";
		BigInteger temp(rsltString);
		//cout<<" \t"<<temp<<" "<<rsltBigInteger<<"\n";
		rsltBigInteger=rsltBigInteger.add(temp);

		delete[] rslt;
	}

	return rsltBigInteger;

}



//sub function is for substraction

BigInteger BigInteger :: sub ( BigInteger b )
{
	int maxSize=(this->n>=b.n ? this->n: b.n);

	string s9="";

	for(int i=0;i<maxSize;i++)
		s9=s9+"9";
	

	int *rslt = new int[2000];


	for(int i=0;i<maxSize;i++)
	{

		rslt[i]=s9[i]-48-b.num[i];

	}
	
	s9="";

	for(int i=maxSize-1;i>=0;i--)
	{
		s9=s9+(char)(rslt[i]+48);		
	}
	
	BigInteger x(s9);
	//cout<<x<<"\n";

	BigInteger temp=this->add(x);
	//cout<<temp<<"\n";

	if(temp.num[maxSize]==1)
	{	
		//cout<<"iam in \t";
		temp.num[maxSize]=0;
		temp.n--;
		BigInteger add1("1");
		temp=temp.add(add1);
	}
	else
	{	
		for(int i=0;i<maxSize;i++)
		{
			temp.num[i]=9-temp.num[i];
		}
	}
	//cout<<temp<<"\t ans.\n";
	delete[] rslt;
	return temp;

}



BigInteger BigInteger :: add(BigInteger b)
{
	int size=(this->n>=b.n ? this->n: b.n);
	//cout<<size;
	int *rslt = new int[2000];

	for(int i=0;i<2000;i++)
		rslt[i]=0;

	int carry=0;

	string s="";
	int i;

	for(i=0; i<size ;i++ )
	{
		int sum = this->num[i]+b.num[i]+carry;

		if(sum > 9){
			carry=1;
			rslt[i]=sum%10;
		}
		else
		{
			rslt[i]=sum;
			carry=0;
		}
	}

	if(carry>0)
	{
		rslt[i]=carry;
		size++;
	}

	for(int i=size-1;i>=0;i--)
	{
		s=s+(char)(rslt[i]+48);		
	}
	s=s+"\0";
	

	BigInteger r(s);
	delete[] rslt;
	return r;
}



int main()
{
	BigInteger a("123456789"), b("987654321");
	cout<<a.add(b);
	cout<<a.fact(100);

}