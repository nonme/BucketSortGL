#pragma once

#include <sstream>
#include <vector>

/*
	Developed by Larin Dmytro
	Unit tests framework to make testing homework easier and cleaner
	Values needs to be checked using macros, not functions
	I put everything in the .h file to make includes easier
*/

#define ASSERT_EQ(x, y) {						\
	std::ostringstream os;						\
	os << #x << " != " << #y << ", "			\
	   << __FILE__ << ":" << __LINE__;			\
	test::__ASSERT_EQUALS__(x, y, os.str());	\
}

#define ASSERT_THROWS(x, y) {					\
	std::ostringstream os;						\
	os << #x << " doesn't throw " << #y << ": "	\
	<< std::endl << __FILE__ << ":" << __LINE__;\
	test::__ASSERT_THROWS__(x, y, os.str());	\
}

#define RUN_TEST(tr, func) {					\
	tr.runTest((func), #func);					\
}

namespace test {
    class TestRunner {
    private:
        int tests_failed_;
        int tests_;
        bool isEnabled_;
    public:
        TestRunner() :
                tests_failed_(0), tests_(0), isEnabled_(true) {};
        ~TestRunner() {
            if (tests_failed_ > 0) {
                std::cerr << tests_failed_ << "/" << tests_ << " tests failed. Terminating program." << std::endl;
                exit(1);
            }
        }

        template<typename TestFunc>
        void runTest(TestFunc func, const std::string name) {
            tests_++;
            if (isEnabled_) {
                try {
                    func();
                    std::cerr << name << " -> OK" << std::endl;
                }
                catch (std::runtime_error e) {
                    std::cerr << name << " -> " << e.what() << std::endl;
                    tests_failed_++;
                }
            }
        }

        void enable() {
            isEnabled_ = true;
        }

        void disable() {
            isEnabled_ = false;
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
        os << "{ ";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i != 0)
                os << ", ";
            os << vec[i];
        }
        os << " }";
        return os;
    }


    template<typename T, typename U>
    void __ASSERT_EQUALS__(const T& t, const U& u, const std::string& msg) {
        if (t != u) {
            std::ostringstream os;
            os << "Assertion failed! : " << t << " != " << u << std::endl << "(" << msg << ")";
            throw std::runtime_error(os.str());
        }
    }
    void __ASSERT_EQUALS__(double a, double b, const std::string& msg) {
        if (abs(a - b) >= 0.0001) {
            std::ostringstream os;
            os << "Assertion failed: " << a << " != " << b << std::endl << " (" << msg << ")";
            throw std::runtime_error(os.str());
        }
    }

    void __ASSERT_THROWS__(void (*func)(), const std::exception& e, const std::string& msg) {
        try {
            func();
        }
        catch (const std::exception& e) {
            return;
        }
        std::ostringstream os;
        os << "Assertion failed: " << msg;
        throw std::runtime_error(os.str());
    }
}