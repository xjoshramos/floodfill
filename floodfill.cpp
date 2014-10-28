#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

struct Image
{

	int width, height;
	int *data;
	Image(int w, int h)
	{
		width = w;
		height = h;
		data = NULL;
		Init();

	}
	~Image()
	{
		delete[] data;
	}
	void Display() const
	{
		for(int i=0; i<height; i++)
		{
			for(int j=0; j<width; j++)
			{
				std::cout << data[i*width +j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void Example1()
	{
		width  = 8;
		height = 6;
		Init();
		Image &self = *this;
		for(int i=1; i<height; i++)
			self(0,i) = 1;
		for(int i=1; i<height; ++i)
			self(i,0) = 1;
		self(2,2) = 1;
		self(3,3) = 3;
		self(4,4) = 1;
		self(3,5) = 1;
		self(2,5) = 2;
		self(1,5) = 3;
		self(5,5) = 2;
	}
	
	void Solution1()
	{
		Example1();
		Image &self = *this;
		self(1,1) = 5;
		self(1,2) = 5;
		self(1,3) = 5;
		self(1,4) = 5;
		self(2,1) = 5;
		self(2,3) = 5;
		self(2,4) = 5;
		self(3,1) = 5;
		self(3,2) = 5;
		self(3,4) = 5;
		self(4,1) = 5;
		self(4,2) = 5;
		self(4,3) = 5;
		self(5,1) = 5;
		self(5,2) = 5;
		self(5,3) = 5;
		self(5,4) = 5;
	}
	void Init()
	{
		if(data) delete[] data;
		data = new int[width*height];
		memset(data, 0, width*height*sizeof(int));
	}
	inline int& operator()(int i, int j)
	{
		return data[i*width +j];
	}
	bool operator==(Image const& rhs) const
	{
		Image const& self = *this;
		for(int i =0; i<height; i++)
		{
			for(int j =0; j<width; j++)
			{
				//if(self(i,j) != rhs(i,j))
				//{
				//	return false;
				//}
			}
		}
		return true;
	}

	void floodfill( int x, int y, int color)
	{
	}
};


int main(int argc, char *argv[])
{
	
	std::cout << "Input: " <<std::endl;
	Image in(1,1);
	cout << "helllllloooooo" << endl;
	in.Example1();
	in.Display();
	std::cout << "solution: "<<std::endl;
	Image out(1,1);
	out.Solution1();
	out.Display();

	Image sanity(1,1);
	sanity.Solution1();
	
	in.floodfill(2,3,5);

	system("PAUSE");
	return 0;
}
