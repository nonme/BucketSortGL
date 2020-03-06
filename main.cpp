#include <iostream>
#include <list>
#include <random>

#include "bucket_sort.h"
#include "TestRunner.h"

void TestBucketClass();

void TestBucketFunction();

int main() {
    {
        test::TestRunner tr;
        //tr.disable();  // comment disable to see the tests passed
        RUN_TEST(tr, TestBucketClass);
        RUN_TEST(tr, TestBucketFunction);
    }
    std::list<float> input;
    float value = 0;
    std::cin >> value;
    while (value != 0) {
        input.emplace_back(value);
        std::cin >> value;
    }
    ltd::BucketSort bucketSort(input.size());
    for (auto &item : input) {
        bucketSort.insert(item);
    }

    std::vector<float> result = bucketSort.sort();
    size_t collisions = bucketSort.collisions();
    for (auto &item : result) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << collisions << std::endl;
    return 0;
}

void TestBucketClass() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> randomer(0, 100);

    std::vector<float> a(1000);
    for (auto &item : a) {
        item = randomer(generator);
    }
    ltd::BucketSort bucketSort(1000);
    for (auto &item : a) {
        bucketSort.insert(item);
    }
    std::vector<float> sorted = bucketSort.sort();
    ASSERT_EQ(sorted.size(), 1000);
    for (size_t i = 1; i < sorted.size(); ++i) {
        ASSERT_EQ(sorted[i] >= sorted[i - 1], true);
    }
    // Standart template library provides uniform distribution, so if we have range 100 and number
    // of elements 1000, on avg, there will less than 10 numbers in each bucket
    ASSERT_EQ(bucketSort.collisions() <= 10, true);

    a.resize(100);
    bucketSort.reset(100);
    for (auto &item : a) {
        item = randomer(generator);
        bucketSort.insert(item);
    }
    sorted = bucketSort.sort();
    ASSERT_EQ(sorted.size(), 100);
    for (size_t i = 1; i < sorted.size(); ++i) {
        ASSERT_EQ(sorted[i] >= sorted[i - 1], true);
    }
}

void TestBucketFunction() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> randomer(0, 100);

    std::vector<float> a(1000);
    for (auto &item : a) {
        item = randomer(generator);
    }

    ltd::bucket_sort(a.begin(), a.end());
    for (size_t i = 1; i < a.size(); ++i) {
        ASSERT_EQ(a[i] >= a[i - 1], true);
    }
}