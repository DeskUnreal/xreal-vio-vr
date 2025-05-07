
#!/bin/bash

# Step 1: Uninstall current version of Eigen
echo "Uninstalling current version of Eigen..."
sudo apt remove -y libeigen3-dev

# Step 2: Download Eigen 3.3.7
echo "Downloading Eigen 3.3.7..."
cd ~
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz
tar -xzf eigen-3.3.7.tar.gz
cd eigen-3.3.7

# Step 3: Install Eigen to system (or specify a local directory)
echo "Installing Eigen 3.3.7..."
mkdir build && cd build
cmake ..
sudo make install

# Step 4: Rebuild ORB-SLAM3
echo "Rebuilding ORB-SLAM3..."
cd ~/xreal/xreal-vio-vr/slam/orbslam3
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)

echo "Process completed successfully!"
