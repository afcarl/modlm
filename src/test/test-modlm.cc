#define BOOST_TEST_MODULE "modlm Tests"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <cnn/init.h>

// Set up CNN
struct CnnSetup {
    CnnSetup()   { 
        int zero = 0;
        char** null = NULL;
        cnn::initialize(zero, null);
    }
    ~CnnSetup()  { /* shutdown your allocator/check memory leaks here */ }
};

BOOST_GLOBAL_FIXTURE( CnnSetup );
