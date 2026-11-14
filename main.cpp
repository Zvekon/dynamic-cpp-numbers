#include <iostream>

using namespace std;

struct dint {
    long long n;
    unsigned char *x;

    dint(long long x = 0) {
        this->n = 0;
        long long temp = x;
        do {
            this->n++;
            temp /= 256;
        } while (temp > 0);
        this->x = new unsigned char[n];
        for (long long i = n - 1 ; i >= 0; i--) {
            this->x[i] = x % 256;
            x /= 256;
        }
    }

    string to_string() {
        string s = "";
        for (long long i = n - 1; i >= 0; i--) {
            string c = "";
            for (int j = 7; j >= 0; j--) {
                c += ((x[i] >> j) & 1) ? '1' : '0';
            }
            s = c + s;
        }
        return s;
    }
};

int main() {
    dint a = 2147483647L;
    cout << a.to_string() << endl;
    return 0;
}