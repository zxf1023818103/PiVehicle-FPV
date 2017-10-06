# PiVehicle-FPV
This is a part of [PiVehicle](https://github.com/zxf1023818103/PiVehicle/).

## Todo
- Add Template class `FpvCameraFrame` instead of `void *` to ensure memory safety.
- Process camera device lost event in class [`FpvCameraLinux`](https://github.com/zxf1023818103/PiVehicle-FPV/blob/master/FpvCameraLinux.h#L11).
- Refactor function [`CreateFpvCamera`](https://github.com/zxf1023818103/PiVehicle-FPV/blob/master/create_fpv_camera_linux.cc#L8). Only device verification and class construction part will be left.
- Unit test (Use Google Test).
