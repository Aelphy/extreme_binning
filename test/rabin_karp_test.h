// ../cxxtest-4.4/bin/cxxtestgen --error-printer -o test/runner.cpp  test/rabin_karp_test.h
// g++ -o test/runner -I../cxxtest-4.4  test/runner.cpp rabin_karp_hasher.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include <math.h>
#include <algorithm>
#include "../rabin_karp_hasher.h"

class RabinKarpTest : public CxxTest::TestSuite {
public:
    RabinKarpHasher hasher;

    unsigned long long int hash(const std::string &s) {
        std::vector<char> test_data(s.begin(), s.end());

        hasher.init(&test_data);

        return hasher.get_hash();
    }

    unsigned long long int recompute(char c) {
        hasher.recompute(c);

        return hasher.get_hash();
    }

    std::string concat(unsigned long long int h, std::string s) {
        std::string s1("");

        while (h) {
            s1 = (char) (h & 0xFF) + s1;
            h >>= 8;
        }

        return s1 + s;
    }

    void test_hash(void) {
        TS_ASSERT_EQUALS(hash("\0"), 0);
        hasher.finish();

        TS_ASSERT_EQUALS(hash("\1"), 1);
        hasher.finish();

        TS_ASSERT_EQUALS(hash("1"), 49);
        hasher.finish();

        TS_ASSERT_EQUALS(hash("\1\1"), 256 + 1);
        hasher.finish();

        TS_ASSERT_EQUALS(hash("\1\1\1\1\1\1\1\1"), 1 + pow(256, 1)
           + pow(256, 2)
           + pow(256, 3)
           + pow(256, 4)
           + pow(256, 5)
           + pow(256, 6)
           + pow(256, 7));
        hasher.finish();

        unsigned long long int i = hash("\3");
        hasher.finish();

        unsigned long long int j = hash("\1");
        hasher.finish();

        unsigned long long int k = hash("\2");
        hasher.finish();

        TS_ASSERT_EQUALS(i, j + k);

        std::string s1 = "fdsdf оптывдаот пваот sldfjn sdf nsdfj тыдваот sldfjn sldfjn gsldjfn sldfjn gsdlfjn gsldfjn gsdlfjn gsdfljn gsdlfj ngsdfjn gsdfl gnsdlfg nsdflg nsldfg";
        std::string s2 = "fasd asd fasd fasdf ывап sfdgn в ылври ылвраи ылвраи sdkhf bsdkhfbg sdkfhbg sdkhfb gsdkfhbg skdfhbg sdhfb gsdfg b";

        i = hash(s1 + s2);
        hasher.finish();

        j = hash(s1);
        hasher.finish();

        k = hash(concat(j,  s2));
        hasher.finish();

        TS_ASSERT_EQUALS(i, k);
    }


    void test_recompute(void) {
        hash("\1");
        TS_ASSERT_EQUALS(recompute('\1'), 256 + 1);
        hasher.finish();
    }
};
