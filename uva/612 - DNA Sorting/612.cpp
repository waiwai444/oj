// this program uses merge sort, which is stable, because the problem 1007 requires that "since two strings can be equally sorted, then output them according to the orginal order".
// however, quick sort, which is unstable, is also accepted by the online judgement. (a bug?)

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

std::string strList[101];
int invList[101];
std::string auxStrList[101];
int auxInvList[101];

int inversionNumber(const char *str, int len)
{
	int i, j;
	int inv = 0;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(str[i]>str[j])
				inv++;
		}
	}
	return inv;
}

//int partition(int low, int high)
//{
//	int pivot = invList[low];
//	char *pivotStr = strList[low];
//	while(low<high)
//	{
//		while(high>low && invList[high]>=pivot)
//			high--;
//		if(high>low)
//		{
//			invList[low] = invList[high];
//			strList[low++] = strList[high];
//		}
//		while(low<high && invList[low]<=pivot)
//			low++;
//		if(low<high)
//		{	
//			invList[high] = invList[low];
//			strList[high--] = strList[low];
//		}
//	}
//	invList[low] = pivot;
//	strList[low] = pivotStr;
//	return low;
//}
//
//void quicksort(int low, int high)
//{
//	if(low<high)
//	{
//		int mid = partition(low, high);
//		quicksort(low, mid-1);
//		quicksort(mid+1, high);
//	}
//}

void mergesort(int low, int high)
{
	int i;
	int mid;
	int p1, p2;
	if(low<high)
	{
		mid = (low+high)/2;
		mergesort(low, mid);
		mergesort(mid+1, high);
		
		p1 = low;
		p2 = mid+1;
		for(i=low; i<=high; i++)
		{
			if(p1>mid || p2>high)
				break;
			if(invList[p1]<=invList[p2])
			{
				auxStrList[i] = strList[p1];
				auxInvList[i] = invList[p1];
				p1++;
			}
			else
			{
				auxStrList[i] = strList[p2];
				auxInvList[i] = invList[p2];
				p2++;
			}
		}
		for(; p1<=mid; p1++, i++)
		{
			auxStrList[i] = strList[p1];
			auxInvList[i] = invList[p1];
		}
		for(; p2<=high; p2++, i++)
		{
			auxStrList[i] = strList[p2];
			auxInvList[i] = invList[p2];
		}
		for(i=low; i<=high; i++)
		{
			strList[i] = auxStrList[i];
			invList[i] = auxInvList[i];
		}
	}
}

int main()
{
	int tc, i, n, m;
	cin>>tc;
	while(tc--)
	{
		cin>>n>>m;
		for(i=0; i<m; i++)
		{
			cin>>strList[i];
			invList[i] = inversionNumber(strList[i].c_str(), n);
		}
		//quicksort(0, m-1);
		mergesort(0, m-1);
		for(i=0; i<m; i++)
		{
			cout<<strList[i]<<endl;
		}
		if(tc)
			cout<<endl;
	}
	return 0;
}