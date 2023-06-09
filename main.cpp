
#include <iostream>

using namespace std;

class Function{

    private:
        int a,b,c; // a b/c

    friend istream &operator>>(istream &s,Function &input);
    friend ostream &operator<<(ostream &s,Function p); 
};
istream &operator>>(istream &s,Function &input)
{
    input.a = 0; // init
    
    char c;
    string str;
    while( cin >> str )
    {
        int num = 0;
        bool slash = false;
        for(int i=0;i<str.size();i++)
        {
            if( str[i] >= '0' && str[i] <= '9' ) num *= 10 , num += str[i] - '0';
            if( str[i] == '/' ) input.b = num , num = 0 , slash = true;
        }

        if( slash == false ) // 分數還沒讀取完，現在只讀取到帶分數的數字而已
        {
            input.a = num;
            continue;
        } 
        else
        {
            input.c = num;
            break;
        }
    }

    return s;
}
ostream &operator<<(ostream &s, Function p) { 
    s << p.a << " " << p.b << " " << p.c;
    return s; 
} 
int main()
{
    Function x,y;
    cout << "請輸入兩個分數\n";
    cin >> x >> y;
    cout << x << " " << y << "\n";
    
}
