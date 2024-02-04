gunzip bunny200.tri.gz
./viewer.out bunny200.tri
echo
time ./zipper1.out bunny200.tri bunny200_small.tri 50 50 50
./viewer.out bunny200_small.tri
echo
time ./zipper2.out bunny200.tri bunny200_small.tri 50 50 50
./viewer.out bunny200_small.tri
echo
time ./zipper3.out bunny200.tri bunny200_small.tri 50 50 50
./viewer.out bunny200_small.tri
