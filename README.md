# ref_count_test
An incomplete comparison of alternative reference counting mechanisms. Currently more of a rough guestimate of their performance than actual realistic comparison.

-----
## Results
Run on (16 X 3600 MHz CPU s)
2017-08-11 21:25:06
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.

--------------------------------------------------------------------------------------------
Benchmark                                                     Time           CPU Iterations
--------------------------------------------------------------------------------------------
BM_LocalIncrementAndDecrement/threads:16                      0 ns          2 ns  321471056
BM_ThreadLocalIncrementAndDecrement/threads:16                0 ns          5 ns  148346736
BM_ThreadLocalArrayIncrementAndDecrement/threads:16           0 ns          3 ns  215744864
BM_UncontestedAtomicIncrementAndDecrement/threads:16          1 ns         14 ns   48595360
BM_ContestedAtomicIncrementAndDecrement/threads:16           27 ns        423 ns    1600000
BM_UnorderedMapInsertAndErase/threads:16                      3 ns         51 ns   14268080
BM_ThreadLocalUnorderedMapInsertAndErase/threads:16           3 ns         51 ns   13661520

--------------------------------------------------------------------------------------------
Benchmark                                                     Time           CPU Iterations
--------------------------------------------------------------------------------------------
BM_LocalIncrementAndDecrement/threads:16                      0 ns          2 ns  321130640
BM_ThreadLocalIncrementAndDecrement/threads:16                0 ns          5 ns  148380032
BM_ThreadLocalArrayIncrementAndDecrement/threads:16           0 ns          4 ns  192874208
BM_UncontestedAtomicIncrementAndDecrement/threads:16          1 ns         14 ns   48584400
BM_ContestedAtomicIncrementAndDecrement/threads:16           25 ns        383 ns    1600000
BM_UnorderedMapInsertAndErase/threads:16                      4 ns         47 ns   14119104
BM_ThreadLocalUnorderedMapInsertAndErase/threads:16           3 ns         49 ns   14724080

----

## Interesting Observations

* BM_ThreadLocalIncrementAndDecrement is slower than BM_ThreadLocalArrayIncrementAndDecrement
* BM_ContestedAtomicIncrementAndDecrement: the number of iterations is often exacly 1600000
