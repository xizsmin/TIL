// simple implementation

int* finalPrices(int* prices, int pricesSize, int* returnSize){
    printf("pricesSize: %d\n", pricesSize);
    returnSize[0] = pricesSize;
    
    int *ret= (int *)malloc(sizeof(int)*pricesSize);
    int discounted = 0;
    for(int i=0; i<pricesSize;++i) {
        int cur = prices[i];
        discounted = 0;
        for(int j=i+1; j<pricesSize; ++j) {
            if (prices[j] <= cur) {
                discounted = 1;
                printf("ret[%d] <- %d\n", i, cur - prices[j]);
                ret[i] = cur - prices[j];
                break;
            }
            
        }
        if (discounted == 0) {
            ret[i] = cur;
            printf("* ret[%d] <- %d\n", i, cur);// - prices[j]);
        }
    
    }
    
    return ret;

}

