# Description

Implementation of Harris Corner in C++.

This repository contains the implementation of finding Harris Corners as per A combined corner and edge detector by Harris et al.


## Usage

To run the following code:
1. Clone the repo
2. Open a new terminal
3. Type the following:

```console
mkdir build
cd build
cmake ..
make 
```
This will compile the code. There are 2 options in the code. In the first, one can feed an input image and the detector will find the corners in the image. In the second option, the user can feed in a video and the detector will find the corners and play the video with corners overlayed over it in real time.

To run the first option, do:
```console
./harris 1 <path_to_image>
```

To run the first option, do:
```console
./harris 2 <path_to_video>
```


## Sample Results

Displaying a sample result of the code. We can see that the corners of the cube are detected by the detector and highlighted in red.
![alt text](https://github.com/akshay-iyer/Harris-Corner/blob/master/Harris2.png)
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

