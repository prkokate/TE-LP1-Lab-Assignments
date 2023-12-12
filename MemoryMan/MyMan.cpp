#include<bits/stdc++.h>
using namespace std;

class mem{
    int size;
    bool fill;
public:
friend class MemMan;

mem(int s,bool f){
    size=s;
    fill=f;
}

};

class MemMan{
    int n;
    // vector<mem>v={{100,0},{500,0},{200,0},{300,0},{600,0}};
     vector<mem>v={{5,0},{10,0},{20,0}};
     int nextPtr=-1;
public:

    void input(){
        int k=1,s,f;
        while(k){
            cout<<"Enter size: ";
            cin>>s;
            cout<<"Filled?- ";
            cin>>f;
            v.push_back({s,f});
            cout<<"\nContinue? : ";
            cin>>k;

        }
    }
   
   void bestFit(int x){
    int bf=INT_MAX;
    int j=-1;
    for (int i = 0; i < v.size(); ++i) {
        //cout<<"YES"<<endl;
        if(v[i].size>=x && v[i].fill==0){
            if(bf>v[i].size){
                bf=v[i].size;
                j=i;
            }
        }
    }

    if(v[j].size>x){
        //int sz=v[j].size;
        v[j].size-=x;
        mem l(x,1);
        v.insert(v.begin()+j,l);
    }
    else{
        v[j].fill=1;
    }

    display();

   }



    void worstFit(int x){
    int bf=INT_MIN;
    int j=-1;
    bool flag=false;
    for (int i = 0; i < v.size(); ++i) {
        //cout<<"YES"<<endl;
        if(v[i].size>=x && v[i].fill==0){
            if(bf<v[i].size){
                bf=v[i].size;
                j=i;
            }
            flag=true;
        }
    }

    if(flag==false){
        cout<<"========================Not allocated!!!======================="<<endl;
        return;
    }

    if(v[j].size>x){
        //int sz=v[j].size;
        v[j].size-=x;
        mem l(x,1);
        v.insert(v.begin()+j,l);
    }
    else{
        v[j].fill=1;
    }

    display();

   }



   void firstFit(int x){
    int j=0;
    int flag=false;
    for (int i = 0; i < v.size(); ++i) {
        //cout<<"YES"<<endl;
        if(v[i].size>=x && v[i].fill==0){
                j=i;
                flag=true;
                break;
        }
    }

    if(flag==false){
        cout<<"=================Not allocated!!============="<<endl;
        return;
    }

    if(v[j].size>x){
        //int sz=v[j].size;
        v[j].size-=x;
        mem l(x,1);
        v.insert(v.begin()+j,l);
    }
    else{
        v[j].fill=1;
    }

    display();

   }


  void nextFit(int x){
    int j=0;
    int flag=false;
    for (int i = (nextPtr+1)%v.size(); i != nextPtr; i=(i+1)%v.size()) {
        // if(i==v.size()){
        //     i=i%v.size();
        // }
        if(v[i].size>=x && v[i].fill==0){
                j=i;
                nextPtr=i;
                flag=true;
                break;
        }
    }
    // int temp=j;
    // for (int i = (j+1)%v.size(); i < v.size(); i=(i+1)%v.size()) {
    //     //cout<<"YES"<<endl;
    //     if(i==temp){
    //         break;
    //     }
    //     if(v[i].size>=x && v[i].fill==0){
    //             j=i;
    //             flag=true;
    //             break;
    //     }
        
    // }

    if(flag==false){
        cout<<"=================Not allocated!!============="<<endl;
        return;
    }

    if(v[j].size>x){
        
        v[j].size-=x;
        mem l(x,1);
        v.insert(v.begin()+j,l);
    }
    else{
        
        v[j].fill=1;
    }

    display();

   }

   void display(){
    for(int i=0;i<v.size();i++){
        if(v[i].fill==1){
            cout<<"="<<v[i].size<<"="<<endl;
        }
        else{
            cout<<v[i].size<<endl;
        }
    }
   }
};


int main(){
    MemMan m;
    //m.input();
    int k=1;
    int s;
    while(k){
        cout<<"Enter the size of memory block to be allocated: ";
        cin>>k;
        if(k>0){
        //m.bestFit(k);
        // m.firstFit(k);
        // m.worstFit(k);
        m.nextFit(k);
        }
    }
}

