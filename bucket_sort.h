#pragma once
#include <vector>
#include <list>

namespace ltd {
    /*
     * BucketSort class requires inserting every item in it via insert(float)
     * For in-place sort see bucket_sort defined below
     */
    class BucketSort {
    public:
        friend void bucket_sort(std::vector<float>::iterator, std::vector<float>::iterator);
        BucketSort();
        explicit BucketSort(size_t);

        void insert(float);

        std::vector<float> sort();
        size_t collisions();

        void reset(size_t = 10);
    private:
        void insertionSort(std::list<float>::iterator begin, std::list<float>::iterator end);
        std::vector<float> mergeBuckets();
        void clear();

        size_t n_buckets_;
        size_t collisions_;
        std::vector<std::list<float> > buckets_;
    };

    /*
     * Non-member function that accepts iterators in STL style.
     * It's not possible to calculate collisions with it without returning them or passing
     * variable as reference to save the number of collisions, but i didn't want to do that here
     */
    void bucket_sort(std::vector<float>::iterator, std::vector<float>::iterator);
}