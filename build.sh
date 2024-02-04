if [ -f main.o ]; then
    make clean
fi

for version in 0 1 2 3; do
    qmake "VERSION=$version" && make && make clean 
done
