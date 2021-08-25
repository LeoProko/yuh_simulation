mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
cd benchmarks/bin/
./map_one_thread_BM
./map_mutex_BM
./map_lock_free_BM
cd ..
cd ..
cd ..

