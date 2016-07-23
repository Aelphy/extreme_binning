/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
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
bool suite_BinTest_init = false;
#include "/Users/Aelphy/Documents/projects/extreme_binning/test/bin_test.h"

static BinTest suite_BinTest;

static CxxTest::List Tests_BinTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BinTest( "test/bin_test.h", 11, "BinTest", suite_BinTest, Tests_BinTest );

static class TestDescription_suite_BinTest_test_creation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BinTest_test_creation() : CxxTest::RealTestDescription( Tests_BinTest, suiteDescription_BinTest, 13, "test_creation" ) {}
 void runTest() { suite_BinTest.test_creation(); }
} testDescription_suite_BinTest_test_creation;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
