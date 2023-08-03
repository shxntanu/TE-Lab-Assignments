#include <bits/stdc++.h>
using namespace std;

char exor(char a, char b) {
    if(a == b) return '0';
    else return '1';
}

void crc(char data[], char key[]) {
    int datalen = strlen(data);
    int keylen = strlen(key);

    for(int i=0; i<keylen-1;i++)
        data[datalen + i] = '0';
    
    data[datalen + keylen - 1] = '\0';

    int codelen = datalen + keylen - 1;

    char temp[50], rem[50];

    for(int i=0;i<keylen;i++)
        rem[i]=data[i];     

    for(int j = keylen; j<=codelen; j++) {
        for(int i=0;i<keylen;i++)
            temp[i] = rem[i];

        if(rem[0] == '0') {
            for(int i=0;i<keylen-1;i++)
                rem[i] = temp[i+1];
        }
        else {
            for(int i=0;i<keylen-1;i++)
                rem[i] = exor(temp[i+1], key[i+1]);
        }

        if(j!=codelen)
            rem[keylen-1] = data[j];
        else
            rem[keylen-1] = '\0';
    }
    
    for(int i=0;i<keylen-1;i++)
        data[datalen+i]=rem[i];

    data[codelen]='\0';
    cout<<"CRC="<<rem<<"\nDataword="<<data;
}

int main()
{
    char key[50],data[50];

    cout<<"Enter the data:";
    cin>>data;
    cout<<"Enter the key:";
    cin>>key;

    crc(data,key);                    

    return 0;
}
