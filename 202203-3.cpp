#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct Node
{
    int id, block, cnt;
    set<int> task;
    bool operator<(const Node &a) const
    {
        if (this->cnt == a.cnt)
            return this->id < a.id;
        return this->cnt < a.cnt;
    }
};

unordered_map<int, Node> node;
vector<int> v;
int n, m, l, g, f, a, na, pa, paa, paar;

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        cin >> l;
        set<int> temp;
        node.insert(make_pair(i, Node{i, l, 0, temp}));
        v.push_back(i);
    }

    cin >> g;
    for (int i = 1; i <= g; i++)
    {
        cin >> f >> a >> na >> pa >> paa >> paar;
        for (int j = 1; j <= f; j++)
        {

            vector<int> temp = v;
            if (na)
            {
                for (auto it = temp.begin(); it != temp.end();)
                {
                    if (node[*it].block != na)
                        temp.erase(it);
                    else
                        it++;
                }
            }

            if (pa)
            {
                set<int> temp_s;
                for (auto &it : node)
                {
                    if (it.second.task.count(pa))
                        temp_s.insert(it.second.block);
                }

                for (auto it = temp.begin(); it != temp.end();)
                {
                    if (!temp_s.count(node[*it].block))
                        temp.erase(it);
                    else
                        it++;
                }
            }

            vector<int> temp2 = temp;
            if (paa)
            {
                for (auto it = temp2.begin(); it != temp2.end();)
                {
                    if (node[*it].task.count(paa))
                        temp2.erase(it);
                    else
                        it++;
                }
            }

            if ((temp2.empty() && paar) || temp.empty())
            {
                cout << "0"
                     << " ";
                continue; // 勿忘
            }

            if (temp2.empty() && !paar)
                temp2 = temp;

            sort(temp2.begin(), temp2.end(), [](const auto &a, const auto &b) -> bool
                 { return node[a] < node[b]; });
            node[temp2[0]].cnt++;
            node[temp2[0]].task.insert(a);
            cout << temp2[0] << " ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}