#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	int k;
	int store[13] = {2, 7, 5, 30, 169, 441, 1872, 7632, 1740, 93313, 459901, 1358657, 2504881};
	while(cin>>k)
	{
		if(k==0)
			break;
		cout<<store[k-1]<<endl;
	}
	return 0;
}

