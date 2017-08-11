/*
Copyright (c) 2017 Juha Lepola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <benchmark/benchmark.h>

#include <atomic>
#include <array>
#include <unordered_map>

// Value type for the counter.
typedef int64_t counter_t;


// Simulates simple reference counter for single CPU systems.
static void BM_LocalIncrementAndDecrement(benchmark::State& state) {

    counter_t value = 0;
    while( state.KeepRunning() )
    {
        benchmark::DoNotOptimize( ++value );
        benchmark::DoNotOptimize( --value );
    }
}
BENCHMARK(BM_LocalIncrementAndDecrement)->Threads( 16 );

// Estimates the performance hit from going from local stack variable to thread local variable.
static thread_local counter_t thread_value = 0;
static void BM_ThreadLocalIncrementAndDecrement(benchmark::State& state) {

    while( state.KeepRunning() )
    {
        benchmark::DoNotOptimize( ++thread_value );
        benchmark::DoNotOptimize( --thread_value );
    }
}
BENCHMARK(BM_ThreadLocalIncrementAndDecrement)->Threads( 16 );

// A rough guestimate on how the performance would look like in a Google dense hash map. Will integrate it here later.
static thread_local std::array< counter_t, 4096 > thread_array;
static void BM_ThreadLocalArrayIncrementAndDecrement(benchmark::State& state) {

    counter_t value = 0;
    while( state.KeepRunning() )
    {
        benchmark::DoNotOptimize( thread_array[ ( ++value ) % 4096 ]++ );
        benchmark::DoNotOptimize( thread_array[ value % 4096 ]-- );
    }
}
BENCHMARK(BM_ThreadLocalArrayIncrementAndDecrement)->Threads( 16 );

// A standard atomic reference counter for SMP systems when uncontested
static void BM_UncontestedAtomicIncrementAndDecrement(benchmark::State& state) {
    std::atomic< counter_t > value;
    while( state.KeepRunning() )
    {
        benchmark::DoNotOptimize( ++value );
        benchmark::DoNotOptimize( --value );
    }
}
BENCHMARK(BM_UncontestedAtomicIncrementAndDecrement)->Threads( 16 );

// A standard atomic reference counter for SMP systems when heavily contested
static std::atomic< counter_t > global_value;
static void BM_ContestedAtomicIncrementAndDecrement(benchmark::State& state) {
    while( state.KeepRunning() )
    {
        ++global_value;
        --global_value;
    }
}
BENCHMARK(BM_ContestedAtomicIncrementAndDecrement)->Threads( 16 );

// How was we would externalize the reference counters to a hash table outside the actual objects.
// TODO: Add a hash table benchmark with some values.
static void BM_UnorderedMapInsertAndErase(benchmark::State& state) {
    std::unordered_map< counter_t, counter_t > values;
    int64_t value =0;
    while( state.KeepRunning() )
    {
        values[ ++value ] = 1;
        values.erase( value );
    }
}
BENCHMARK(BM_UnorderedMapInsertAndErase)->Threads( 16 );

// How was we would externalize the reference counters to a thread local hash table outside the actual objects.
// TODO: Add a hash table benchmark with some values.
static thread_local std::unordered_map< counter_t, counter_t > thread_values;
static void BM_ThreadLocalUnorderedMapInsertAndErase(benchmark::State& state) {
    int64_t value =0;
    while( state.KeepRunning() )
    {
        thread_values[ ++value ] = 1;
        thread_values.erase( value );
    }
}
BENCHMARK(BM_ThreadLocalUnorderedMapInsertAndErase)->Threads( 16 );

BENCHMARK_MAIN();
