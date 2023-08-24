#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
   int next_seq_num, window_size, frame_size;
   cout<<"Enter the window size";
   cin>>window_size;
   cout<<"Enter the frame size:";
   cin>>frame_size;
   int frame[frame_size];
   for(int i=0; i<frame_size; i++)
   frame[i]=i;
   int send[window_size], receive[window_size], acked[frame_size], total_transmissions=0;
   for(int i=0; i<frame_size; i++)
   {
       acked[i]=-1;
   }
   for(int i=0; i<window_size; i++)
   {
      send[i]=-1;
      receive[i]=-1;
   }
   int i=0, k=0, p=0;
   while(i<frame_size)
   {
       int flag=1, j;
       for(j=0; j<=(i-window_size); j++)
       {
           if(acked[j]==0)
           {
               cout<<"Timeout for frame "<<j<<". Retransmitting frame "<<j<<endl;
               flag=0;
               break;
           }
      }
      if(flag==0)
      {
         int temp=i;
         i=j;
         int rn=rand()%5;
         // packet is lost or corrupted
         if(rn==2)
         {
            acked[i]=0;
            cout<<"Frame "<<" is lost or corrupted"<<endl;
            total_transmissions++;
            i=temp;
         }
         else
         {
            cout<<"Frame "<<i<<" is sent"<<endl;
            receive[p]=frame[i];
            cout<<"Frame "<<i<<" is received"<<endl;
            acked[i]=1;
            cout<<"Ack is sent for frame "<<i<<endl;
            total_transmissions++;
            total_transmissions++;
            i=temp;
            if(p==window_size-1)
            p=0;
            else
            p++;
         }
      }
      else
      {
          int rn=rand()%5;
          //packet is lost or corrupted
          if(rn==2)
          {
             acked[i]=0;
             cout<<"Frame "<<i<<" is lost or corrupted."<<endl;
             send[k]=frame[i];
             total_transmissions++;
             i++;
             if(k==window_size-1)
             k=0;
             else
             k++;
          }
         else
         {
             send[k]=frame[i];
             cout<<"Frame "<<i<<" is sent"<<endl;
             receive[p]=frame[i];
             cout<<"Frame "<<i<<" is received."<<endl;
             acked[i]=1;
             cout<<"Ack is sent for frame "<<i<<endl;
             total_transmissions++;
             total_transmissions++;
             i++;
             if(k==window_size-1)
             k=0;
             else
             k++;
             if(p==window_size-1)
             p=0;
             else
             p++;
         }
      }
      cout<<"Sender Window:"<<endl;
      for(int l=0; l<window_size; l++)
      {
          if(send[l]!=-1)
          cout<<send[l]<<"      ";
      }
       cout<<endl;
       cout<<"Receiver Window:"<<endl;
       for(int l=0; l<window_size; l++)
       {
            if(receive[l]!=-1)
            cout<<receive[l]<<"       ";
       }
       cout<<endl;
   }
   cout<<"Total number of transmissions are "<<total_transmissions<<endl;
   return 0;
}
