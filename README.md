# Algorithms analysis and design lab work.

[![Build Status](https://travis-ci.org/dkurtaev/graph_skeletonizer.svg?branch=master)](https://travis-ci.org/dkurtaev/graph_skeletonizer)

Minimal edge-weighted graph skeleton.  
Different methods implementation and comparison.

### Dependencies
* OpenCV
```
sudo apt-get install libopencv-dev
```
### How to use it
Clone repository on your machine:
```
git clone https://github.com/dkurtaev/graph_skeletonizer.git
cd graph_skeletonizer
```
Initialize submodules (google-test and glog):
```
git submodule init
git submodule update
```
Uncomment line ```add_subdirectory("./tools")``` inside ```CMakeLists.txt``` at the root of project (disabled for Travis).
