#include<bits/stdc++.h>
using namespace std;


class Semaphore{

int rcnt;
int rwt;
int wrt;
int mutex;
public:
  Semaphore(){
    mutex=1;
    rcnt = 0;
    rwt = 0;
    wrt=0;
  }

  void addReader(Semaphore *s){
    if(s->mutex==0 && s->rcnt==0){
        cout<<"\n=============File open in write mode!!=================\n";
        s->rwt++;
        cout<<"!! "<<s->rwt<<" Reader(s) added to queue............. !!\n";
    }
    else{
        cout<<"\n===============New Reader added!==============\n";
        s->mutex--;
        s->rcnt++;
        cout<<s->rcnt<<" Reader(s) to process....\n";
    }
    return;
    
  }

  void addWriter(Semaphore *s){
    if(s->mutex==1){
        cout<<"\n=============Writer Added!!=================\n";
        s->wrt++;
        s->mutex--;
    }
    else if(s->wrt){
        cout<<"\n=============Writer process already executing!!=================\n";
    }
    else{
        cout<<"\n===============File open in Read mode!!====================\n";
    }
    return;
  }


  void remReader(Semaphore *s){
    if(s->rcnt==0){
        cout<<"\n=============No readers to remove!!==============\n";
    }
    else{
        cout<<"\n=============Reader removed!!!==============\n";
        s->rcnt--;
        s->mutex++;
        cout<<s->rcnt<<" Reader(s) left to process....\n";
    }
    return;
  }

  void remWriter(Semaphore *s){
    if(s->wrt==0){
        cout<<"\n=============No writers to remove!!==============\n";
    }
    else{
        cout<<"\n=============Writer Removed!!====================\n";
        s->wrt--;
        s->mutex++;
        if(s->rwt){
            s->rcnt=s->rwt;
            s->rwt=0;
            s->mutex-=s->rcnt;
            cout<<"\n==============="<<s->rcnt<<" Reader(s) processes in queue!==================\n";
        }
    }
    return;
  }
};


int main(){
    Semaphore *s=new Semaphore;
    int c=1;
    while(c){
        cout<<"\nEnter choice: ";
        cin>>c;

        switch (c)
        {
        case 1:{
            s->addReader(s); 
            break;
        }
         case 2:{
            s->addWriter(s); 
            break;
        }
         case 3:{
            s->remReader(s); 
            break;
        }
         case 4:{
            s->remWriter(s); 
            break;
        }
           
        
        default:
            break;
        }

    }
}