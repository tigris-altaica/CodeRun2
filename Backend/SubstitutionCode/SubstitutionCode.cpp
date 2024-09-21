#include <iostream>
#include <concepts>
#include <vector>
#include <set>
#include <array>

using namespace std;

namespace {
    template<typename T>
    T read() {
        T val;
        cin >> val;
        return val;
    }

    template<typename T>
    void write(const T &val) {
        cout << val << " ";
    }

    template<typename T>
    void writeln(const T &val) {
        cout << val << "\n";
    }
}
namespace {
    using value_type = long long;

    template <value_type modulo>
    class Modular {
    public:
        Modular() = default;
        explicit Modular(std::integral auto val) : value(val)  {
            reduce_modulo();
        }

        Modular& operator += (const Modular& rhs) {
            this->value += rhs.value;
            reduce_modulo();
            return *this;
        }

        Modular& operator -= (const Modular& rhs) {
            this->value -= rhs.value;
            reduce_modulo();
            return *this;
        }

        Modular& operator *= (const Modular& rhs) {
            this->value *= rhs.value;
            reduce_modulo();
            return *this;
        }

        Modular& operator += (std::integral auto rhs) {
            Modular rhs_mod(rhs);
            return *this += rhs_mod;
        }

        Modular& operator -= (std::integral auto rhs) {
            Modular rhs_mod(rhs);
            return *this -= rhs_mod;
        }

        Modular& operator *= (std::integral auto rhs) {
            Modular rhs_mod(rhs);
            return *this *= rhs_mod;
        }

        bool operator < (const Modular& rhs) const {
            return value < rhs.value;
        }

        bool operator > (const Modular& rhs) const {
            return value > rhs.value;
        }

        template <value_type M>
        friend bool operator ==(const Modular<M>& lhs, const Modular<M>& rhs);
        template <value_type M>
        friend bool operator ==(const Modular<M>& lhs, std::integral auto rhs);

    private:
        value_type value{0};

        void reduce_modulo() {
            this->value %= modulo;
            value += modulo * (value < 0);
        }
    };

    template <value_type M>
    bool operator ==(const Modular<M>& lhs, const Modular<M>& rhs) {
        return lhs.value == rhs.value;
    }

    template <value_type M>
    bool operator ==(const Modular<M>& lhs, std::integral auto rhs) {
        Modular<M> rhs_mod(rhs);
        return lhs == rhs_mod;
    }

    template <value_type M>
    Modular<M> operator + (const Modular<M>& lhs, const Modular<M>& rhs) {
        Modular temp(lhs);
        temp += rhs;
        return temp;
    }

    template <value_type M>
    Modular<M> operator - (const Modular<M>& lhs, const Modular<M>& rhs) {
        Modular temp(lhs);
        temp -= rhs;
        return temp;
    }

    template <value_type M>
    Modular<M> operator * (const Modular<M>& lhs, const Modular<M>& rhs) {
        Modular temp(lhs);
        temp *= rhs;
        return temp;
    }

    template <value_type M>
    Modular<M> operator + (const Modular<M>& lhs, std::integral auto rhs) {
        Modular temp(lhs);
        temp += rhs;
        return temp;
    }

    template <value_type M>
    Modular<M> operator - (const Modular<M>& lhs, std::integral auto rhs) {
        Modular temp(lhs);
        temp -= rhs;
        return temp;
    }

    template <value_type M>
    Modular<M> operator * (const Modular<M>& lhs, std::integral auto rhs) {
        Modular temp(lhs);
        temp *= rhs;
        return temp;
    }
}

using Zmod = Modular<1'000'000'000 + 7>;

vector<Zmod> computePowers(int power, size_t k) {
    vector<Zmod> powers(k);
    Zmod mult(1);
    for (int i = k - 1; i >= 0; --i) {
        powers[i] = mult;
        mult *= power;
    }
    return powers;
}

constexpr int p = 2;
vector<Zmod> powersOfP;

class SubstitutionHash {
public:
    explicit SubstitutionHash(string_view sv) {
        for (size_t i = 0; i < alphabetSize; ++i) {
            index[i] = symbolHashes.emplace();
        }

        for (auto pit = powersOfP.begin(); auto ch : sv) {
            auto node = symbolHashes.extract(index[val(ch)]);
            node.value() += *pit;
            index[val(ch)] = symbolHashes.insert(std::move(node));
            ++pit;
        }
    }

    void del(char ch) {
        auto node = symbolHashes.extract(index[val(ch)]);
        node.value() -= powersOfP.front();
        index[val(ch)] = symbolHashes.insert(std::move(node));
    }

    void shift() {
        for (size_t i = 0; i < alphabetSize; ++i) {
            if (*(index[i]) == 0) {
                continue;
            }
            auto node = symbolHashes.extract(index[i]);
            node.value() *= p;
            index[i] = symbolHashes.insert(std::move(node));
        }
    }

    void add(char ch) {
        auto node = symbolHashes.extract(index[val(ch)]);
        node.value() += powersOfP.back();
        index[val(ch)] = symbolHashes.insert(std::move(node));
    }

    bool operator == (const SubstitutionHash& rhs) const {
        return symbolHashes == rhs.symbolHashes;
    }

private:
    static int val(char c) {
        return c - 33;
    }

    static constexpr size_t alphabetSize = 94;

    multiset<Zmod, greater<Zmod>> symbolHashes;
    array<multiset<Zmod, greater<Zmod>>::iterator, alphabetSize> index;
};

int main() {
    auto str = read<string>();
    auto pattern = read<string>();

    powersOfP = computePowers(p, pattern.size());

    const auto patternHash = SubstitutionHash(pattern);

    auto substrHash = SubstitutionHash(string_view(str).substr(0, pattern.size() - 1));
    vector<size_t> startIdxs;

    for (size_t i = 0; i + pattern.size() - 1 < str.size(); ++i) {
        substrHash.add(str[i + pattern.size() - 1]);

        if (substrHash == patternHash) {
            startIdxs.push_back(i);
        }

        substrHash.del(str[i]);
        substrHash.shift();
    }

    writeln(startIdxs.size());
    for (auto idx : startIdxs) {
        write(idx + 1);
    }

    return 0;
}