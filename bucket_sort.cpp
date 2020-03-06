
#include <cmath>
#include <algorithm>
#include <iostream>
#include "bucket_sort.h"

namespace ltd {
    BucketSort::BucketSort() :
            n_buckets_(10), buckets_(n_buckets_), collisions_(0) {
    }

    BucketSort::BucketSort(size_t n_elements) :
            n_buckets_(n_elements), buckets_(n_buckets_), collisions_(0) {
    }

    void BucketSort::insert(float number) {
        size_t position = floor((number * n_buckets_) / 101.0);
        buckets_[position].emplace_back(number);

        collisions_ = std::max(collisions_, buckets_[position].size());
    }

    std::vector<float> BucketSort::sort() {
        for (auto &bucket : buckets_) {
            insertionSort(bucket.begin(), bucket.end());
        }
        return mergeBuckets();
    }

    void BucketSort::insertionSort(std::list<float>::iterator begin, std::list<float>::iterator end) {
        if (begin == end) return;

        for (auto it = std::next(begin); it != end; ++it) {
            auto current = it;
            auto prev = std::prev(it);
            while (current != begin && *current < *prev) {
                std::swap(*current, *prev);
                current = prev;
                if (current != begin)
                    prev = std::prev(current);
            }
        }
    }

    std::vector<float> BucketSort::mergeBuckets() {
        std::vector<float> result (n_buckets_);
        auto it = result.begin();
        for (const auto &bucket : buckets_) {
            it = std::copy(bucket.begin(), bucket.end(), it);
        }
        return result;
    }

    size_t BucketSort::collisions() {
        return collisions_;
    }

    void BucketSort::clear() {
        for (auto &bucket : buckets_)
            bucket.clear();
        collisions_ = 0;
    }

    void bucket_sort(std::vector<float>::iterator begin, std::vector<float>::iterator end) {
        size_t buckets = end - begin;
        BucketSort bucketSort(buckets);
        for (auto it = begin; it != end; ++it)
            bucketSort.insert(*it);

        for (auto &bucket : bucketSort.buckets_) {
            bucketSort.insertionSort(bucket.begin(), bucket.end());
        }
        size_t bucket_index = 0;
        auto bucket_iterator = bucketSort.buckets_[bucket_index].begin();
        for (auto &it = begin; it != end; ++it) {
            while (bucket_iterator == bucketSort.buckets_[bucket_index].end()) {
                ++bucket_index;
                bucket_iterator = bucketSort.buckets_[bucket_index].begin();
            }
            *it = *bucket_iterator;
            bucket_iterator++;
        }
    }

    void BucketSort::reset(size_t buckets) {
        clear();
        n_buckets_ = buckets;
        buckets_.resize(buckets);
    }
}
