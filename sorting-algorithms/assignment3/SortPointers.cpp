#include "SortPointers.hpp"
#include <cassert>
#include <vector>
#include <iostream>
#include <cmath>

//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace sort_pointers {
//---------------------------------------------------------------------------
namespace {
//---------------------------------------------------------------------------
void swap(const unsigned*& a, const unsigned*& b)
// Swap two elements
{
    const unsigned* tmp = a;
    a = b;
    b = tmp;
}
//---------------------------------------------------------------------------
const unsigned** partition(const unsigned** begin, const unsigned** end)
// Partition the range [begin; end)
{
    assert((end - begin) > 1);

    const unsigned** pivot = end - 1;
    const unsigned** i = begin;

    for (const unsigned** j = begin; j < (end - 1); ++j) {
        if (**j < **pivot) {
            swap(*i, *j);
            i++;
        }
    }

    swap(*i, *pivot);
    return i;
}
//---------------------------------------------------------------------------
void merge(const unsigned** out, const unsigned** begin, const unsigned** mid, const unsigned** end)
// Merge two subarrays
{
    const unsigned** i = begin;
    const unsigned** j = mid;

    while ((i != mid) && (j != end)) {
        if (**i < **j) {
            *out = *i;
            ++i;
        } else {
            *out = *j;
            ++j;
        }

        ++out;
    }

    while ((i != mid)) {
        *out = *i;
        ++i;
        ++out;
    }

    while ((j != end)) {
        *out = *j;
        ++j;
        ++out;
    }
}
//---------------------------------------------------------------------------
void mergesort(const unsigned** begin0,const unsigned** end0, const unsigned** begin1,const unsigned** end1)
// Sort a range of pointers [begin; end) using the specified scratch space
{
    if(begin0 < end0-1) {

        const unsigned **mid0 = begin0 + (end0 - begin0) / 2;
        const unsigned **mid1 = begin1 + (end1 - begin1) / 2;

        mergesort(begin0, mid0, begin1, mid1);
        mergesort(mid0, end0, mid1, end1);

        merge(begin1, begin0, mid0, end0);

        copy(begin1, end1, begin0);

    }

    //-----------------------------------------------------
    // Alternative version (which doesn't use end1 and IMO is a little bit better, because it uses fewer calculations):
//      if(begin0 < end0-1) {
//
//            const unsigned **mid = begin0 + (end0 - begin0) / 2;
//
//            mergesort(begin0, mid, begin1, end1);
//            mergesort(mid, end0, begin1, end1);
//
//            merge(begin1, begin0, mid, end0);
//
//            copy(begin1, begin1 + (end0 - begin0), begin0);
//      }
    //-----------------------------------------------------
}

/// A function used to create / maintain the heap's structure (called by heapsort)
    void heapify(const unsigned** begin, const unsigned** end, unsigned i, unsigned length)
    {
        unsigned largest = i;
        unsigned l = 2*i+1;
        unsigned r = 2*i+2;

        if (l < length && **(begin + l) > **(begin + largest)){
            largest = l;
        }

        if (r < length && **(begin + r) > **(begin + largest)){
            largest = r;
        }

        if (largest != i){
            swap(*(begin+i), *(begin + largest));
            heapify(begin, end, largest, length);
        }
    }

/// Heap Sort implementation (called by sort)
void heapsort(const unsigned** begin, const unsigned** end)
{
     unsigned length = end - begin;

     for(unsigned i = length / 2 - 1; i < length; i--){
         heapify(begin, end, i, length);
     }

     for(unsigned i = length - 1; i > 0; i--){
         swap(*begin,*(begin+i));
         heapify(begin, begin + i, 0, i);
     }
}

/// Insertion Sort implementation (called by sort)
void insertionsort(const unsigned** begin, const unsigned** end)
{
     if(begin < end - 1){

         for(const unsigned** i = begin + 1; i < end; i++){
             const unsigned** j = i;
             const unsigned* k = *i;

             while(j > begin && **(j-1) > *k){
                 *j = *(j-1);
                 --j;
             }
             *j=k;
         }
     }
}    

    /// A function that does the actual sorting (called by introsort)
void sort(const unsigned** begin, const unsigned** end, unsigned maxDepth)
{
        unsigned length = end - begin;

        if(length > 1) {
            if (length < 16){
                insertionsort(begin, end);
            }else if (maxDepth == 0){
                heapsort(begin, end);
            }else{
                const unsigned **p = partition(begin, end);
                sort(begin, p, maxDepth - 1);
                sort(p+1, end, maxDepth - 1);
            }
        }
}
//---------------------------------------------------------------------------
} // namespace
//---------------------------------------------------------------------------
void quicksort(const unsigned** begin, const unsigned** end)
// Sort the range of pointers [begin; end)
{
     if(begin < end-1){
         const unsigned ** p = partition(begin, end);
         quicksort(begin, p);
         quicksort(p+1, end);
     }
}
//---------------------------------------------------------------------------
void mergesort(const unsigned** begin,const unsigned** end)
// Sort the range of pointers [begin; end)
{
    auto **arr = new const unsigned*[end-begin];
   mergesort(begin, end, arr, arr + (end - begin));
   delete[] arr;
}
//---------------------------------------------------------------------------
void introsort(const unsigned** begin, const unsigned** end)
// Sort the range of pointers [begin; end)
{
     unsigned length = end - begin;
     if(length > 1) {
         
         unsigned maxDepth = log2(length) * 2;
         sort(begin, end, maxDepth);
     }
}
//---------------------------------------------------------------------------
} // namespace sort_pointers
//---------------------------------------------------------------------------
