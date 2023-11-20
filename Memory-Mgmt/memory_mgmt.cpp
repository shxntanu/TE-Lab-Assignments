#include<iostream>
#include<map>
#include<iomanip>
#include<algorithm>
using namespace std;
class Memory{
    int *blocks;
    int *process;
    int *flag;
    int bsize;
    int psize;

    public:
        Memory(){
            bsize=0;
            psize=0;
        }
    void input();
    void firstfit();
    void bestfit();
    void worstfit();
    //void intial_wastage();

};
void Memory::input(){
    cout<<"Enter the number of blocks present\n"<<endl;
    cin>>bsize;
    cout<<"Enter the number of processes\n"<<endl;
    cin>>psize;
    blocks=new int[bsize];
    process=new int[psize];
    flag=new int[bsize];
    cout<<"Enter the size of the block: "<<endl;
    for(int i=0;i<bsize;i++){
        cin>>blocks[i];

    }
    cout<<"Enter the size of the process: "<<endl;
    for(int i=0;i<psize;i++){
        cin>>process[i];

    }

}

void Memory::firstfit(){
    
    for(int i=0;i<bsize;i++){
        flag[i]=0; //denotes that memory block is free
    }
    map<int,int>mp; //blockno and size allocated process
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++){
        for(int j=0;j<bsize;j++){
            if(process[i]<=blocks[j] && flag[j]==0){
                mp[j]=process[i];
                flag[j]=1;
                break;
            }
        }
    }
    cout<<"Block No"<<setw(20)<<"Size of Block"<<setw(30)<<"Size of Process allocated"<<endl;
    for(it=mp.begin();it!=mp.end();it++){
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }
}
void Memory::bestfit(){
    for(int i=0;i<bsize;i++){
        flag[i]=0; //denotes that memory block is free
    }
    int wastage[bsize];

    map<int,int>mp; //blockno and size allocated process
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++){
        for(int k=0;k<bsize;k++){
            wastage[k]=0;
        }
        for(int j=0;j<bsize;j++){
            if(process[i]<=blocks[j] && flag[j]==0){
                wastage[j]=blocks[j]-process[i];
                // cout<<wastage[j]<<"  ";
            }
            else{
                wastage[j]=9999;
            }
        }
        int min=*min_element(wastage,wastage+bsize);
        int pos=find(wastage,wastage+bsize,min)-wastage;
        mp[pos]=process[i];
        flag[pos]=1;

    }
    cout<<"Block No"<<setw(20)<<"Size of Block"<<setw(30)<<"Size of Process allocated"<<endl;
    for(it=mp.begin();it!=mp.end();it++){
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }
    
}
void Memory::worstfit(){
    for(int i=0;i<bsize;i++){
        flag[i]=0; //denotes that memory block is free
    }
    int wastage[bsize];

    map<int,int>mp; //blockno and size allocated process
    map<int,int>::iterator it;
    for(int i=0;i<psize;i++){
        for(int k=0;k<bsize;k++){
            wastage[k]=0;
        }
        for(int j=0;j<bsize;j++){
            if(process[i]<=blocks[j] && flag[j]==0){
                wastage[j]=blocks[j]-process[i];
                cout<<wastage[j]<<"  ";
            }
            else{
                wastage[j]=0;
            }
        }
        int max=*max_element(wastage,wastage+bsize);
        int pos=find(wastage,wastage+bsize,max)-wastage;
        mp[pos]=process[i];
        flag[pos]=1;

    }
    cout<<"\nBlock No"<<setw(20)<<"Size of Block"<<setw(30)<<"Size of Process allocated"<<endl;
    for(it=mp.begin();it!=mp.end();it++){
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<endl;
    }
    
}
int main(){
    Memory m;
    m.input();
    //m.firstfit();
    //m.bestfit();
    m.worstfit();
    return 0;
}
