Install modern cmake > v20
Follow the best answer in
https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line
Download `https://cmake.org/files/v3.22/cmake-3.22.6.tar.gz`

### Command
```
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -S . -B build && cmake --build build/ -j 4
cmake -G Ninja -S . -B build && cmake --build build/ -j 4 && (cd build/; ctest -V)

cmake -G Ninja -S . -B build && cmake --build build/ -j 4 && cmake --install ./build --prefix /tmp/install-test && (cd build/; ctest -V)

cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON –S . -B ./build && cmake --build ./build && cmake --install ./build --prefix /tmp/install-test
```

###  Reading materials
- https://www.pragmaticlinux.com/2022/02/create-a-shared-library-in-c-with-cmake/
- https://www.pragmaticlinux.com/2022/03/how-to-link-a-shared-library-with-gcc-and-cmake/
- https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html
- https://decovar.dev/blog/2021/03/08/cmake-cpp-library/
- https://github.com/retifrav/cmake-library-example
- https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html#src-dir
- https://surfertas.github.io/cmake/cpp/projecteuler/2019/05/01/cmake.html
- https://cliutils.gitlab.io/modern-cmake/
- https://youtu.be/eC9-iRN2b04
- https://github.com/Mizux/cmake-cpp
- https://github.com/pananton/cpp-lib-template
- https://rvarago.medium.com/introduction-to-cmake-for-cpp-4c464272a239
- https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
- https://medium.com/@pananton/modern-cmake-tutorial-for-c-library-developers-12f3bf57dc87
- https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/cppProgramStructure/index.html
- https://medium.com/heuristics/c-application-development-part-1-project-structure-454b00f9eddc
- https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs
- https://www.reddit.com/r/cpp/comments/8qzepa/comment/e0o5gd0/?utm_source=share&utm_medium=web2x&context=3
- https://www.udemy.com/course/complete-cmake-project-management/#reviews
- https://thatonegamedev.com/cpp/how-to-embed-files-in-your-c-project/
- https://hsf-training.github.io/hsf-training-cmake-webpage/04-targets/index.html
- https://iscinumpy.dev/
- https://thatonegamedev.com/cpp/how-to-write-unit-tests-with-cmake/
