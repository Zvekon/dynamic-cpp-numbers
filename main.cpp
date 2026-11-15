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

    dint(const dint &other) : n(other.n), x(new unsigned char[other.n]) {
        for (long long i = 0; i < n; i++) {
            x[i] = other.x[i];
        }
    }

    dint &operator=(const dint &other) {
        if (this != &other) {
            unsigned char *newX = new unsigned char[other.n];
            for (long long i = 0; i < other.n; i++) {
                newX[i] = other.x[i];
            }
            delete[] x;
            n = other.n;
            x = newX;
        }
        return *this;
    }

    ~dint() {
        delete[] x;
    }

    dint(const unsigned char *x, long long n) {
        this->n = n;
        this->x = new unsigned char[n];
        for (long long i = 0; i < n; i++) {
            this->x[i] = x[i];
        }
    }

    string to_string(char base = 10) {
        if (base < 2 || base > 36) {
            throw invalid_argument("Base must be between 2 and 36");
        }

        if (n == 0) {
            return "0";
        }

        string result = "";
        dint temp(*this);
        long long i = -1;
        do {
            i++;
            char remainder = temp % base;
            char digit = (char)(remainder < 10 ? '0' + remainder : 'A' + (remainder - 10));
            if (i % 3 == 0 && temp > 0) {
                result = " " + result;
            }
            result = digit + result;
            temp = temp / base;
        } while (temp > 0);
        return result;
    }

    dint operator+(long long other) {
        return *this + dint(other);
    }

    dint operator+(dint other) {
        // cout << "Adding: " << this->to_string() << " + " << other.to_string() << endl;
        long long maxN = max(this->n, other.n);
        unsigned char *resultX = new unsigned char[maxN + 1];
        unsigned char carry = 0;

        for (long long i = 0; i < maxN; i++) {
            unsigned short sum = carry;

            if (i < this->n) {
                sum += this->x[i];
            }
            if (i < other.n) {
                sum += other.x[i];
            }
            // cout << "Index: " << i << ", Sum: " << sum << ", Carry: " << static_cast<int>(carry) << endl;

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

    long long operator%(long long other) {
        long long rem = 0;
        long long base = 1;
        for (long long i = 0; i < n; i++) {
            rem = (rem + x[i] * base) % other;
            base = (base << 8) % other;
        }

        return rem;
    }

    dint operator/(long long other) {
        long long resultN = this->n;
        long long div = 0;

        unsigned char *resultX = new unsigned char[resultN];
        for (int i = resultN - 1; i >= 0; i--) {
            div = (div << 8) + x[i];
            resultX[i] = div / other;
            div %= other;
        }

        while (resultN > 1 && resultX[resultN - 1] == 0) {
            resultN--;
        }

        dint result(0);
        delete[] result.x;
        result.n = resultN;
        result.x = new unsigned char[resultN];
        for (long long i = 0; i < resultN; i++) {
            result.x[i] = resultX[i];
        }
        delete[] resultX;
        return result;

    }

    char operator>(long long other) {
        return *this > dint(other);
    }

    char operator>(dint other) {
        if (this->n != other.n) {
            return this->n > other.n;
        }
        for (long long i = this->n - 1; i >= 0; i--) {
            if (this->x[i] != other.x[i]) {
                return this->x[i] > other.x[i];
            }
        }
        return 0;
    }
};

int main() {
    dint a = LONG_LONG_MAX;
    // dint b = LONG_LONG_MAX;
    for (int i = 0; i < 100000; i++) {
        a = a + a;
    }
    // a = a + 2;
    cout << a.to_string() << endl;
    return 0;
}