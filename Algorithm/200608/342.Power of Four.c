
// solution 1
bool isPowerOfFour(int num){
    if (num <= 0) return false;
    while (num) {
        if (num & 3) return (num == 1);
        num >>= 2;
    }
    return false;
}

// solution 2
bool isPowerOfFour(int num){
    return ((num > 0) && ((!((num) & (num-1))) && (!((num) & 0xAAAAAAAA))));
}

