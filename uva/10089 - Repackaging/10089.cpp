#include <iostream>

using namespace std;

long long vec[1000][2];	// (package[i][0]-package[i][1], package[i][0]-package[i][2])

bool repackagable(int n)
{
	int i;
	long long cur_v1[2], cur_v2[2];
	long long cp1, cp2;
	if(n==1)
		return false;
	cur_v1[0] = cur_v2[0] = vec[0][0];
	cur_v1[1] = cur_v2[1] = vec[0][1];
	for(i=1; i<n; i++)
	{
		if(cur_v1[0]*vec[i][1]==cur_v1[1]*vec[i][0])	// collinear
		{
			if(cur_v1[0]*vec[i][0]+cur_v1[1]*vec[i][1]>0)	// dot product
				continue;
			else
				return true;
		}
		if(cur_v2[0]*vec[i][1]==cur_v2[1]*vec[i][0])
		{
			if(cur_v2[0]*vec[i][0]+cur_v2[1]*vec[i][1]>0)
				continue;
			else
				return true;
		}

		if(cur_v1[0]*cur_v2[1]-cur_v2[0]*cur_v1[1]>0)
			return true;
		
		cp1 = cur_v1[0]*vec[i][1]-vec[i][0]*cur_v1[1];	// cross product
		cp2 = vec[i][0]*cur_v2[1]-cur_v2[0]*vec[i][1];
		if(cp1>0)
		{
			cur_v1[0] = vec[i][0];
			cur_v1[1] = vec[i][1];
		}
		else if(cp1<0 && cp2>0)
		{
			cur_v2[0] = vec[i][0];
			cur_v2[1] = vec[i][1];
		}
		else
			continue;
	}
	return false;
}

int main()
{
	int i, n;
	long long package[3];
	while(cin>>n && n)
	{
		for(i=0; i<n; i++)
		{
			cin>>package[0]>>package[1]>>package[2];
			vec[i][0] = package[0]-package[1];
			vec[i][1] = package[0]-package[2];
		}
		if(repackagable(n))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}