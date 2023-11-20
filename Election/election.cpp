#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process
{
public:
    int id;
    string pname;

    Process()
    {
        id = 0;
        pname = "";
    }

    friend class Election;
};

class Election
{
    Process *p;
    int num;
    int *flag;

public:
    void input()
    {
        cout << "Enter the number of process : ";
        cin >> num;
        p = new Process[num];
        flag = new int[num];
        for (int i = 0; i < num; i++)
        {
            cout << "Enter the Process name:  " << endl;
            cin >> p[i].pname;
            cout << "Enter the Id of Process : " << endl;
            cin >> p[i].id;
        }
        int pos = highest(p);
        cout << "The initial coordinator " << p[pos].pname << " has crashed ";
    }

public:
    int highest(Process p[])
    {
        int pos = 0;
        int max = 0;
        for (int i = 0; i < num; i++)
        {
            if (p[i].id > max)
            {
                max = p[i].id;
                pos = i;
            }
        }
        return pos;
    }

public:
    Process bully(Process cord)
    {
        for (int i = 0; i < num; i++)
        {
            flag[i] = 0;
        }
        int crashed = highest(p);
        flag[crashed] = 1;

        for (int i = 0; i < num; i++)
        {
            if (p[i].id > cord.id)
            {
                cout << "The election message is sent from " << cord.id << " to " << p[i].id;
            }
            else
            {
                flag[i] = 1;
            }
        }
        for (int i = 0; i < num; i++)
        {
            if (flag[i] != 1 && p[i].id > cord.id)
            {
                cout << "The id" << p[i].id << " takes over from " << cord.id << endl;
                flag[cord.id] = 1;
                cord = p[i];
            }
        }
        for (int i = 0; i < num; i++)
        {
            if (flag[i] == 0)
            {
                cord = bully(cord);
            }
        }
        return cord;
    }
    int find_pos(int id)
    {
        int pos = 0;
        for (int i = 0; i < num; i++)
        {
            if (p[i].id == id)
            {
                pos = i;
            }
        }
        return pos;
    }

public:
    Process ring(Process cord)
    {
        vector<int> v;
        int crashed = highest(p);
        int pos = find_pos(cord.id);
        int count = 0;
        int i = pos;
        while (count < num)
        {
            if (i != crashed)
            {
                v.push_back(p[i].id);
            }
            i = (i + 1) % num;
            count++;
        }
        vector<int>::iterator it;
        cout << "Message is: " << endl;
        cout << "[";
        for (it = v.begin(); it != v.end(); it++)
        {
            cout << *it << " ";
        }
        cout << "]" << endl;
        int cord_id = *max_element(v.begin(), v.end());
        int final_coord_pos = find_pos(cord_id);
        cout << "The final coordinator is " << p[final_coord_pos].pname << endl;
    }
};
int main()
{
    Election e;
    e.input();
    Process coord;
    Process final_coord;

    cout << "Enter the name process which detects that the coordinator has crashed: ";
    cin >> coord.pname;
    cout << "Enter the id process which detects that the coordinator has crashed: ";
    cin >> coord.id;
    int ch = 0;
    while (ch != 3)
    {
        cout << "MENU" << endl;
        cout << "1.Bully algorithm\n2.Ring algorithm\n3.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            final_coord = e.bully(coord);
            cout << "The final coordinator is: " << final_coord.pname << endl;
            break;
        case 2:
            e.ring(coord);
        }
    }

    return 0;
}
