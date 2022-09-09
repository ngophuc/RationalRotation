# RationalRotation

This code aims at performing a rational rotation on 2D digital image given the rotation as a Pythagorean triplet (a, b, c) 
such that a^2 + b^2 = c^2.

# Dependencies
- DGtal (https://dgtal.org/)
- GMP (https://gmplib.org/)

# Install
```sh
mkdir build; cd build
cmake ..
make -j 5
```    
# Running command
```sh
./Rotation2D <input_image> [[a b] c]
```
# Example of valid commands
```sh
./Rotation2D ../ball_r5.pgm

./Rotation2D ../ball_r5.pgm 3 4 5

./Rotation2D ../ball_r5.pgm 3 4

```
# Example of invalid commands
```sh
./Rotation2D ball_r5.pgm 3 5

./Rotation2D ball_r5.pgm 3 4 6

```
