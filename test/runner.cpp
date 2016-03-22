/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_UtilTest_init = false;
#include "/Users/Aelphy/Documents/projects/extreme_binning/test/util_test.h"

static UtilTest suite_UtilTest;

static CxxTest::List Tests_UtilTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UtilTest( "test/util_test.h", 4, "UtilTest", suite_UtilTest, Tests_UtilTest );

static class TestDescription_suite_UtilTest_test_get_instance : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UtilTest_test_get_instance() : CxxTest::RealTestDescription( Tests_UtilTest, suiteDescription_UtilTest, 6, "test_get_instance" ) {}
 void runTest() { suite_UtilTest.test_get_instance(); }
} testDescription_suite_UtilTest_test_get_instance;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
