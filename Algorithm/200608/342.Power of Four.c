// simple math

bool isPowerOfFour(int num){
    if (num <= 0) return false;
    while (num) {
        if (num & 3) return (num == 1);
        num >>= 2;
    }
    return false;
}

