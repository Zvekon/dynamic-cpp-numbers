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
        for (long long i = 0; i < n; i++) {
            this->x[i] = x % 256;
            x /= 256;
        }
    }

    dint(unsigned char *x, long long n) {
        this->n = n;
        this->x = new unsigned char[n];
        for (long long i = 0; i < n; i++) {
            this->x[i] = x[i];
        }
    }

    string to_string() {
        string s = "";
        for (long long i = 0; i < n; i++) {
            string c = "";
            for (int j = 7; j >= 0; j--) {
                c += ((x[i] >> j) & 1) ? '1' : '0';
            }
            s = c + s;
        }
        return s;
    }

    dint operator+(long long other) {
        return *this + dint(other);
    }

    dint operator+(dint other) {
        cout << "Adding: " << this->to_string() << " + " << other.to_string() << endl;
        long long maxN = max(this->n, other.n);
        unsigned char *resultX = new unsigned char[maxN];
        unsigned char carry = 0;

        for (long long i = 0; i < maxN; i++) {
            unsigned short sum = carry;

            if (i < this->n) {
                sum += this->x[i];
            }
            if (i < other.n) {
                sum += other.x[i];
            }
            cout << "Index: " << i << ", Sum: " << sum << ", Carry: " << static_cast<int>(carry) << endl;

            resultX[i] = static_cast<unsigned char>(sum % 256);
            carry = static_cast<unsigned char>(sum / 256);
        }

        if (carry > 0) {
            resultX[maxN] = carry;
            maxN++;
        }

        dint result(0);
        delete[] result.x;
        result.n = maxN;
        result.x = resultX;
        return result;
    }
};

int main() {
    dint a = 9223372036854775807L;
    dint b = 9223372036854775807L;
    a = a + b;
    a = a + 2;
    cout << a.to_string() << endl;
    return 0;
}