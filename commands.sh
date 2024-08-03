#nvcc vector_add_thread.cu -o vector_add.out

#sudo nvprof ./vector_add.out

function profile() {
    file_name=$1
    nvcc $1 -o $1.out
    sudo nvprof ./$1.out
}

function cleanup() {
    rm *.out
}

