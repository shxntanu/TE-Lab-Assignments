#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Process {
    public:
    int id;
    string pname;

    Process () {
        id = 0;
        pname = "";
    } 

    friend class Election;
};

class Election {
    Process *p;
    int *flag;
    int num;

    int highest(Process p[]) {
        int pos = 0, max = 0;
        for(int i=0;i<num;i++) {
            if(p[i].id > max) {
                max = p[i].id;
                pos = i;
            }
        }
        return pos;
    }

    int find_position(int id) {
        for(int i=0;i<num;i++) {
            if(p[i].id == id)
                return i;
        }
        return 0;
    }

    public:

    void input() { 
        cout<<"Enter number of processes: ";
        cin>>num;

        p = new Process[num];
        flag = new int[num];

        for(int i=0;i<num;i++) {
            cout<<"Enter process name: ";
            cin>>p[i].pname;
            cout<<"Enter process id: ";
            cin>>p[i].id;
        }

        int pos = highest(p);
        cout<<"Process named "<<p[pos].pname<<" has crashed. ID: "<<p[pos].id<<endl;
    }

    Process bully (Process coordinator) {
        for(int i=0;i<num;i++)
            flag[i] = 0;

        int crashed = highest(p);
        flag[crashed] = 1;

        for(int i=0;i<num;i++) {
            if(p[i].id > coordinator.id) 
                cout<<"Election message sent from Process (coordinator) "<<coordinator.id<<" to Process "<<p[i].id<<endl;
            else flag[i] = 1;
        }

        for(int i=0;i<num;i++) {
            if(flag[i] != 1 && p[i].id > coordinator.id) {
                cout<<"The process "<<p[i].id<<" takes over from the current coordinator "<<coordinator.id<<endl;
                flag[coordinator.id] = 1;
                coordinator = p[i];
            }
        }

        for(int i=0;i<num;i++) {
            if(flag[i] == 0) 
                coordinator = bully(coordinator);
        }

        return coordinator;
    }

    void ring (Process coordinator) {
        vector<int> vec;
        int crashed = highest(p);
        int pos = find_position(coordinator.id);
        int count = 0, i = pos;
        while(count < num ) {
            if(i != crashed) 
                vec.push_back(p[i].id);
            i = (i+1)% num;
            count++;
        }
        vector<int>::iterator it;

        cout<<"Message is [";
        for(int i=0;i<count;i++) {
            cout<<vec[i]<<" ";
        }
        cout<<"]"<<endl;
        int coord_id = *max_element(vec.begin(), vec.end());
        int final_coord_pos = find_position(coord_id);
        cout<<"Final coordinator is: "<<p[final_coord_pos].pname<<endl;
    }
};

int main() {
    Election e;
    e.input();
    Process i_coord;
    Process f_coord;

    cout << "Enter the name process which detects that the coordinator has crashed: ";
    cin >> i_coord.pname;
    cout << "Enter the id process which detects that the coordinator has crashed: ";
    cin >> i_coord.id;

    int ch = 0;
    while(ch != 3) {
        cout << "MENU" << endl;
        cout << "1.Bully algorithm\n2.Ring algorithm\n3.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            f_coord = e.bully(i_coord);
            cout << "The final coordinator is: " << f_coord.pname << endl;
            break;
        case 2:
            e.ring(i_coord);
        }
    }

    return 0;
}
