# xreal-vio-vr

A lightweight Linux spatial computing stack for the XREAL Ultra

## Purpose

This repository is aimed at creating a reproducible, modular pipeline for using the XREAL Air 2 Ultra on Linux.  
It serves both as a reference implementation and a quick-start integration method for combining:

- Stereo SLAM via Basalt
- Pose injection into Monado (OpenXR)
- Controller and hand input
- Linux-native 3D desktop overlays

## Description

A modular setup to enable stereo SLAM, IMU tracking, controller input, and 3D workspace rendering with the XREAL Air 2 Ultra headset on Linux.

## Stack Components

- Camera + IMU access via UVC and USB serial
- VIO backend using patched Basalt with fisheye624 model
- Pose injection layer through Monado (OpenXR runtime)
- Joy-Con input via evdev or user-space driver
- Optional hand tracking pipeline (future module)
- wlroots-based compositor overlay (wlx-overlay-s)

## Dependencies

- `basalt` (VIO)
- `basalt-headers` (camera models)
- `wlx-overlay-s` (Wayland overlay compositor)
- `monado` (OpenXR runtime)
- `udev` and `libusb` for device interfaces
- `libcamera` or raw video stream handler

## Build Notes

This stack is not plug-and-play. Yet.

## Contributing

Contributions are welcome. Keep patches modular and comments minimal.
