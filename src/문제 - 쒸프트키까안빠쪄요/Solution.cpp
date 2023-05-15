#include <bits/stdc++.h>
#define INF 1987654321
using namespace std;

string s;

typedef struct node
{
    node *l, *r, *p;
    int lv, rv, len, midmx, midmn, cnt, v;
    bool rev;
    node(): l(nullptr), r(nullptr), p(nullptr) {};
}node;

node *root;

void lp(node *n);

void update(node *n)
{
    if(!n) return;
    if(n -> v < -1 || n -> v > 1) // 더미 노드 예외처리
    {
        n -> cnt = 1;
        n -> lv = n -> rv = 0; n -> len = 1;
        n -> midmx = -INF, n -> midmn = INF;
        if(n -> l)
        {
            n -> cnt += n -> l -> cnt;
        }
        if(n -> r)
        {
            n -> cnt += n -> r -> cnt;
        }
        return;
    }
    n -> cnt = 1;
    n -> midmx = -INF, n -> midmn = INF;
    if(n -> v >= -1 && n -> v <= 1)
    {
        n -> len = n -> v ? 1 : 2;
        n -> lv = n -> rv = n -> v;
    }
    if(n -> v)
    {
        if(n -> l)
        {
            lp(n -> l);
            n -> cnt += n -> l -> cnt;
            n -> len += n -> l -> len - 1;
            n -> lv = n -> l -> lv;
            n -> rv = n -> l -> rv + n -> v;
            if(n -> l -> len == 1) n -> lv = n -> rv;
            n -> midmx = n -> l -> midmx;
            n -> midmn = n -> l -> midmn;
        }
        if(n -> r)
        {
            lp(n -> r);
            int tmplen = n -> len;
            n -> cnt += n -> r -> cnt;
            n -> len += n -> r -> len - 1;
            int e1 = n -> rv, s2 = n -> r -> lv;
            if(n -> r -> len == 1)
            {
                n -> rv += n -> r -> lv;
                if(tmplen == 1)
                {
                    n -> lv = n -> rv;
                }
            }
            else
            {
                n -> rv = n -> r -> rv;
                if(tmplen == 1)
                {
                    n -> lv += n -> r -> lv;
                }
            }
            n -> midmx = max(n -> midmx, n -> r -> midmx);
            n -> midmn = min(n -> midmn, n -> r -> midmn);
            if(n -> r -> len > 1 && tmplen > 1)
            {
                n -> midmx = max(n -> midmx, s2 + e1);
                n -> midmn = min(n -> midmn, s2 + e1);
            }
        }
    }
    else
    {
        if(n -> l)
        {
            lp(n -> l);
            n -> cnt += n -> l -> cnt;
            n -> len += n -> l -> len - 1;
            n -> lv = n -> l -> lv;
            n -> rv = 0;
            n -> midmx = n -> l -> midmx;
            n -> midmn = n -> l -> midmn;
            if(n -> l -> len > 1)
            {
                n -> midmx = max(n -> midmx, n -> l -> rv);
                n -> midmn = min(n -> midmn, n -> l -> rv);
            }
        }
        if(n -> r)
        {
            lp(n -> r);
            int tmplen = n -> len;
            n -> cnt += n -> r -> cnt;
            n -> len += n -> r -> len - 1;
            n -> rv = n -> r -> rv;
            n -> midmx = max(n -> midmx, n -> r -> midmx);
            n -> midmn = min(n -> midmn, n -> r -> midmn);
            if(n -> r -> len > 1)
            {
                n -> midmx = max(n -> midmx, n -> r -> lv);
                n -> midmn = min(n -> midmn, n -> r -> lv);
            }
        }
    }
}

void lp(node *n)
{
    if(!n) return;
    if(n -> rev)
    {
        node *tmp = n -> l;
        n -> l = n -> r;
        n -> r = tmp;
        if(n -> len > 1)
        {
            int t = n -> lv;
            n -> lv = n -> rv;
            n -> rv = t;
            if(n -> len > 2)
            {
                if(n -> v) // n -> v == + or -
                {
                    /*
                    [s1, e1] + [v] + [s2, e2]
                    -> [s2, e2] + [v] + [s1, e1] -> 이 단계까지 완료
                    -> [e2, s2] + [v] + [e1, s1]
                    */
                    n -> lv = n -> rv = n -> v;
                    n -> len = 1;
                    if(n -> l)
                    {
                        n -> len += n -> l -> len - 1;
                        int s2 = n -> l -> lv, e2 = n -> l -> rv;
                        if(n -> l -> rev)
                        {
                            s2 = n -> l -> rv;
                            e2 = n -> l -> lv;
                        }
                        n -> lv = e2; n -> rv = s2 + n -> v;
                        if(n -> l -> len == 1) n -> lv = n -> rv;
                        n -> midmx = n -> l -> midmx;
                        n -> midmn = n -> l -> midmn;
                    }
                    if(n -> r)
                    {
                        int tmplen = n -> len, endv = n -> rv;
                        n -> len += n -> r -> len - 1;
                        int s1 = n -> r -> lv, e1 = n -> r -> rv;
                        if(n -> r -> rev)
                        {
                            s1 = n -> r -> rv;
                            e1 = n -> r -> lv;
                        }
                        if(n -> r -> len == 1)
                        {
                            n -> rv += s1;
                            if(tmplen == 1)
                            {
                                n -> lv = n -> rv;
                            }
                        }
                        else
                        {
                            n -> rv = s1;
                            if(tmplen == 1)
                            {
                                n -> lv += e1;
                            }
                        }
                        n -> midmx = max(n -> midmx, n -> r -> midmx);
                        n -> midmn = min(n -> midmn, n -> r -> midmn);
                        if(n -> r -> len > 1 && tmplen > 1)
                        {
                            n -> midmx = max(n -> midmx, endv + e1);
                            n -> midmn = min(n -> midmn, endv + e1);
                        }
                    }
                }
                else // n -> v == >
                {
                    /*
                    [s1, e1] + [0, 0] + [s2, e2]
                    -> [s2, e2] + [0, 0] + [s1, e1] -> 이 단계까지 완료
                    -> [e2, s2] + [0, 0] + [e1, s1]
                    */
                    n -> lv = n -> rv = 0;
                    if(n -> l)
                    {
                        int s2 = n -> l -> lv, e2 = n -> l -> rv;
                        if(n -> l -> rev)
                        {
                            s2 = n -> l -> rv;
                            e2 = n -> l -> lv;
                        }
                        n -> lv = e2; n -> rv = 0;
                        if(n -> l -> len > 1)
                        {
                            n -> midmx = max(n -> l -> midmx, s2);
                            n -> midmn = min(n -> l -> midmn, s2);
                        }
                    }
                    if(n -> r)
                    {
                        // [e2, s2, 0] + [e1, s1]
                        int s1 = n -> r -> lv, e1 = n -> r -> rv;
                        if(n -> r -> rev)
                        {
                            s1 = n -> r -> rv;
                            e1 = n -> r -> lv;
                        }
                        if(n -> r -> len == 1)
                        {
                            n -> rv += s1;
                        }
                        else
                        {
                            n -> rv = s1;
                            n -> midmx = max(max(n -> midmx, n -> r -> midmx), e1);
                            n -> midmn = min(min(n -> midmn, n -> r -> midmn), e1);
                        }
                    }
                }
            }
        }
        if(n -> l) n -> l -> rev = !n -> l -> rev;
        if(n -> r) n -> r -> rev = !n -> r -> rev;
        n -> rev = false;
    }
}

void rotate(node *n)
{
    node *par = n -> p;
    node *g = par -> p;
    node *tmp;
    if(!par) return;
    lp(par);
    lp(n);
    if(n == par -> l)
    {
        par -> l = n -> r;
        tmp = n -> r;
        n -> r = par;
    }
    else
    {
        par -> r = n -> l;
        tmp = n -> l;
        n -> l = par;
    }
    n -> p = g;
    par -> p = n;
    if(tmp) tmp -> p = par;
    if(!g) root = n;
    else
    {
        if(g -> l == par) g -> l = n;
        else g -> r = n;
    }
    update(par);
    update(n);
}

void splay(node *n)
{
    while(n -> p)
    {
        node *par = n -> p;
        node *g = par -> p;
        if(g)
        {
            if((n == par -> l) == (par == g -> l)) // n, par 방향 같음
            {
                rotate(par);
            }
            else rotate(n);
        }
        rotate(n);
    }
}

void findkth(int k) // 1-Based, index == k인 노드가 root가 된다.
{
    node *n = root;
    lp(n);
    while(true)
    {
        while(n -> l && n -> l -> cnt > k)
        {
            n = n -> l;
            lp(n);
        }
        if(n -> l) k -= n -> l -> cnt;
        if(!k) break;
        else k--;
        n = n -> r;
        lp(n);
    }
    splay(n);
}

void treeinit(int k, node *n) // s[k-1]에 따라 노드 값 지정
{
    switch(s[k-1])
    {
        case '+':
            n -> v = n -> lv = n -> rv = 1;
            n -> len = 1;
            break;

        case '-':
            n -> v = n -> lv = n -> rv = -1;
            n -> len = 1;
            break;

        case '>':
            n -> v = n -> lv = n -> rv = 0;
            n -> len = 2;
            break;
    }
    n -> midmn = INF, n -> midmx = -INF;
}

void init(int k) // 초기화는 편향 트리로 진행
{
    node *n;
    root = n = new node;
    n -> lv = n -> rv = 0; n -> v = 2;
    n -> midmn = INF; n -> midmx = -INF; n -> len = 1;
    n -> rev = false;
    for(int i=1;i<=k;i++)
    {
        n -> r = new node;
        n -> r -> p = n;
        n = n -> r;
        treeinit(i, n);
        n -> rev = false;
    }
    n -> r = new node;
    n -> r -> p = n;
    n = n -> r;
    n -> lv = n -> rv = 0; n -> v = 2;
    n -> midmn = INF; n -> midmx = -INF; n -> len = 1;
    n -> rev = false;
    while(n != nullptr)
    {
        update(n);
        n = n -> p;
    }
}

void query(int l, int r) // 실행 시 [l, r]에 해당하는 값을 갖는 노드가 root -> r -> l이 된다. (l, r은 1-Based)
{
    findkth(l-1);
    node *n = root;
    root = n -> r;
    root -> p = nullptr;
    findkth(r-l+1);
    root -> p = n;
    n -> r = root;
    root = n;
}

void reverse(int l, int r)
{
    query(l, r);
    node *n = root -> r -> l;
    n -> rev = !n -> rev;
    lp(n);
}

void query1(int l, int r, int k)
{
    if(k > 0)
    {
        reverse(r-k+1, r);
        reverse(l, r-k);
    }
    else
    {
        k = -k;
        reverse(l, l+k-1);
        reverse(l+k, r);
    }
    reverse(l, r);
}

int query2(int l, int r)
{
    query(l, r);
    node *n = root -> r -> l;
    lp(n);
    return max(max(n -> midmx, n -> lv), n -> rv);
}

void debug()
{
    node *n = root;
    while(n != nullptr)
    {
        cout << n -> lv << " " << n -> rv << " " << n -> midmx << " " << n -> midmn << " " << n -> len << " " << n -> v << "\n";
        n = n -> r;
    }
}

void debug1(node *n)
{
    lp(n);
    if(n -> l) debug1(n -> l);
    switch(n -> v)
    {
        case -1:
            cout << "-";
            break;
        case 0:
            cout << ">";
            break;
        case 1:
            cout << "+";
            break;
        default:
            cout << "?";
            break;
    }
    if(n -> r) debug1(n -> r);
}

void debug2(node *n) // lazyprop 없이 트리 출력
{
    queue< pair<node*, int> > q;
    int d = 1;
    q.push({n, d});
    while(!q.empty())
    {
        node* n = q.front().first;
        int k = q.front().second;
        q.pop();
        if(d < k)
        {
            cout << "\n";
            d++;
        }
        if(!n)
        {
            cout << " NA /";
            continue;
        }
        else cout << " " << n -> lv << " " << n -> rv << " " << (n -> midmx == -INF ? "-INF" : to_string(n -> midmx)) << " " << (n -> midmn == INF ? "INF" : to_string(n -> midmn)) << " " << n -> len << " " << (n -> v ? (n -> v > 0 ? (n -> v == 1 ? "+" : "?") : "-"): ">") << " " << n -> rev << " " << n -> cnt << " /";
        q.push({n -> l ? n -> l : nullptr, d+1});
        q.push({n -> r ? n -> r : nullptr, d+1});
    }
    cout << "\n\n";
}

int main(void)
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, i, q;
    cin >> n;
    cin >> s;
    init(n);
    cin >> q;
    while(q--)
    {
        int a, b, c, d;
        cin >> a;
        switch(a)
        {
            case 1:
                cin >> b >> c >> d;
                query1(b, c, d);
                break;
            
            case 2:
                cin >> b >> c;
                cout << query2(b, c) << "\n";
                break;
        }
    }
}