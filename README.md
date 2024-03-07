# Experiment: convert image to and from I420 format

## Get Started

```
mkdir build && cd build
cmake ..
make -j12
./main
```

## Observations

* The results generated with OpenCV and libyuv are not exactly the same.
* Converting the image back and forth results in bigger and bigger difference in libyuv but not in OpenCV.
