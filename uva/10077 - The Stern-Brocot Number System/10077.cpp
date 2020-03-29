#include <iostream>

using namespace std;

int main()
{
	int m, n;
	int m_left, n_left, m_mid, n_mid, m_right, n_right;
	while(cin>>m>>n)
	{
		if(m==1 && n==1)
			break;
		m_left = 0, n_left = 1;
		m_mid = 1, n_mid = 1;
		m_right = 1, n_right = 0;
		while(m_mid!=m || n_mid!=n)
		{
			if(m*n_mid>n*m_mid)
			{
				cout<<'R';
				m_left = m_mid;
				n_left = n_mid;
				m_mid = m_mid+m_right;
				n_mid = n_mid+n_right;
			}
			else
			{
				cout<<'L';
				m_right = m_mid;
				n_right = n_mid;
				m_mid = m_mid+m_left;
				n_mid = n_mid+n_left;
			}
		}
		cout<<endl;
	}
	return 0;
}