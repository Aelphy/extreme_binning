// ../cxxtest-4.4/bin/cxxtestgen --error-printer -o test/runner.cpp  test/rabin_karp_test.h
// g++ -o test/runner -I../cxxtest-4.4  test/runner.cpp rabin_karp_hasher.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include <math.h>
#include <algorithm>
#include "../rabin_karp_hasher.h"

class RabinKarpTest : public CxxTest::TestSuite {
public:
    unsigned long long int hash(const std::string &s) {
        RabinKarpHasher hasher;
        std::vector<char> test_data(s.begin(), s.end());

        hasher.init(&test_data);

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
        TS_ASSERT_EQUALS(hash("\1"), 1);
        TS_ASSERT_EQUALS(hash("1"), 49);
        TS_ASSERT_EQUALS(hash("\1\1"), 256 + 1);
        TS_ASSERT_EQUALS(hash("\1\1\1\1\1\1\1\1"), 1 + pow(256, 1)
           + pow(256, 2)
           + pow(256, 3)
           + pow(256, 4)
           + pow(256, 5)
           + pow(256, 6)
           + pow(256, 7));

        TS_ASSERT_EQUALS(hash("\3"), hash("\1") + hash("\2"));

        std::string s1 = "fdsdf оптывдаот пваот sldfjn sdf nsdfj тыдваот sldfjn sldfjn gsldjfn sldfjn gsdlfjn gsldfjn gsdlfjn gsdfljn gsdlfj ngsdfjn gsdfl gnsdlfg nsdflg nsldfg";
        std::string s2 = "fasd asd fasd fasdf ывап sfdgn в ылври ылвраи ылвраи sdkhf bsdkhfbg sdkfhbg sdkhfb gsdkfhbg skdfhbg sdhfb gsdfg b";

        TS_ASSERT_EQUALS(hash(s1 + s2), hash(concat(hash(s1),  s2)));
    }
};
