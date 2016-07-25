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
bool suite_IndexItemTest_init = false;
#include "/Users/Aelphy/Documents/projects/extreme_binning/test/index_item_test.h"

static IndexItemTest suite_IndexItemTest;

static CxxTest::List Tests_IndexItemTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IndexItemTest( "test/index_item_test.h", 8, "IndexItemTest", suite_IndexItemTest, Tests_IndexItemTest );

static class TestDescription_suite_IndexItemTest_test_index_item : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_IndexItemTest_test_index_item() : CxxTest::RealTestDescription( Tests_IndexItemTest, suiteDescription_IndexItemTest, 10, "test_index_item" ) {}
 void runTest() { suite_IndexItemTest.test_index_item(); }
} testDescription_suite_IndexItemTest_test_index_item;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
