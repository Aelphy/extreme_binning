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
bool suite_StorageTest_init = false;
#include "/Users/Aelphy/Documents/projects/extreme_binning/test/storage_test.h"

static StorageTest suite_StorageTest;

static CxxTest::List Tests_StorageTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_StorageTest( "test/storage_test.h", 9, "StorageTest", suite_StorageTest, Tests_StorageTest );

static class TestDescription_suite_StorageTest_test_storage_read_write : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_StorageTest_test_storage_read_write() : CxxTest::RealTestDescription( Tests_StorageTest, suiteDescription_StorageTest, 11, "test_storage_read_write" ) {}
 void runTest() { suite_StorageTest.test_storage_read_write(); }
} testDescription_suite_StorageTest_test_storage_read_write;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
