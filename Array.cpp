// $Id: Array.cpp 820 2011-01-17 15:30:41Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array.h"
//default
Array::Array (void)
{
	data_= nullptr;
	char firstElement = '';
	data_ = &firstElement;
	cur_size_ = 0;
	max_size_ = 0;
}

Array::Array (size_t length)
{
	data_= nullptr;
	char firstElement = '';
	data_ = &firstElement;
	char **setAddress = nullptr;
	for (size_t i = 0; i < length; i++)
	{
		setAddress = &data_ + i;
		**setAddress = '';
	}
	cur_size_= length;
	max_size_= cur_size_;
}

Array::Array (size_t length, char fill)
{
	cur_size_ = length;
	max_size_ = cur_size_;
	char **fillAddress = nullptr;
	for(size_t i = 0; i< length; i++)
	{
		fillAddress = &data_ + i;
		**fillAddress = fill;
	}
}

//array name didn't match header file so i changed one
Array::Array (const Array & arr)
{
	cur_size_=arr.size();
	max_size_ = arr.max_size();
	char firstElement = arr.get(0);
	data_ = &firstElement;
	char **fillAddress = nullptr;
	for (size_t i = 1; i < cur_size_; i++)
	{
		fillAddress = &data_ + i;
		**fillAddress = arr.get(i);;
	}
}
//destructor
Array::~Array (void)
{

}

//what i am percieving here is an alternative method to method on line 47 not a comparison operator?
const Array & Array::operator = (const Array & rhs)
{
	cur_size_ = rhs.size();
	max_size_ = rhs.max_size();
	char firstElement = rhs.get(0);
	data_ = &firstElement;
	char **fillAddress = nullptr;
	for (size_t i = 1; i < cur_size_; i++)
	{
		fillAddress = &data_ + i;
		**fillAddress = rhs.get(i);;
	}
}

char & Array::operator [] (size_t index)
{
	if (index < cur_size_)
	{
		char **grabAddress = nullptr;
		grabAddress = &data_ + index;
		return **grabAddress;
	}
	else
	{
		return std::out_of_range;
	}
}
//Don't necessarily undstand the importance of the function below.
const char & Array::operator [] (size_t index) const
{
	if (index < cur_size_)
	{
		char **grabAddress = nullptr;
		grabAddress = &data_ + index;
		return **grabAddress;
	}
	else
	{
		return std::out_of_range;
	}
}

char Array::get (size_t index) const
{
	if (index >= cur_size_)
	{
		return std::out_of_range;
	}
	else
	{
		char **getAddress = nullptr;
		getAddress = &data_ + index;
		return **getAddress;
	}
}

void Array::set (size_t index, char value)
{
	if (index >= cur_size_)
	{
		return std::out_of_range;
	}
	else
	{
		char **setAddress = nullptr;
		setAddress = &data_ + index;
		**setAddress = value;
	}
}

void Array::resize (size_t new_size)
{
	char **resizeAddress = nullptr;
	if (new_size > cur_size_)
	{
		max_size_ = new_size;
		for (size_t i = cur_size_; i < max_size_; i++)
		{
			resizeAddress = &data_ + i;
			**resizeAddress = '';
		}
		cur_size_ = max_size_;
	}
	if (new_size < cur_size_) 
	{
		for (size_t i = new_size; i < cur_size_; i++)
		{
			resizeAddress = &data_ + i;
			**resizeAddress = nullptr;
		}
		cur_size_ = new_size;
		max_size_ = cur_size_;
	}
}

int Array::find (char ch) const
{
	char **findAddress = nullptr;
	for (size_t i = 0; i < cur_size_; i++)
	{
		findAddress = &data_ + i;
		if (**findAddress == ch ) {
			return i;
		}
		return -1;
	}
}

int Array::find (char ch, size_t start) const
{
	char **findAddress = nullptr;
	for (size_t i = start; i < cur_size_; i++)
	{
		findAddress = &data_ + i;
		if (**findAddress == ch) {
			return i;
		}
		return -1;
	}
}

bool Array::operator == (const Array & rhs) const
{
	char **findAddress = nullptr;
	if (cur_size_ == rhs.size())
	{
		for (size_t i = 0; i < cur_size_; i++)
		{
			findAddress = &data_ + i;
			if (**findAddress != rhs.get(i))
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
//I feel like you can't assume just because size else the elephant would be the king of the jungle!
bool Array::operator != (const Array & rhs) const
{
	if (cur_size_ != rhs.size())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Array::fill (char ch)
{
	char **fillAddress = nullptr;
	for (size_t i = 0; i < cur_size_; i++)
	{
		fillAddress = &data_ + i;
		**fillAddress = fill;
	}
}

void Array::shrink (void)
{
	char **prev_Address = nullptr;
	char **cur_Address = nullptr;
	char **next_Address = nullptr;
	//condense characters to start
	for (size_t i = 0; i < cur_size_; i++)
	{
		if ((**prev_Address == '' || **prev_Address == ' ') && (**cur_Address != '' || **cur_Address != ' '))
		{
			i--;
		}
		prev_Address = &data_ - 1;
		cur_Address = &data_ + i;
		next_Address = &data + i + 1;
		
		if (**cur_Address == '' || **cur_Address == ' ')
		{
			if (**next_Address != '' || **next_Address != ' ')
			{
				**cur_Address = **next_Address;
				**next_Address = '';
			}
		}
	}
	size_t c = 0;
	int stop = 0;
	//find new end
	do 
	{
		cur_Address = &data_ + c;
		if (**cur_Address == '' || **cur_Address == ' ')
		{
			cur_size_ = c;
			stop = 1;
		}
	} while (stop < 1);
	//clear
	for (size_t r = cur_size_; r < max_size_; r <  r++)
	{
		cur_Address = &data_ + r;
		**cur_Address = nullptr;
	}
	max_size_ = cur_size_;
}

void Array::reverse (void)
{
	char **front_Address = nullptr;
	char **back_Address = nullptr;
	char save_Value = '';
	size_t r = cur_size_;
	for (size_t i = 0; i < cur_size_; i++)
	{
		back_Address = &data_ + r;
		front_Address = &data_ + i;
		save_Value = **front_Address;
		**front_Address = **back_Address;
		**back_Address = save_Value;
		r--;
	}
  
}
//the following two methods have commented parts which in theory should make it so they slice out the duplicated part from the original array 
void Array::slice (size_t begin) const
{
	Array new_Array;
	char **splitAddress = nullptr;
	size_t r = 0;
	for (size_t i = begin; i < cur_size_; i++)
	{
		splitAddress = &data_ + i;
		new_Array.set(r, **splitAddress);
		//**splitAddress = nullptr;
		r++;
	}
	//cur_size_ = cur_size_ - (begin + 1);
	//max_size_ = cur_size_;
	return new_Array;

}

void Array::slice (size_t begin, size_t end) const
{
	Array new_Array;
	char **splitAddress = nullptr;
	size_t r = 0;
	for (size_t i = begin; i < end; i++)
	{
		splitAddress = &data_ + i;
		new_Array.set(r, **splitAddress);
		//**splitAddress = nullptr;
		r++;
	}
	/** 
	if ((end != cur_size_) && (end < cur_size_))
	{
		size_t ref = begin;
		char **replaceAddress = nullptr;
		for (size_t p = end; p < cur_size_; p++)
		{
			replaceAddress = &data + ref;
			splitAddress = &data + p;
			**replaceAddress = **splitAddress;
			**splitAddress = nullptr;
			ref++;
		}
	}
	cur_size_= cur_size_ - (end - begin);
	max_size_ = cur_size_;
	*/
}
