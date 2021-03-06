#include <bits/stdc++.h>
using namespace std;

int buff_size;
int page_size;
int num_records;
int num_pages;

int logb(int b, int x) {
    int ans = 0;
    int t = x;
    while (x > 0) {
        x /= b;
        ans++;
    }
    if(pow(b, ans) == t) {
        ans--;
    }
    return ans;
}

class Page
{
public:
    vector<int> data;
    int page_id;
    Page *next;
    Page *prev;
    Page(int s)
    {
        this->next = NULL;
        this->prev = NULL;
        this->page_id = s;
    }
};

Page **pages;

class buffer
{
public:
    Page **buff_pages=new Page*[buff_size-1];
    Page *output_page=new Page(buff_size-1);
    buffer()
    {
        for(int i=0;i<buff_size-1;i++)
        {
            buff_pages[i]=new Page(i);
        }
    }
};

buffer buff();

void ext_sort()
{
    int z=buff_size;
    int c = logb(buff_size-1, num_pages/buff_size + ((num_pages%buff_size)?1:0)) + 1;
    cout<<c<<"hi"<<endl;
    for(int i=0;i<c;i++){
        for(int j=0;j<num_pages;j+=z){
            int l = j + z -1;
            l = min(num_pages-1, l);
            vector<int> temp;
            for(int k=j;k<=l;k++){
                temp.insert(temp.end(), pages[k]->data.begin(), pages[k]->data.end());
            }
            sort(temp.begin(),temp.end());
            int cc=0;
            for(int k=j;k<=l;k++){
                for(int y=0;y<pages[k]->data.size();y++){
                    pages[k]->data[y]=temp[cc];
                    cc++;
                }
            }
        }
        z*=(buff_size-1);
    }
}

int main()
{
    cin >> buff_size >> page_size >> num_records;
    num_pages = num_records/page_size + (num_records%page_size==0?0:1);
    pages = new Page*[num_pages];
    int counter=0;
    for(int i=0;i<num_pages;i++)
    {
        pages[i] = new Page(i);
        for(int j=0;j<page_size && counter<num_records;j++)
        {
            int k;
            cin>>k;
            pages[i]->data.push_back(k);
            counter++;
        }
    }

    ext_sort();

    //output
    for(int i=0;i<num_pages;i++)
    {
        for(int j=0;j<pages[i]->data.size();j++)
        {
            cout<<pages[i]->data[j]<<endl;
        }
    }
    
}