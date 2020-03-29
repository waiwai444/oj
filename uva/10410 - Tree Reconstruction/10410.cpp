#include <cstdio>
#include <vector>
#include <stack>

int n;
int bfs[1000];
int dfs[1000];
std::vector<int> child[1001];
int idx_to_bfs[1001];

void solve()
{
    int i;
    std::stack<int> st;

    for(i = 1; i <= n; ++i)
        child[i].clear();
    if(n == 1)
        return;
    for(i = 0; i < n; ++i)
        idx_to_bfs[bfs[i]] = i;

    st.push(dfs[0]);
    st.push(dfs[1]);
    child[dfs[0]].push_back(dfs[1]);
    for(i = 2; i < n; ++i)
    {
        int node = dfs[i];
        if(idx_to_bfs[st.top()] == idx_to_bfs[node]-1)
        {
            if(st.top() < node)
                st.pop();
        }
        else if(idx_to_bfs[st.top()] > idx_to_bfs[node])
        {
            st.pop();
            while(idx_to_bfs[st.top()]+1 != idx_to_bfs[node])
                st.pop();
            st.pop();
        }
        child[st.top()].push_back(node);
        st.push(node);
    }
}

void print_ans()
{
    for(int i = 1; i <= n; ++i)
    {
        std::printf("%d:", i);
        for(int j = 0; j < child[i].size(); ++j)
            std::printf(" %d", child[i][j]);
        std::putchar('\n');
    }
}

int main()
{
    int i;
    while(std::scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%d", &bfs[i]);
        for(i = 0; i < n; ++i)
            std::scanf("%d", &dfs[i]);
        solve();
        print_ans();
    }
    return 0;
}

