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
bool suite_RabinKarpTest_init = false;
#include "/Users/Aelphy/Documents/projects/extreme_binning/test/rabin_karp_test.h"

static RabinKarpTest suite_RabinKarpTest;

static CxxTest::List Tests_RabinKarpTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RabinKarpTest( "test/rabin_karp_test.h", 4, "RabinKarpTest", suite_RabinKarpTest, Tests_RabinKarpTest );

static class TestDescription_suite_RabinKarpTest_test_hash : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RabinKarpTest_test_hash() : CxxTest::RealTestDescription( Tests_RabinKarpTest, suiteDescription_RabinKarpTest, 6, "test_hash" ) {}
 void runTest() { suite_RabinKarpTest.test_hash(); }
} testDescription_suite_RabinKarpTest_test_hash;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
