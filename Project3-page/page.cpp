#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include<vector>
#include <string>
#include <map>
#include<queue>
#include<deque>
using namespace std;
typedef struct data
{
    char trans[5];
}data;
vector<string> v;
data s;
string getdata;
int main()
{
    FILE *fp;
    int ch;
    fp=fopen("trace.txt","r");
    char temp_data[10];
    while(fgets(temp_data , 10 , fp))
    {
        for(int i=0;i<=4;i++)
        {
            s.trans[i]=temp_data[i];
        }
            getdata=s.trans;
        v.push_back(getdata);
    }
    fclose(fp);
    //FIFO
    cout<<"FIFO---"<<endl<<"size    miss    hit          page fault ratio"<<endl;
    for(int fsize=64;fsize<=512;fsize*=2)
    {
        int cou=0,hit=0,miss=0;
        string fiout;
        map<string,int> fifo;
        map<string,int>::iterator it;
        queue<string> recque;
        while(cou<=v.size()-1)
        {
        if(fifo.count(v[cou])==0)
        {
            if(fifo.size()!=fsize)
            {
                fifo.insert(pair<string,int>(v[cou],0));
                recque.push(v[cou]);
                miss++;
            }
            else if(fifo.size()==fsize)
            {
                recque.push(v[cou]);
                fifo.insert(pair<string,int>(v[cou],0));
                miss++;
                it=fifo.find(recque.front());
                fifo.erase (it);
                recque.pop();
            }
        }
        else if(fifo.count(v[cou])==1)
        {
            hit++;
        }
        cou++;
        }
        if(fsize==64)cout<<fsize<<"      "<<miss<<"   "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==128)cout<<fsize<<"     "<<miss<<"    "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==256)cout<<fsize<<"     "<<miss<<"    "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==512)cout<<fsize<<"     "<<miss<<"     "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
    }
    //LRU
    cout<<endl<<"LRU---"<<endl<<"size    miss    hit          page fault ratio"<<endl;
    for(int fsize=64;fsize<=512;fsize*=2)
    {
        int cou=0,hit=0,miss=0,deqcou=0,j=0;
        map<string,int> lru;
        map<string,int>::iterator it;
        deque<string> recdeq;
        while(cou<=v.size()-1)
        {
            if(lru.count(v[cou])==0)
            {
                if(lru.size()!=fsize)
                { 
                    lru.insert(pair<string,int>(v[cou],deqcou));

                    recdeq.push_back(v[cou]);
                    miss++;
                    deqcou++;
                }
                else if(lru.size()==fsize)
                {
                    j=1;
                    while(j<recdeq.size())
                    {
                        lru[recdeq[j]]--;
                        j++;
                    }
                    it=lru.find(recdeq.front());
                    lru.erase(it);
                    recdeq.pop_front();
                    recdeq.push_back(v[cou]);
                    lru.insert(pair<string,int>(v[cou],recdeq.size()-1/*0*/));
                    miss++;
                }
            }
            else if(lru.count(v[cou])==1)
            {
                hit++;
                j=lru[v[cou]]+1;
                while(j<=recdeq.size()-1)
                {
                    lru[recdeq[j]]--;
                    j++;
                }
                recdeq.erase(recdeq.begin()+lru[v[cou]]);
                recdeq.push_back(v[cou]);
                lru[v[cou]]=recdeq.size()-1;
            }
            cou++;
        }
        recdeq.clear();
        lru.clear();
        if(fsize==64)cout<<fsize<<"      "<<miss<<"    "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==128)cout<<fsize<<"     "<<miss<<"    "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==256)cout<<fsize<<"     "<<miss<<"    "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
        else if(fsize==512)cout<<fsize<<"     "<<miss<<"     "<<hit<<"     "<<((double)miss/(double)cou)<<endl;
    }
    return 0;
}
