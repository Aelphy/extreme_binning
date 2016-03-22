#include <cxxtest/TestSuite.h>
#include "../util.h"

class UtilTest : public CxxTest::TestSuite {
 public:
    void test_get_instance(void) {
        Util *util = Util::get_instance();

        TS_ASSERT_EQUALS(util->window, WINDOW);
    }
};
