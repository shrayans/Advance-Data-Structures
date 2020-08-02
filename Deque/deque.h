#include<iostream>

using namespace std;



template <typename ValueType>
class deque{

public :
	int count,capacity,top=-1,rear=-1;

	ValueType * array;

	 deque()
	{
		count = 0;
		capacity=2;
		array=new ValueType[capacity+1];
	}

	 deque(int n, ValueType value)
	{
		array=new ValueType [n+1];
		int i;
		top=0;
		for( i=1;i<n+1;i++){
			array[i]=value;
		}
		rear=n;
		count=n;
		capacity=n;
	}

	int size();


	void push_back(ValueType);//append data x at the end.

	void push_front(ValueType);

	void pop_front();

	void pop_back();

	ValueType front();

	ValueType back ();

	void clear();

	bool empty();

	void resize(int);

	ValueType &operator[] (int);

	bool isFull(); 



};

template <typename ValueType>
void deque<ValueType>::pop_back(){
   if(empty())
   {
   	cout<<"deque is empty\n";
   	return;
   }
   else
   {	
	   	if((rear-1)==-1){
	   		rear=capacity;
	   	}
	   	else
	   	{
	   		rear--;
	   	}
	   	count--;
   }
}


template <typename ValueType>
void deque<ValueType>::push_back(ValueType value){
   
	if(count==capacity)
	{
		resize(capacity*2);
	}

	if (top == -1) /* Insert First Element */
    { 
        rear = 0;
        top=capacity; 
        array[rear] = value; 
    } 
  
  	else
  	{
  		rear=(rear+1)%(capacity+1);
  		array[rear]= value;
  	}

    count++;

}

template <typename ValueType>
void deque<ValueType>::pop_front(){
   if(empty())
   {
   		cout<<"deque is empty\n";
   		return;
   }
   else
   {	
   		top=(top+1)%(capacity+1);
   		//array[top]=-1;
   		count--;
   }
}


template <typename ValueType>
void deque<ValueType>::push_front(ValueType value){
   
	if(count==capacity)
	{
		resize(capacity*2);
	}

	if(top==-1)
	{
		top=rear=0;
		array[top]=value;
		top=capacity;
	}
	else if( (top-1) == -1)
	{
		array[top]=value;
		top=capacity;
	}
	else
	{
		array[top]=value;
		top=(top-1)%(capacity+1);
	}

	count++;

}


// returns the current size of deque.
template <typename ValueType>
int deque<ValueType>::size(){
   return count;
}


template <typename ValueType>
ValueType deque<ValueType>::front(){
	
   return array[(top+1)%(capacity+1)];
}


template <typename ValueType>
ValueType deque<ValueType>::back(){
	
   return array[rear];
}



template <typename ValueType>
void deque<ValueType>::clear(){
   top=rear=-1;
   count=0;

}

template <typename ValueType>
bool deque<ValueType>::empty(){
   
   return(top==rear);

}

template <typename ValueType>
void deque<ValueType>::resize(int n){
	ValueType * a=new ValueType[n+1];
	int i,var=-1;
   for( i=0;i<n+1;i++)
   {
   		if(var<=count && !((rear+1)==(top+1)%(capacity+1) ) )
   		{
   			top=(top+1)%(capacity+1);
   			var++;
   			//cout<<"imin "<<i<<"\n";
   			a[i]=array[top];
   		}
   		else
   		{
   			//a[i]=0;
   		}

   }

   	//array[var]=array[top];
   	//cout<<var<<" \n";
   	capacity=n;
   	rear=var;
   	//cout<<"rear "<<var<<" \n";
	count=var+1;
	top=capacity;

	delete[] array;
	array=a;

}

template <typename ValueType>
ValueType & deque<ValueType>::operator[](int index) {
   if (index >= count /*|| index >= count*/){
   	cout<<"Selection index out of range="<<index<<" ";
   	//ValueType value=NULL 
	return array[0];
	}
   return array[(top+index+1)%(capacity+1)];

}


template<typename ValueType>
bool deque<ValueType>::isFull()
{
	if( (top==0 && rear==capacity) || (rear == (top-1)%(capacity)) ){
		//cout<<"ram";
		return true;
	}else
	{
		//cout<<"rames";
		return false;
	}
}


// int main()
// {

// 	deque<int> d;

// 	d.push_back(225);

// 	d.push_front(999);

	
// 	d.push_front(888);
// 	d.pop_back();

// 		for(int i=0;i<=d.capacity;i++)
// 		cout<<d[i]<<" ";
// 	cout<<"\n";


// 	cout<<"size "<<d.size()<<"\n";
// 	cout<<"front "<<d.front()<<"\n";
// 	cout<<"back "<<d.back()<<"\n";
// 	cout<<"capacity "<<d.capacity<<"\n";
// 	cout<<"empty "<<d.empty()<<"\n\n";
// 	cout<<"isFull "<<d.isFull()<<"\n\n";

// 	// d.pop_front();

// 	// for(int i=0;i<=d.capacity;i++)
// 	// 	cout<<d[i]<<" ";
// 	// cout<<"\n";

// 	// 	cout<<"size "<<d.size()<<"\n";
// 	// cout<<"front "<<d.front()<<"\n";
// 	// cout<<"back "<<d.back()<<"\n";
// 	// cout<<"capacity "<<d.capacity<<"\n";
// 	// cout<<"empty "<<d.empty()<<"\n\n";
// 	// cout<<"isFull "<<d.isFull()<<"\n\n";

// 	for(int i=4;i<16;i++){
// 		d.push_back(i);

// 	for(int i=0;i<=d.capacity;i++)
// 		cout<<d[i]<<" "; 
// 	cout<<"\n";

// 	cout<<"size "<<d.size()<<"\n";
// 	cout<<"front "<<d.front()<<"\n";
// 	cout<<"back "<<d.back()n<<"\n";
// 	cout<<"capacity "<<d.capacity<<"\n";
// 	cout<<"empty "<<d.empty()<<"\n\n";
// 	cout<<"isFull "<<d.isFull()<<"\n\n";
// 	}

// 	for(int i=16;i<36;i++){
// 		d.push_front(i);

// 	for(int i=0;i<=d.capacity;i++)
// 		cout<<d[i]<<" ";
// 	cout<<"\n";

// 	cout<<"size "<<d.size()<<"\n";
// 	cout<<"front "<<d.front()<<"\n";
// 	cout<<"back "<<d.back()<<"\n";
// 	cout<<"capacity "<<d.capacity<<"\n";
// 	cout<<"empty "<<d.empty()<<"\n\n";
// 	cout<<"isFull "<<d.isFull()<<"\n\n";
// 	}
// }




