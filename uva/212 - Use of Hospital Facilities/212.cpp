#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

#define MAXM 1440

int nor, nrrb, start, mm, mpo, mpr, np;

struct patient_t
{
    char name[10];
    int sur_min, rec_min;
    int oroom, rbed;
    int start;
} patients[100];

struct facility_t
{
    int avail_time;
    int used_min;
} rooms[10], beds[30];

struct event_t
{
    int t, p, f;
    bool operator<(const event_t &e) const
    {
        if(t == e.t)
            return f > e.f;
        return t > e.t;
    }
};

std::priority_queue<event_t> pq;

int avail_time;

void solve()
{
    int t = MAXM, i, j, maxt = start;
    event_t e;
    std::memset(rooms, 0, sizeof(rooms));
    std::memset(beds, 0, sizeof(beds));
    while(!pq.empty())
        pq.pop();
    for(i = 0; i < np && i < nor; ++i)
    {
        patients[i].oroom = i;
        patients[i].start = start;
        //rooms[i].avail_time = t+patients[i].sur_min+mpo;
        rooms[i].used_min += patients[i].sur_min;
        e.t = start+patients[i].sur_min, e.p = e.f = i;
        pq.push(e);
        if(e.t < t)
            t = e.t;
    }
    while(!pq.empty())
    {
        e = pq.top(), pq.pop();
        t = e.t;
        patient_t &p = patients[e.p];
        for(j = 0; j < nrrb; ++j)
        {
            if(beds[j].avail_time <= t)
            {
                p.rbed = j;
                beds[j].avail_time = t+mm+p.rec_min+mpr;
                beds[j].used_min += p.rec_min;
                maxt = std::max(maxt, t+mm+p.rec_min);
                break;
            }
        }
        if(i < np)
        {
            patients[i].oroom = e.f;
            patients[i].start = t+mpo;
            //rooms[e.f].avail_time = t+mpo+patients[i].sur_min+mpo;
            rooms[e.f].used_min += patients[i].sur_min;
            e.t = t+mpo+patients[i].sur_min, e.p = i;
            pq.push(e);
            ++i;
        }
    }
    avail_time = maxt-start;
}

void print_ans()
{
    int i, t, h[4], m[4];
    std::puts(" Patient          Operating Room          Recovery Room");
    std::puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
    std::puts(" ------------------------------------------------------");
    for(i = 0; i < np; ++i)
    {
        t = patients[i].start;
        h[0] = t/60, m[0] = t%60;
        t += patients[i].sur_min;
        h[1] = t/60, m[1] = t%60;
        t += mm;
        h[2] = t/60, m[2] = t%60;
        t += patients[i].rec_min;
        h[3] = t/60, m[3] = t%60;
        std::printf("%2d  %-9s %2d   %2d:%02d   %2d:%02d     %2d   %2d:%02d   %2d:%02d\n",
                i+1, patients[i].name, patients[i].oroom+1, h[0], m[0], h[1], m[1], patients[i].rbed+1, h[2], m[2], h[3], m[3]);
    }
    std::putchar('\n');
    std::puts("Facility Utilization");
    std::puts("Type  # Minutes  % Used");
    std::puts("-------------------------");
    for(i = 0; i < nor; ++i)
        std::printf("Room %2d %7d  %6.2f\n", i+1, rooms[i].used_min, rooms[i].used_min*100/(double)avail_time);
    for(i = 0; i < nrrb; ++i)
        std::printf("Bed  %2d %7d  %6.2f\n", i+1, beds[i].used_min, beds[i].used_min*100/(double)avail_time);
    std::putchar('\n');
}

int main()
{
    int i;
    while(std::scanf("%d%d%d%d%d%d%d", &nor, &nrrb, &start, &mm, &mpo, &mpr, &np) != EOF)
    {
        start *= 60;
        for(i = 0; i < np; ++i)
        {
            std::scanf("%s%d%d", patients[i].name, &patients[i].sur_min, &patients[i].rec_min);
            patients[i].oroom = patients[i].rbed = patients[i].start = -1;
        }
        solve();
        print_ans();
    }
    return 0;
}

