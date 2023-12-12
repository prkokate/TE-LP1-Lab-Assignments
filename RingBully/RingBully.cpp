#include<bits/stdc++.h>
using namespace std;


int coordinator,n;
int process[20];


void display(){
    cout<<"Process *"<<coordinator<<"* is the cordinator"<<endl;
    cout<<"Process\tActive status\n";
    for(int i=0;i<n;i++){
        cout<<i<<"\t  "<<process[i]<<endl;
    }
}
void Bully(){
    int c;
    while(c!=4){
        cout<<"1)Crash\n2)Activate\n3)Display\n4)Exit\n==> ";
        cin>>c;
        switch (c)
        {
        case 1:
           { cout<<"Enter process to crash : ";
            int crash;
            cin>>crash;
            if(process[crash]==0) {
                cout<<"Already crashed!";
                break;
            }
            process[crash]=0;
            if (crash==coordinator){
                cout<<"Enter generator id : ";
                int gid;
                cin>>gid;
                while(gid==coordinator || process[gid]==0){
                    cout<<"Enter a valid generator id ! : ";
                    cin>>gid;
                }
                int flag=0;
                int sub=gid;
                for(int i=gid+1;i<n;i++){
                    cout<<"Message sent from "<<gid<<" to"<<i<<endl;
                    if(process[i]){
                        cout<<"Acknowledgement from "<<i<<endl;
                        sub=i;
                        flag=1;
                    }
                }

                coordinator=sub;
                display();
            }
            break;}

        case 2:
           {cout<<"Enter process to activate : ";
           int activate;
           cin>>activate;
           if(process[activate]==1) {
            cout<<"Already active!";
            break;
           }
           process[activate]=1;
           int newcor=activate;
           for(int i=activate+1;i<n;i++){
            cout<<"Message sent from "<<activate<<" to"<<i<<endl;
            if(process[i]){
                cout<<"Acknowledgement from "<<i<<endl;
                newcor=max(newcor,i);
            }
           }
           coordinator=newcor;
           display();
           break;
}
        case 3:
           display();
           break;
        
        default:
            break;
       
        }
    }
}

bool check(vector<int>v,int x){
    for(int i=0;i<v.size();i++){
        if(v[i]==x) return true;
    }
    return false;
}
void Ring(){
    int c;
    while(c!=4){
        cout<<"1)Crash\n2)Activate\n3)Display\n4)Exit\n==> ";
        cin>>c;
        switch (c)
        {
        case 1:
           { cout<<"Enter process to crash : ";
            int crash;
            cin>>crash;
            if(process[crash]==0) {
                cout<<"Already crashed!";
                break;
            }
            process[crash]=0;
            if (crash==coordinator){
                cout<<"Enter generator id : ";
                int gid;
                cin>>gid;
                while(gid==coordinator || process[gid]==0){
                    cout<<"Enter a valid generator id ! : ";
                    cin>>gid;
                }
                int flag=1;
                // int sub=gid;
                vector<int>election;
                election.push_back(gid);
                int next=gid;
                int sender=next;
                while(flag){
                    cout<<"Message sent from "<<sender;
                    next=(next+1)%n;
                    cout<<" to"<<next<<endl;
                    if(check(election,next)){
                        flag=0;
                        break;
                    }
                    
                    if(process[next]){
                        cout<<"-------Acknowledgement from "<<next<<"----------"<<endl;
                        election.push_back(next);
                        sender=next;
                        // sub=next;
                        // flag=1;
                    }
                }
                sort(election.begin(),election.end());
                coordinator=election[election.size()-1];
                display();
            }
            break;}

        case 2:
           {cout<<"Enter process to activate : ";
           int activate;
           cin>>activate;
           if(process[activate]==1) {
            cout<<"Already active!";
            break;
           }
           process[activate]=1;
           int flag=1;
           vector<int>election;
           election.push_back(activate);
           int next=activate;
           int sender=next;
           while(flag){
            cout<<"Message sent from "<<sender;
            next=(next+1)%n;
            cout<<" to"<<next<<endl;
            if(check(election,next)){
                flag=0;
                break;
            }

            
            if(process[next]){
                 cout<<"-------Acknowledgement from "<<next<<"----------"<<endl;
                 election.push_back(next);
                 sender=next;
            }
           }
           sort(election.begin(),election.end());
           coordinator=election[election.size()-1];
           display();
           break;
}
        case 3:
           display();
           break;
        
        default:
            break;
       
        }
    }
}


int main(){
    cout<<"Enter no. of processes: ";
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter 1 if process "<<i<<" is active, else 0 :";
        cin>>process[i];
        if(process[i]){
            coordinator=i;
        }
    }

    int c=1;
    while(c){
        cout<<"1)Bully\n2)Ring\n0 to exit\n==> ";
        cin>>c;
        switch (c) {
            case 1:{
                Bully();
            }
            case 2:{
                Ring();
            }
            default:
               break;
        }
    }

}

