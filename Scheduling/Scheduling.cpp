#include<bits/stdc++.h>
using namespace std;


class process{
public:
 int at;
 int bt;
 int ct;
 int wt;
 int tat;
 int pr;
 process(int a,int b){
    at=a;
    bt=b;
    ct=0;
    wt=0;
    tat=0;
    pr=1;
 }
};
class Scheduling{

public:
void fcfs(vector<process*>v){
    int totalWt=0;
    v[0]->ct=v[0]->bt;
    for(int i=1;i<v.size();i++){
        v[i]->ct = v[i-1]->ct + v[i]->bt;
        v[i]->tat=v[i]->ct-v[i]->at;
        v[i]->wt=v[i]->tat - v[i]->bt;
        totalWt+=v[i]->wt;
    }
    display(v);
    cout<<"Average waiting time is : "<<totalWt/(double)v.size()<<endl;
}


void sjf(vector<process*>p){
    int k=p.size();
    int time=0;
    int curBt=p[0]->bt;
    int index=0;
    vector<process*>v;
    int totalWt=0;
    for(auto i:p){
        process *j=new process(i->at,i->bt);
        v.push_back(j);
    }
    bool check=false;
    while(k){
        for(int i=0;i<p.size();i++){
            if(v[i]->at<=time && v[i]->bt>0){
                if(v[i]->bt<v[index]->bt || v[index]->bt==0){
                    index=i;
                    check=true;
                }

            }
        }

        if(check==false){
            time++;
            continue;
        }

        v[index]->bt--;
        if(v[index]->bt==0){
            p[index]->ct=time+1;
            p[index]->tat=p[index]->ct-p[index]->at;
            p[index]->wt=p[index]->tat - p[index]->bt;
            if(p[index]->wt<0) p[index]->wt=0;
            totalWt+=p[index]->wt;
            check=false;
            k--;
        }
        time++;
    }

    display(p);
    cout<<"Average waiting time is : "<<totalWt/(double)v.size()<<endl;
}


void RoundRobin(vector<process*>v,int quant){
    int bt[v.size()];
    for(int i=0;i<v.size();i++){
        bt[i]=v[i]->bt;
    }

    int all=v.size();
    int ind=0;
    int time=0;
    int diff=1;
    bool flag=false;
    int totalWt=0;
    bool gt0=true;
    

    while(all){
        
        if(bt[ind]>0){
            if(v[ind]->at<=time){

            if(bt[ind]<quant){
                time+=bt[ind];
                bt[ind]=0;
            }
            else{
                bt[ind]-=quant;
                time+=quant;
            }
            flag=true;
            cout<<"ind="<<ind<<endl;
            cout<<"time="<<time<<endl;
            }
            
            gt0=true;
        }
        else if(bt[ind]<=0){
            gt0=false;
        }
        if(flag==false){
            
            if(gt0==false){
                ind=(ind+1)%v.size();
            }
            else{
                time++;
            }
            continue;
        }

        if(bt[ind]==0){
            all--;
            cout<<"complete :"<<ind<<" "<<time<<endl;
            v[ind]->ct=time;
            v[ind]->tat=v[ind]->ct-v[ind]->at;
            v[ind]->wt=v[ind]->tat - v[ind]->bt;
            totalWt+=v[ind]->wt;
            bt[ind]=-1;
            flag=false;
        }

        ind=(ind+1)%v.size();
        
    }

    display(v);
    cout<<"Average waiting time is : "<<totalWt/(double)v.size()<<endl;
}


void Priority(vector<process*>v){
    int time=0;
    int all=v.size();
    int mini=INT_MIN;
    int bt[v.size()];
    for(int i=0;i<v.size();i++){
        bt[i]=v[i]->bt;
    }
    int ind=0;
    int totalWt=0;
    bool flag=false;
    while(all){
        for(int i=0;i<v.size();i++){
            if(v[i]->pr>mini && bt[i]>0 && v[i]->at<=time){
                mini=v[i]->pr;
                ind=i;
                flag=true;
            }
        }

        if(flag==false){
            time++;
            continue;
        }

        if(bt[ind]){
            time+=bt[ind];
            bt[ind]=0;
            all--;
            v[ind]->ct=time;
            v[ind]->tat=v[ind]->ct-v[ind]->at;
            v[ind]->wt=v[ind]->tat - v[ind]->bt;
            if(v[ind]->wt<0) v[ind]->wt=0;
            totalWt+=v[ind]->wt;
            flag=false;
        }
    }
    display(v);
    cout<<"Average waiting time is : "<<totalWt/(double)v.size()<<endl;
}

void display(vector<process*>v){
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting time\n";
    for(int i=0;i<v.size();i++){

        cout<<"P"<<i<<"\t\t"<<v[i]->at<<"\t\t"<<v[i]->bt<<"\t\t"<<v[i]->ct<<"\t\t"<<v[i]->tat<<"\t\t"<<v[i]->wt<<"\n";
    }
}
};

int main(){
    vector<process*>p;
    int k=1;
    int a,b,pr;
    while(k){
        int cnt=p.size();
        cout<<"\nAT-"<<cnt<<": ";
        cin>>a;
        cout<<"BT-"<<cnt<<": ";
        cin>>b;
        // cout<<"Priority-"<<cnt<<": ";
        // cin>>pr;
        process* n=new process(a,b);
        // n->pr=pr;
        p.push_back(n);
        cout<<"\nEnter 0 to exit: ";
        cin>>k;
    }

    Scheduling s;
    s.RoundRobin(p,50);
    //s.sjf(p);
    //s.fcfs(p);
    //s.Priority(p);

}