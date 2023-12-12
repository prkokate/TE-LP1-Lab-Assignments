#include <bits/stdc++.h>
using namespace std;

class mem{
    int size;
    bool fill;
public:
    mem(){
        size = 0;
        fill = 0;
    }

    mem(int s, bool f){
        size = s;
        fill = f;
    }

    friend class mem_man_algo;
};

class mem_man_algo{
    vector <mem> arr;
    int n;

public:

    mem_man_algo(){
        n = 0;
    }

    void input(){
        int p;
        bool q;
        cout<<"Enter number of Memory blocks : ";
        cin>>n;
        for(int i = 0;i<n;i++){
            cout<<"Enter Size : ";
            cin>>p;
            cout<<"Filled? - ";
            cin>>q;
            mem x(p,q);
            arr.push_back(x);
        }

        display();
    }

    void best_fit(int s){
        int i = 0,j = -1;
        int bf = 650000;
        while(i<n){
            if(arr[i].size >= s && arr[i].fill == 0){
                if(bf >= arr[i].size){
                    bf = arr[i].size;
                    j = i;
                }
            }
            i++;
        }
        if(arr[j].size > s){
            int curr = arr[j].size;
            arr[j].size -= s;
            mem ins(curr-arr[j].size,1);
            arr.insert(arr.begin()+j,ins);
        }
        else{
            arr[j].fill = 1;
        }

        display();
    }

    void first_fit(int s){
        int i = 0;
        int count = 0;
        while(i<arr.size()){
            if(arr[i].fill != 1 && arr[i].size >= s){
                if(count != 0){
                    count --;
                }
                else{
                    if(arr[i].size != s){
                        int curr = arr[i].size;
                        arr[i].size -= s;
                        mem ins(curr-arr[i].size,1);
                        arr.insert(arr.begin()+i,ins);
                    }
                    else{
                        //arr[i].size -= s;
                        arr[i].fill = 1;
                    }
                    break;
                }
            }
            i++;
        }

        display();
    }

    void next_fit(int s){
        int i = 0;
        int count = 1;
        while(i<arr.size()){
            if(arr[i].fill != 1 && arr[i].size >= s){
                if(count != 0){
                    count --;
                }
                else{
                    if(arr[i].size != s){
                        int curr = arr[i].size;
                        arr[i].size -= s;
                        mem ins(curr-arr[i].size,1);
                        arr.insert(arr.begin()+i,ins);
                    }
                    else{
                        //arr[i].size -= s;
                        arr[i].fill = 1;
                    }
                    break;
                }
            }
            i++;
        }
        //cout<<i;

        display();
    }

    void worst_fit(int s){
        int i = 0;
        int j = 0;
        int wf = s;
        while(i<n){
            if(s <= arr[i].size && arr[i].fill == 0){
                if(wf < arr[i].size){
                    wf = arr[i].size;
                    j = i;
                }
            }
            i++;
        }

        if(arr[j].size != s){
            int curr = arr[j].size;
            arr[j].size -= s;
            mem ins(curr-arr[j].size,1);
            arr.insert(arr.begin()+j,ins);
        }
        else{
            arr[j].fill = 1;
        }

        display();
    }

    void display(){
        for(int i = 0;i<arr.size();i++){
            if(arr[i].fill == 1)
                cout<<"="<<arr[i].size<<"=";
            else
                cout<<arr[i].size;
            cout<<endl;
        }
    }


};


int main(){
    mem_man_algo m;
    int ch,s, c = 1;

    while(c != 0){
        cout<<"OPTIONS :\n1) Input\n2) Best fit\n3) First fit\n4) Next fit\n5) Worst fit\n6) END\n\n Choice : ";
        cin>>ch;
        if(ch == 1){
            m.input();
            
            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 2){
            cout<<"Enter Value to Fit : ";
            cin>>s;
            m.best_fit(s);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 3){
            cout<<"Enter Value to Fit : ";
            cin>>s;
            m.first_fit(s);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 4){
            cout<<"Enter Value to Fit : ";
            cin>>s;
            m.next_fit(s);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 5){
            cout<<"Enter Value to Fit : ";
            cin>>s;
            m.worst_fit(s);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 6){
            cout<<"Thank you for using program :)";
            break;
        }

        else{
            cout<<"Invalid !!"<<endl;

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }
    }

    return 0;
}