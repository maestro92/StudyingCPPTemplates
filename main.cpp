// #include <iostream>
#include <stdio.h>

using namespace std;


template<class T> T add(T a, T b)
{
	return a + b;
}


int main()
{

	float g = add<float>(10, 2);
	int c = add<int>(10, 2);
//	cout << c << endl;
//	cout << g << endl;

//	float g = 10 + 2;
//	int c = 10 + 2;

	printf("%d", c);
	printf("%f", g);
}