#define debugMode 0
#if debugMode==1
#define Log(x) std::cout<<x<<std::endl
#else
#define Log(x)
#endif
#include <iostream>
#include <stdexcept>
#include <exception>
template <class T>
class Vector
{
private:
	unsigned int size_,capacity_;
	T* arr_;
	void Allocate();
	void Expand();
	void Shorten();
public:
	Vector():arr_(nullptr),size_(0),capacity_(0){}
	Vector(const std::initializer_list<T>&);
	Vector(std::initializer_list<T>&&);
	Vector(const Vector&);
	Vector(Vector&&);
	~Vector();
	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);
	void PushBack(const T&);
	void PopBack();
	void Insert(int,const T&);
	T& operator[](const int&);
};


template<class T>
void Vector<T>::Allocate()
{
	int count=0;
	while(1)
	{
		arr_=new(std::nothrow) T[capacity_];
		if(arr_!=nullptr)
		{
			Log("Memory allocated");
			return;
		}
		count++;
		Log("Memory allocation faild");
		if(count==5)
		{
			Log("Memory could not be allocated");
			std::exit(EXIT_FAILURE);
		}
		Log("Try again");
	}
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>&list):size_(list.size_),capacity_(2*size_)
{
	if(capacity_==0)
	{
		arr_=nullptr;
		return;
	}
	Allocate();
	unsigned int index=0;
	for(const auto& i:list)
	{
		arr_[index]=i;
		index++;
	}
}

template<class T>
Vector<T>::Vector(std::initializer_list<T>&& list):size_(list.size()),capacity_(2*size_)
{
	if(capacity_==0)
	{
		arr_=nullptr;
		return;
	}
	Allocate();
	unsigned int index=0;
	for(const auto& i:list)
	{
		arr_[index]=std::move(i);
		index++;
	}
}

template <class T>
Vector<T>::Vector(const Vector<T> &other):size_(other.size_),capacity_(other.capacity_)
	{
		if(capacity_==0)
		{
			arr_=nullptr;
			return;
		}
		Allocate();
		for(unsigned int i=0;i<size_;i++)
		{
			arr_[i]=other[i];
		}
	}

template <class T>
Vector<T>::Vector(Vector &&other):arr_(other.arr_),size_(other.size_),capacity_(other.capacity_)
	{
		other.arr_=nullptr;
		other.size_=0;
		other.capacity_=0;
	}

template <class T>
Vector<T>::~Vector()
	{
		delete[] arr_;
		arr_=nullptr;
	}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector&other)
	{
		if(this==&other)
		{
			return(*this);
		}
		if(other.size_==0)
		{
			delete[]arr_;
			arr_=nullptr;
			size_=0;
			capacity_=0;
			return (*this);
		}
		if(capacity_>=other.size_)
		{
			size_=other.size_;
			for(int i=0;i<other.size_;i++)
			{
				arr_[i]=other.arr_[i];
			}
			if((size_*4)<=capacity_)
			{
				Shorten();
			}
			return(*this);
		}
		else
		{
			delete[]arr_;
			size_=other.size_;
			capacity_=other.capacity_;
			Allocate();
			for(unsigned int i=0;i<size_;i++)
			{
				arr_[i]=other.arr_[i];
			}
			return(*this);
		}
	}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other)
	{
		if(this==&other)
		{
			return(*this);
		}
		delete[]arr_;
		arr_=other.arr_;
		other.arr_=nullptr;
		size_=other.size_;
		capacity_=other.capacity_;
		other.size_=0;
		other.capacity_=0;
	}

template <class T>
void Vector<T>::PushBack(const T&k)
	{
		if(size_==capacity_)
		{
			Expand();
		}
		arr_[size_]=k;
		size_++;
	}

template<class T>
void Vector<T>::PopBack()
	{
		if(size_==0)
		{
			throw std::underflow_error("There's nothing to pop");
		}
		size_--;
		if(size_<=(capacity_/4))
		{
			Shorten();
		}
	}

template <class T>
void Vector<T>::Insert(int n,const T&k)
{
	if(n<0 || n>size_)
	{
		throw std::out_of_range("Invalid index");
	}
	if(size_==capacity_)
	{
		Expand();
	}
	size_+=1;
	for(int i=size_-1;i>n;i--)
	{
		arr_[i]=arr_[i-1];
	}
	arr_[n]=k;
}

template <class T>
void Vector<T>::Expand()
	{
		if(size_==0)
		{
			capacity_=1;
		}
		capacity_*=2;
		int count=0;
		T* newarr_=nullptr;
		while(1)
		{
			newarr_=new(std::nothrow) T[capacity_];
			if(newarr_!=nullptr)
			{
				Log("Expanded");
				break;
			}
			count++;
			Log("Failed");
			if(count==5)
			{
				Log("Could not expand");
				std::exit(EXIT_FAILURE);
			}
			Log("Try again");
		}
		for(unsigned int i = 0; i < size_; i++)
		{
       		newarr_[i] = arr_[i];
    	}
    	delete[] arr_;
    	arr_=newarr_;
	}

template <class T>
void Vector<T>::Shorten()
	{
		int count=0;
		unsigned int newCapacity=size_*2;
		T* newarr_=nullptr;
		while(1)
	{
		newarr_=new(std::nothrow)T[newCapacity];
		if(newarr_!=nullptr)
		{
			Log("Shortened");
			break;
		}
		count++;
		Log("failed");
		if(count==5)
		{
			Log("Could not shorten");
			return;
		}
		Log("Try again");
		for(unsigned int i=0;i<size_;i++)
		{
			newarr_[i]=arr_[i];
		}
		delete[]arr_;
		arr_=newarr_;
		capacity_=newCapacity;
	}
}

template <class T>
T& Vector<T>::operator[](const int&i)
	{
		if(i<0 || i>size_)
		{
			throw std::out_of_range("Invalid index");
		}
		return arr_[i];
	}


int main()
{
	Vector<int> v={1,2,3,4};
	Vector<int> w={90};
	v=w;	
	return 0;
} 