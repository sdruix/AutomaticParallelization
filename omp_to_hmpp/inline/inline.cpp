#include <iostream>
int r = 2;
int g(int a, int b)
{
    int c=2;
    int ret = a + b + c + r * 2;
    return ret;
}
int f(int a)
{
    int ret = a + 1;
    return ret;
}
int main()
{
    int l;
    l = 0;
    std::cout<<"L value before inline function: "<<l<<"\n";
    l = ({
        int _p_0 = (3);
        int _p_1 = (6);
	int c=2;
        int _return;
        {
            int ret = _p_0 + _p_1 + c + r * 2;
            _return = (ret);
        }
        _return;
    }) + ({
        int _p_0 = (1);
        int _return;
        {
            int ret = _p_0 + 1;
            _return = (ret);
        }
        _return;
    });
    l = l + 1;
    std::cout<<"L value after inline function: "<<l<<"\n";
    return 1;
}
