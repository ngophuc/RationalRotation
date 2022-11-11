# RationalRotation

This code aims at performing a rational rotation on 2D /3D digital image 

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
./RationalRotation -h

Apply 2D/3D rational rotation on a given image.
 Typical use example:
 	 RationalRotation --input <filename> --dim [2 3] --ox 1.0 --oy 1.0 --oz 1 -a 1.2 --ax 1 --ay 1 --az 0 --tx 1 --ty 0 --tz 0 
 Example:
 RationalRotation -d 2 -i ../ball_r5.pgm --pa 3 --pb 4 --pc 5 
 RationalRotation -d 3 -i Al.100.vol --qa 3 --qb 4 --qc 5 --qd 5

Usage: /Users/hngo/Documents/Codes/Code_Dev/RationalRotation/build/Debug/RationalRotation [OPTIONS] 1

Positionals:
  1 TEXT:FILE REQUIRED                  Input file.

Options:
  -h,--help                             Print this help message and exit
  -i,--input TEXT:FILE REQUIRED         Input file.
  -d,--dim INT=2                        Dimension: 2 or 3 (default 2)
  -a,--angle FLOAT=0                    Rotation angle in degrees (default 0)
  --pa INT=3                            Pythagorean triplet for 2D rotation (default 3)
  --pb INT=4                            Pythagorean triplet for 2D rotation (default 4)
  --pc INT=5                            Pythagorean triplet for 2D rotation (default 5)
  --ax INT=1                            X component of 3D rotation axis (default 1)
  --ay INT=0                            Y component of 3D rotation axis (default 0)
  --az INT=0                            Z component of 3D rotation axis (default 0)
  --qa INT=0                            Quaternion for 3D rotation (default 0)
  --qb INT=1                            Quaternion for 3D rotation (default 1)
  --qc INT=0                            Quaternion for 3D rotation (default 0)
  --qd INT=0                            Quaternion for 3D rotation (default 0)
```
# Examples of valid commands
```sh
./RationalRotation -d 2 -i ../ball_r5.pgm --pa 3 --pb 4 --pc 5 

./RationalRotation -d 2 -i ../ball_r5.pgm -a 45

./RationalRotation -d 3 -i ../Al.100.vol --qa 3 --qb 4 --qc 5 --qd 6

./RationalRotation -d 3 -i ../Al.100.vol -a 45 --ax 1 --ay 2 --az 3

```
# Examples of invalid commands
```sh
./Rotation2D -i ball_r5.pgm 3 5

./Rotation2D -i Al.100.vol

```
