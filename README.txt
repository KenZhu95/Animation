Name: Weiyu Zhu
UT EID: wz4245

To build, use the following commands:

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8

excutable file will be "build/bin/animation"

For Extra Credits:

1. Not sure about it, but translation is also implemented in this milestone, that is, each keyframe stores a translation information of the root joint. The translation can be shown in the animation.

2. Toggle CTRL+L to save animation file, a dialog box will pop up and user can input a name for the saved json file. Click the "save" button to save the file. Then click the close button of the dialog window and from left corner select "minimize", the dialog window will not affect following functionality of the whole program. Clicking the close button will not close the window, however. This might be some conflict of the FLTK and something else. 

3. A "cursor" is implemented. Toggle "Z" to switch between "insert" and "common" mode. In "insert" mode, the top of the selected preview will be red. Toggle "I" under "insert" mode to insert a keyframe before the selected keyframe. "F" is still available to append a keyframe to the end under "insert" mode.

4. A scroll bar is implemented for the list of preview images. Separate shaders are created. Drag the scroll bar can get the same function as mouse scrolling for the preview images.

5. Toggle "V" will play the whole animation once, from the beginning, and save a file "output.mp4" under the current directory. This is implemented with ffmpeg.

6. Toggle "N" to switch between "spline" mode and "linear" mode for the quartenion interpolation. "spline" mode implements spherical spline interpolation. It could slightly change the quatenions at the beginning frame and the ending frame, but the animation seems reasonable. The translation is still interpolated linearly, I think that's the most correct and reasonable one.

One day late, use one late day.
