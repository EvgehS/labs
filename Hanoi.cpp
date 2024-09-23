#include <iostream>

using namespace std;

void func(int n, int curr, int free, int target)
{
    if(n == 0)
        return;
    func(n - 1, curr, target, free);
    cout << curr << " -----> " << target << endl;
    func(n - 1, free, curr, target);
}

int main()
{
    func(3, 1, 2, 3);
    return 0;
}
