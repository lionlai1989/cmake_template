# C++ project template with CMake

As a seasoned software developer, I've had more run-ins with CMake than I can count. But let's be real, it's time to get serious and really learn this thing. Sure, there are a ton of CMake tutorials floating around on the interwebs, but they all focus on small projects. And let's face it, those projects are about as practical as a chocolate teapot. When you dive into larger, real-world projects that use CMake, things get complicated quick. It's like trying to unravel a ball of yarn that's been tangled by a mischievous cat. So, I've taken it upon myself to create a repository that builds a template for a real-world project. Let's cut through the fluff and get down to business!

## Description

TODO: DESCRIBE WHAT FEATURES THIS REPO HAS.

## Getting Started

### Dependencies
* Minimum CMake version is `3.22.0`. Please follow the best answer [here](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line) to either install or update the CMake. Download `https://cmake.org/files/v3.22/cmake-3.22.6.tar.gz` if you want to use CMake `3.22`.
* The C++ library [Eigen](https://gitlab.com/libeigen/eigen) and the C image library [stb](https://github.com/nothings/stb) are added as git submodules. You don't have to do anything here. Just remember to pass `--recursive` while cloning this repo.
* I use Linux and Visual Studio Code (VS Code) as my developing environment. So, you probably also need to download the following tools to be able to have a smoother developing experience. `C/C++`, `C/C++ Extension`, `CMake`, `CMake Extension` from VS Code.  `llvm`, `lldb` and `ninja`. ` apt install python3-dev`.

### Installing
* Download repo: `git clone --recursive https://github.com/lionlai1989/cmake_template.git`. If `--recursive` is not used when cloning, then `git submodule update --init` can be run to clone the submodules.
* TODO: ADD INSTALL CMAKE INSTALL COMMAND.

### Build, Install and Execute
```
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -S . -B build/ && cmake --build build/ -j 4
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON –S . -B build/ && cmake --build build/ -j 4 && cmake --install build/ --prefix /tmp/install-test/
cmake -G Ninja -S . -B build/ && cmake --build build/ -j 4 && (cd build/; ctest -V)
cmake -G Ninja -S . -B build/ && cmake --build build/ -j 4 && cmake --install ./build --prefix /tmp/install-test/ && (cd build/; ctest -V)
```
* Run the example command to verify the executable and libraries are rightly created.
`./build/examples/rgb2gray -i ./files/book.png -o ./files/book_gray.png` converts a RGB `image,png` to a grayscale `image_gray.png`.  
`./build/examples/rgb2gray -i ./files/book_in_scene.jpg -o ./files/book_in_scene_gray.jpg` converts a a RGB `image,jpg` to a grayscale `image_gray.jpg`.

### Developing
TODO: Try libvips, CImg, terrasect, and probably opencv. Use Clang Static Analyzer and clang-tidy.

## Help

If there is any feedbacks, comments or questions, please create an issue in this repository.

## Authors

[@lionlai](https://github.com/lionlai1989)

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments
Inspiration and useful references are listed here for further self-education.

CMake:
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
- https://stackoverflow.com/questions/69542820/cmake-include-paths-library-that-depend-on-external-library

stb_image:
- https://subscription.packtpub.com/book/game-development/9781838986193/2/ch02lvl1sec14/loading-images-with-stb


Eigen:
- https://gist.github.com/jeeho-ahn/07f943110731a0b4c2e73fc2fa8c96bf
- https://stackoverflow.com/questions/60103934/cmake-eigen3-dir-notfound
- https://stackoverflow.com/questions/12249140/find-package-eigen3-for-cmake
