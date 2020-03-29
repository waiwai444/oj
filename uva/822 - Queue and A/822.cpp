#include <cstdio>
#include <cstring>
#include <climits>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

int nt, ns;

struct topic_t
{
    int nr, arr, dur, intv;
    int cur;
} topics[20];

std::map<int, int> topic_idx;
int wait_jobs[20];

struct staff_t
{
    int id, nt;
    int tp[20];
    int last_start, last_end;
} staff[5];

int next_arrive[20], next_finish[5];

struct cmp_staff_t
{
    bool operator()(int i, int j)
    {
        staff_t &p1 = staff[i], &p2 = staff[j];
        if(p1.last_start == p2.last_start)
            return p1.id > p2.id;
        return p1.last_start > p2.last_start;
    }
};

int find_next_time()
{
    int i, t = INT_MAX;
    for(i = 0; i < nt; ++i)
        t = std::min(t, next_arrive[i]);
    for(i = 0; i < ns; ++i)
        t = std::min(t, next_finish[i]);
    return t;
}

int solve()
{
    int i, j, k, p, t, t2;
    int total_jobs = 0, total_wait_jobs = 0;
    int idle[20], idle_num = 0;
    std::priority_queue<int, std::vector<int>, cmp_staff_t> pq;

    for(i = 0; i < ns; ++i)
    {
        for(j = 0; j < staff[i].nt; ++j)
            staff[i].tp[j] = topic_idx[staff[i].tp[j]];
        staff[i].last_start = 0, staff[i].last_end = -1;
        pq.push(i);
        next_finish[i] = INT_MAX;
    }
    for(i = 0; i < nt; ++i)
    {
        topics[i].cur = 0;
        total_jobs += topics[i].nr;
        wait_jobs[i] = 0;
        next_arrive[i] = topics[i].arr;
    }
    for(t = find_next_time(); ; t = find_next_time())
    {
        for(i = 0; i < ns; ++i)
        {
            if(staff[i].last_end == t)
            {
                pq.push(i);
                next_finish[i] = INT_MAX;
                --total_jobs;
            }
        }
        if(total_jobs == 0)
            break;
        for(i = 0; i < nt; ++i)
        {
            if(topics[i].arr == t)
            {
                ++wait_jobs[i];
                ++total_wait_jobs;
                ++topics[i].cur;
                if(topics[i].cur < topics[i].nr)
                {
                    topics[i].arr += topics[i].intv;
                    next_arrive[i] = topics[i].arr;
                }
                else
                    next_arrive[i] = INT_MAX;
            }
        }
        while(!pq.empty() && total_wait_jobs > 0)
        {
            p = pq.top(), pq.pop();
            for(i = 0; i < staff[p].nt; ++i)
            {
                j = staff[p].tp[i];
                if(wait_jobs[j] > 0)
                {
                    --wait_jobs[j];
                    --total_wait_jobs;
                    staff[p].last_start = t;
                    staff[p].last_end = t+topics[j].dur;
                    next_finish[p] = staff[p].last_end;
                    break;
                }
            }
            if(i == staff[p].nt)
                idle[idle_num++] = p;
        }
        while(idle_num > 0)
            pq.push(idle[--idle_num]);
    }

    return t;
}

int main()
{
    int i, j, id, tc = 0;
    while(std::scanf("%d", &nt), nt)
    {
        topic_idx.clear();
        for(i = 0; i < nt; ++i)
        {
            std::scanf("%d%d%d%d%d", &id, &topics[i].nr, &topics[i].arr, &topics[i].dur, &topics[i].intv);
            topic_idx[id] = i;
        }
        std::scanf("%d", &ns);
        for(i = 0; i < ns; ++i)
        {
            std::scanf("%d%d", &staff[i].id, &staff[i].nt);
            for(j = 0; j < staff[i].nt; ++j)
                std::scanf("%d", &staff[i].tp[j]);
        }
        std::printf("Scenario %d: All requests are serviced within %d minutes.\n", ++tc, solve());
    }
    return 0;
}

