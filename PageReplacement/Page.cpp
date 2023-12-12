#include<bits/stdc++.h>
using namespace std;

bool hit(vector<int> arr, int temp)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == temp)
        {
            return true;
        }
    }
    return false;
}

bool ispr(vector<int> arr, int temp, int j)
{
    for (int i = j; i < arr.size(); i++)
    {
        if (arr[i] == temp)
        {
            return true;
        }
    }
    return false;
}

void display(vector<int> arr, int s)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] != -1)
        {
            if (i == s)
                cout << arr[i] << "*"
                     << " ";
            else
                cout << arr[i] << " ";
        }
    }
}

void fifo(vector<int> arr, int size)
{
    vector<int> block(size);
    for(int i = 0;i<block.size();i++){
        block[i] = -1;
    }
    int i = 0;
    int j = 0;
    int h = 0, m = 0;
    int ind = 0;

    while (i < arr.size())
    {
        int k = 0;
        if (!hit(block, arr[i]))
        {
            ind = j % size;
            block[ind] = arr[i];
            display(block, -1);
            cout << " miss";
            j++;
            m++;
        }
        else
        {
            //cout<<"ind = "<<ind;
            while(k<block.size()){
                if(block[k] == arr[i]){
                    break;
                }
                k++;
            }
            display(block, k);
            cout << " hit";
            h++;
        }
        i++;
        cout<<endl;
    }
    cout<<"Total Page faults : "<<m<<endl;
    cout<<"Miss Ratio : "<<m<<"/"<<arr.size()<<endl;
    cout<<"Hit Ratio : "<<h<<"/"<<arr.size()<<endl;
}

void lru(vector<int> arr, int size)
{
    vector<int> block(size);
    for(int i = 0;i<block.size();i++){
        block[i] = -1;
    }
    int i = 0;
    int j = 0;
    int h = 0, m = 0;
    int temp = -1;
    int ind = 0;

    while (i < arr.size())
    {
        int k = 0;
        if (!hit(block, arr[i]))
        {
            ind = j % size;
            if (ind != temp)
            {
                block[ind] = arr[i];
                display(block, -1);
                cout << " miss";
                j++;
                m++;
            }
            else
            {
                j++;
                ind = j % size;
                block[ind] = arr[i];
                display(block, -1);
                cout << " miss";
                j++;
                m++;
            }
        }
        else
        {
            while(k<block.size()){
                if(block[k] == arr[i]){
                    break;
                }
                k++;
            }
            temp = k;
            display(block, k);
            cout << " hit";
            h++;
        }
        i++;
        cout<<endl;
    }
    cout<<"Total Page faults : "<<m<<endl;
    cout<<"Miss Ratio : "<<m<<"/"<<arr.size()<<endl;
    cout<<"Hit Ratio : "<<h<<"/"<<arr.size()<<endl;
}

void opt(vector<int> arr, int size)
{
    vector<int> block(size);
    for(int i = 0;i<block.size();i++){
        block[i] = -1;
    }
    int i = 0;
    int j = 0;
    int h = 0, m = 0;
    int ind = 0;

    while(i < block.size()){
        block[i] = arr[i];
        display(block,-1);
        cout<<" miss";
        i++;
        m++;
        cout<<endl;
    }

    while (i < arr.size())
    {
        int k = 0;
        if (!hit(block, arr[i]))
        {
            while(ispr(arr,block[ind],i)){
                ind = j % size;
                j++;
            }
            block[ind] = arr[i];
            display(block, -1);
            cout << " miss";
            j++;
            m++;
        }
        else
        {
            while(k<block.size()){
                if(block[k] == arr[i]){
                    break;
                }
                k++;
            }
            display(block, k);
            cout << " hit";
            h++;
        }
        i++;
        cout<<endl;
    }
    cout<<"Total Page faults : "<<m<<endl;
    cout<<"Miss Ratio : "<<m<<"/"<<arr.size()<<endl;
    cout<<"Hit Ratio : "<<h<<"/"<<arr.size()<<endl;
}

void mru(vector<int> arr,int size){
    vector<int> block(size);
    for(int i = 0;i<block.size();i++){
        block[i] = -1;
    }
    int i = 0;
    int j = 0;
    int h = 0, m = 0;
    int temp = -1;
    int ind = 0;

    while (i < arr.size())
    {
        int k = 0;
        if (!hit(block, arr[i]))
        {
            ind = j % size;
            if (temp == -1)
            {
                block[ind] = arr[i];
                display(block, -1);
                cout << " miss";
                j++;
                m++;
            }
            else
            {
                j = temp;
                ind = j % size;
                block[ind] = arr[i];
                display(block, -1);
                cout << " miss";
                j++;
                m++;
                temp = -1;
            }
        }
        else
        {
            while(k<block.size()){
                if(block[k] == arr[i]){
                    break;
                }
                k++;
            }
            temp = k;
            display(block, k);
            cout << " hit";
            h++;
        }
        i++;
        cout<<endl;
    }
    cout<<"Total Page faults : "<<m<<endl;
    cout<<"Miss Ratio : "<<m<<"/"<<arr.size()<<endl;
    cout<<"Hit Ratio : "<<h<<"/"<<arr.size()<<endl;
}

int main()
{
    int n, size;
    cout << "Enter number of Frames in one block : ";
    cin >> size;
    cout << "Enter number of Entries : ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter Entries : ";
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        arr[i] = temp;
    }

    int ch,s, c = 1;

    while(c != 0){
        cout<<"OPTIONS :\n1) FIFO\n2) LRU\n3) OPTIMAL\n4) MRU\n5) END\n\n Choice : ";
        cin>>ch;

        if(ch == 1){
            fifo(arr,size);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 2){
            lru(arr,size);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 3){
            opt(arr,size);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 4){
            mru(arr,size);

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }

        else if(ch == 5){
            cout<<"Thank you for using program :)";
            break;
        }

        else{
            cout<<"Invalid !!"<<endl;

            cout<<"Do you want to continue (0/1) : ";
            cin>>c;
        }
    }
}