#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    cout <<setw(60)<<"JANU�R"<<endl;
    cout<<endl;
    const string het_napjai[] = { "h�tf�","kedd","szerda","cs�t�rt�k","p�ntek","szombat","vas�rnap" };
    for(int i=0;i<7;i++)
        cout<<setw(15)<<het_napjai[i]<<" ";
    cout<<endl;
    for(int i=1;i<32;i++){
        cout<<setw(15)<<i;
        if(i%7==0) {
            cout<<endl;
         for(int j=0;j<7;j++)
            if(j%2==0) cout<<setw(15)<<"*";
                   else cout<<setw(15)<<" ";
         cout<<endl<<endl;
    }

    }

}
