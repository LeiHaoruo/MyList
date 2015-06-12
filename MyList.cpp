//class：MyList 

#include<iostream>
using namespace std;

template <class T> class MyList;
template <class T> MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template <class T> MyList<T> operator + (const MyList<T> &l1, const T &item);
template <class T> ostream & operator<< (ostream &os, const MyList<T> &obj);

template <class T>
class MyList{
private:
	T *a;
	int size;          //size of the array 
	int lh;            //number of items
	void double_space();//double the space when needed
public:
	MyList(){
		size = 100;
		a = new T [size];
		lh= 0;
	}
	MyList(int num, const T &item);//repeat item num times to initialize a MyList  
	MyList(const MyList<T> &l);//copy MyList l to create a new MyList
    MyList(T* arr, int len);// initialize a MyList with the first len items of array T

	void push(const T &item);//append item at the end
	T pop();//delete the last item of MyList and return its value
	void insert(int index, const T &item);//insert item at index
	void clean();//empty MyList
	int get_size();//return the number of items in MyList
	void erase(int start, int end); //delete items between start and end in MyList(include start and end)
	T get_item(int index);//return the value of item at index
	MyList<T> get_item(int start, int end);//return items between start and end in MyList(include start and end)
	int count(const T &item);//return the number of the value of item in MyList
	void remove(const T &item);//delete the first element with the value of item


	friend MyList<T> operator + <>(const MyList<T> &l1, const MyList<T> &l2); //combine MyList l1,l2
    friend MyList<T> operator + <>(const MyList<T> &l1, const T &item); //return a new MyList with item appended to MyList l1
	MyList<T> &operator = (const MyList<T> &l);//assign MyList 
	MyList<T> &operator += (const T &item);//equal to push(T item)
	MyList<T> &operator += (const MyList<T> &l);//append MyList l at the end 
	T &operator [](int index);//return the item at index
	friend ostream & operator<< <>(ostream &os, const MyList<T> &obj);//display a MyList

	void sort(bool less=true);//sort items in MyList.if less=true,sort from small to large
	void reverse();//reverse the items of MyList

	~MyList(){delete [] a;}
};

template <class T>
void MyList<T>::double_space()
{	int dsize=2*size;
	T *temp;
	temp=new T [dsize];
	for(int i=0;i<size;++i)
		temp[i]=a[i];
	size=dsize;
	a=temp;	
}

template <class T>
MyList<T>::MyList(int num, const T &item)
{	size=num;
	a=new T [size];
	lh=num;
	for(int i=0;i<size;++i)
		a[i]=item;
}

template <class T>
MyList<T>::MyList(const MyList<T> &l)
{	size=l.lh;
	a=new T [size];
	lh=l.lh;
	for(int i=0;i<lh;++i)
		a[i]=l.a[i];		
}

template <class T>
MyList<T>::MyList(T* arr, int len)
{	size=len;
	a=new T [size];
	lh=len;
	for(int i=0;i<size;++i)
		a[i]=arr[i];
}

template <class T>
void MyList<T>::push(const T &item)
{	if(lh>=size)
		double_space();
	a[lh]=item;
	lh+=1;	
}

template <class T>
T MyList<T>::pop()
{	try{if(lh==0) throw int(0);
		T last;
		last=a[lh-1];
		lh-=1;
		return last;
	   }
	catch(int){cout<<"Error!The list you want to pop is empty!";
			   exit(1); 
	          }
}

template <class T>
void MyList<T>::insert(int index, const T &item)
{	try{if(index<0)
			index+=lh;
		if(index<0||index>lh) throw int(0);
		T *temp;
		lh+=1;
		size=lh;
		temp=new T [size];
		for(int i=0;i<index;++i)
			temp[i]=a[i];
		temp[index]=item;
		for(int i=index+1;i<lh;++i)
			temp[i]=a[i-1];
		a=temp;	
 	   }	
	catch(int){cout<<"Error！Index is out of range while trying to insert!";
			   exit(1);
	          }
}

template <class T>
void MyList<T>::clean()
{	lh=0;
}

template <class T>
int MyList<T>::get_size()
{	return lh;
}

template <class T>
void MyList<T>::erase(int start, int end)
{	try{if(start<0)
			start=lh+start;
		if(end<0)
			end=lh+end;
		if(start<0||start>=lh||end<0||end>=lh||start>end)
			throw int(0);
		T *temp;
		int len=lh+start-end-1;
		temp=new T [len];
		size=len;
		lh=len;
		for(int i=0;i<start;++i)
			temp[i]=a[i];
		for(int i=start;i<len;++i)
			temp[i]=a[i+end-start+1];
		a=temp;
	   }
	catch(int){cout<<"Error！Index is out of range while trying to erase!";
			   exit(1);
			  }
}

template <class T>
T MyList<T>::get_item(int index)
{	try{if(index<0)
			index+=lh;
		if(index<0||index>=lh)
			throw int(0);
		return a[index];
	   }
	catch(int){cout<<"Error！Index is out of range while trying to get a item!";
			   exit(1);
			  }
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end)
{	try{if(start<0)
			start=lh+start;
		if(end<0)
			end=lh+end;
		if(start<0||start>=lh||end<0||end>=lh)
			throw int(0);
		MyList<T> temp;
		if(start>end)
			return temp;
		else for(int i=start;i<=end;++i)
				temp.push(a[i]);	
		return temp;
	  }
	catch(int){cout<<"Error！Index is out of range while trying to get items!";
			   exit(1);
			  }
}

template <class T>
int MyList<T>::count(const T &item)
{	int count=0;
	for(int i=0;i<lh;++i)
		if(a[i]==item)
			count+=1;
	return count;
}

template <class T>
void MyList<T>::remove(const T &item)
{	int pos=0;
	bool jud=false;
	for(int i=0;i<lh;++i)
		if(a[i]==item)
			{pos=i;jud=true;
			 break;
			}
	if(jud==true)
		erase(pos,pos);
}

template <class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2)
{	MyList<T> temp;
	for(int i=0;i<l1.lh;++i)
		temp.push(l1.a[i]);
	for(int i=0;i<l2.lh;++i)
		temp.push(l2.a[i]);
	return temp;
}

template <class T>
MyList<T> operator + (const MyList<T> &l1, const T &item)
{	MyList<T> temp(l1);
	temp.push(item);
	return temp;
}

template <class T>
MyList<T> & MyList<T>::operator = (const MyList<T> &l)
{	if(this==&l) return *this;
	
	delete [] a;
	size=l.lh;
	a=new T [size];
	lh=0;
	for(int i=0;i<l.lh;++i)
		push(l.a[i]);
	
	return *this;
}

template <class T>
MyList<T> & MyList<T>::operator += (const T &item)
{	push(item);
	return *this;
}

template <class T>
MyList<T> & MyList<T>::operator += (const MyList<T> &l)
{	*this=*this+l;
	return *this;
}

template <class T>
T & MyList<T>::operator [](int index)
{	try{if(index<0)
			index+=lh;
		if(index<0||index>=lh)
			throw int(0);
		return a[index];
	   }
	catch(int){cout<<"Error！Index is out of range!";
			   exit(1);
			  }	
}

template <class T>
ostream & operator<<(ostream &os, const MyList<T> &obj)
{	if(obj.lh==0)
		{os<<"[]"<<endl;
		 return os;
		}
	os<<'[';
	for(int i=0;i<obj.lh-1;++i)
		os<<obj.a[i]<<','<<' ';
	os<<obj.a[obj.lh-1]<<']'<<endl;
	return os;
}

template <class T>
void quicksort(T a[],int low,int high)
{	int mid,lb,hb;
	lb=low;hb=high;
	if(low>=high) return;
	T k=a[low];
	do{while(low<high&&a[high]>=k)--high;
	if(low<high){a[low]=a[high];++low;}
	while(low<high&&a[low]<=k)++low;
	if(low<high){a[high]=a[low];--high;}
	  }while(low!=high);
	a[low]=k;
	mid=low;
	quicksort(a,lb,mid-1);
	quicksort(a,mid+1,hb);
}

template <class T>
void MyList<T>::sort(bool less)
{	quicksort(a,0,lh-1);
	if(less==false)
		reverse();
}

template <class T>
void MyList<T>::reverse()
{	T *temp;
	temp=new T [lh];
	for(int i=0;i<lh;++i)
		temp[i]=a[lh-i-1];
	a=temp;
}

//testing code
int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] * if start > end,return[]
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	b.remove(4); // b = [15, 1, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;

	return 0;
}
