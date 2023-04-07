# C++ project template with CMake

Hey there! As a software engineer, I'm always striving to level up my C++ skills. And let me tell you, mastering CMake is an absolute must on that journey. Sure, there are loads of CMake tutorials out there, but most of them fall a bit short when it comes to bigger projects. Don't get me wrong, they're fantastic for getting the basics down. But when it comes to creating a real-world project, I found that I needed to combine multiple small tutorials to make it work. That's why I went ahead and put together this C++ project template with CMake. My hope is that I can use this template straight-up without having to manually cobble together a project from a bunch of small tutorials in the future.


## Description

This project demonstrates how to use CMake and includes the usage of the following tools:
- [eigen library](https://gitlab.com/libeigen/eigen)
- [stb image library](https://github.com/nothings/stb)
- [xtensor library](https://github.com/xtensor-stack/xtensor)
- Namespace package
- GoogleTest

## Getting Started

### Dependencies
Before you start, you need to make sure you have the following dependencies installed:
* **CMake 3.22.0 or higher:** If you don't have CMake installed, or if you need to update it, you can follow the instructions [here](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line). To use version 3.22, you can download it from https://cmake.org/files/v3.22/cmake-3.22.6.tar.gz.
* **Eigen library:** This is a C++ library that we'll use in our project. Don't worry about installing it separately, as it's included as a git submodule in our repository.
* **stb image library:** This is a C library for loading and saving images. It's also included as a git submodule, so you don't need to do anything extra.
* **xtensor-assosiated library:** xtensor is a numpy for C++ library. All
  required code is added as git submodules. Unlike eigen and stb library, I
  can't figure out a way to just add folders to make CMake work. We need to
  first install xtensor and then use it. Please follow the instruction below:
  * Isntall xtl:
  ```
  (cd extern/xtl && cmake -D CMAKE_INSTALL_PREFIX=/tmp/xtl-install && make install)
  ```
  * Install xtensor:
  ```
  (cd extern/xtensor && cmake -D CMAKE_INSTALL_PREFIX=/tmp/xtensor-install -DCMAKE_PREFIX_PATH=/tmp/xtl-install && make install)
  ```
  * Install xsimd:
  ```
  (cd extern/xsimd && cmake -D CMAKE_INSTALL_PREFIX=/tmp/xsimd-install && make install)
  ```
  

* **Development tools for Linux and VS Code:** To develop our project, we'll be using Linux and Visual Studio Code (VS Code). To have a smoother experience, you should install the following tools and extensions for VS Code:
  * `C/C++`
  * `C/C++ Extension`
  * `CMake`
  * `CMake Extension`
  * `llvm`
  * `lldb`
  * `ninja`
  * `python3-dev` (install this with apt install python3-dev)

### Downloading
* To download this repository, run the following command:
```shell
git clone --recursive https://github.com/lionlai1989/cmake_template.git
```
If you forgot to use the `--recursive` option when cloning, you can still clone the submodules by running the command `git submodule update --init --recursive`.

### Build, Install and Execute
- Build:  
  To build the project, run the following command:
  ```
  cmake -G Ninja -S . -B build/ && cmake --build build/ -j 4 && (cd build/; ctest -V)
  ```
  If the build is successful, the tests will be run automatically and you should see the message:
  ```
  100% tests passed, 0 tests failed out of 5
  ```

- Install  
  This package can be installed in your system or a custom location in your file system. To install it, run the following command:
  ```
  cmake --install build/ --prefix /tmp/install-test/
  ```
  The above code installs the package in `/tmp/install-test/`.
  
- Execute  
  The installation can be tested with the following command:
  ```
  /tmp/install-test/bin/rgb2gray -i /tmp/install-test/bin/book_in_scene.jpg -o ./examples/files/book_in_scene_gray.jpg -m eigen
  /tmp/install-test/bin/rgb2gray -i /tmp/install-test/bin/book.png -o ./examples/files/book_gray.png -m xtensor
  ```
  It will use `eigen` to create `book_in_scene_gray.jpg` and `xtensor` to create `book_gray.png` in `./examples/files/`. Here is an example input and output images.
  <p align="left">
    <img src="./examples/files/book_in_scene.jpg" width="300" title="Input RGB Image with JPG Format">
    <img src="./examples/files/book_in_scene_gray.jpg" width="300" title="Output Grayscale Image with JPG Format">
  </p>
  <p align="left">
    <img src="./examples/files/book.png" width="300" title="Input RGB Image with PNG Format">
    <img src="./examples/files/book_gray.png" width="300" title="Output Grayscale Image with PNG Format">
  </p>

### Developing
- Using Libraries in this Package:  
  To use the libraries included in this package, it is necessary to include the appropriate headers in your code and link to the libraries in your project.

- Future Developments:  
  In the future, there are plans to expand this project to include additional example libraries to further explore their use. These libraries include libvips, CImg, terrasect, and opencv. Additionally, the code will be further improved by utilizing tools such as Clang Static Analyzer and clang-tidy to identify potential issues and enhance overall code quality.

## Contributing

Your feedback, comments, and questions about this project are welcome, as are any contributions you'd like to make. Please feel free to create an issue or a pull request in this repository. Together, let's improve this template and make life easier for C++ programmers.

## Authors

[@lionlai](https://github.com/lionlai1989)

## Version History

* 0.0.1
    * Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments
Explore the inspiration and references listed here to further expand your knowledge and sharpen your skills.

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

XTensor:
- https://github.com/xtensor-stack/xtensor
- https://github.com/xtensor-stack/xsimd
- https://github.com/xtensor-stack/xtl
