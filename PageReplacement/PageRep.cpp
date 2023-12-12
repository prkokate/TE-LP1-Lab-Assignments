#include<bits/stdc++.h>
using namespace std;

class PageRep{
public:

bool hit(vector<int>v,int x){
    for(int i=0;i<v.size();i++){
        if(v[i]==x) return true;
    }
    return false;
}

void display(vector<int>v,int c){
    for(int i=0;i<v.size();i++){
        if(v[i]!=-1){
            cout<<v[i];
            if(i==c){
                cout<<"* ";
            }
            else{
                cout<<" ";
            }
        }
    }
}

void fifo(vector<int>v,int size){
   vector<int>frame(size,-1);
   int ind=0,j=0,h=0,m=0;

   for(int i=0;i<v.size();i++){
      if(!hit(frame,v[i])){
        ind=j%size;
        frame[ind]=v[i];
        j++;
        m++;
        display(frame,-1);
        cout<<"miss\n";
      }
      else{
        h++;
        for(int k=0;k<frame.size();k++){
            if(frame[k]==v[i]){
                display(frame,k);
                break;
            }
        }
        cout<<"hit\n";
      }
   }
   cout<<"\nNumber of page faults = "<<m<<endl;
   cout<<"\nNumber of hits = "<<h<<endl;
   cout<<"Page fault ratio = "<<m<<"/"<<v.size()<<endl;
}


void lru(vector<int>v,int size){
    vector<int>frame(size,-1);
   int ind=0,j=0,h=0,m=0,temp=-1;

   for(int i=0;i<v.size();i++){

      if(!hit(frame,v[i])){
        ind=j%size;
        if(ind!=temp){
            frame[ind]=v[i];
            
        }
        else{
            j++;
            ind=j%size;
            frame[ind]=v[i];
           
        }
        j++;
        m++;
        display(frame,-1);
        cout<<"miss\n";
      }
      else{
        h++;
        for(int k=0;k<frame.size();k++){
            if(frame[k]==v[i]){
                display(frame,k);
                temp=k;
                break;
            }
        }
        cout<<"hit\n";
      }
   }
   cout<<"\nNumber of page faults = "<<m<<endl;
   cout<<"\nNumber of hits = "<<h<<endl;
   cout<<"Page fault ratio = "<<m<<"/"<<v.size()<<endl;
}


int ispr(vector<int>v,int ind,int x){

    for(int i=ind;i<v.size();i++){
        if(v[i]==x) return i;
    }
    return -1;
}

int farthest(vector<int>frame,vector<int>v,int ind){
      
    int maxi=INT_MIN;
    int index=0;
    for(int i=0;i<frame.size();i++){
        if(ispr(v,ind,frame[i])==-1){
            return i;
        }
        if(ispr(v,ind,frame[i])>maxi){
            maxi=ispr(v,ind,frame[i]);
            index=i;
        }
    }

  return index;

 

}


void opt(vector<int>v,int size){
    vector<int>frame(size,-1);
   int ind=0,j=0,h=0,m=0;

   for(int i=0;i<v.size();i++){

      if(!hit(frame,v[i])){
        
        // ind=j%size;
        ind=farthest(frame,v,i);
        frame[ind]=v[i];
        // j++;
        m++;
        display(frame,-1);
        cout<<"miss\n";
      }
      else{
        h++;
        for(int k=0;k<frame.size();k++){
            if(frame[k]==v[i]){
                display(frame,k);
                break;
            }
        }
        cout<<"hit\n";
      }
   }
   cout<<"\nNumber of page faults = "<<m<<endl;
   cout<<"\nNumber of hits = "<<h<<endl;
   cout<<"Page fault ratio = "<<m<<"/"<<v.size()<<endl;
}


//Most Recently Used
void mru(vector<int>v,int size){
   vector<int>frame(size,-1);
   int ind=0,j=0,h=0,m=0,temp=-1;

   for(int i=0;i<v.size();i++){

      if(!hit(frame,v[i])){
        if(temp!=-1){
          while(ind!=temp){
            ind=j%size;
            j++;
        }
        }
        else{
            ind=j%size;
            j++;
        }
        
       frame[ind]=v[i];   

       // j++;
        m++;
        display(frame,-1);
        cout<<"miss\n";
      }
      else{
        h++;
        for(int k=0;k<frame.size();k++){
            if(frame[k]==v[i]){
                display(frame,k);
                temp=k;
                break;
            }
        }
        cout<<"hit\n";
      }
   }
   cout<<"\nNumber of page faults = "<<m<<endl;
   cout<<"\nNumber of hits = "<<h<<endl;
   cout<<"Page fault ratio = "<<m<<"/"<<v.size()<<endl;
}


};


int main(){
    PageRep p;
    //vector<int>v={6,7,8,9,6,7,1,6,7,8,9,1,7,9,6};
    vector<int>v={7,0,1,2,0,3,0,4,2,3,0,3,2,3};
    int size=4;
    p.mru(v,size);
}