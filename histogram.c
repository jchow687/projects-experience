#include <stdio.h>
#include <stdlib.h>


int main(void){
    	// To start: lets read the series of integers //
    	// read from stdin //   
    	int num_of_bins = 16;
    	int bin_size = 1;
    	int collection[num_of_bins];
    	int range = (bin_size * num_of_bins);
    	int input;
    	printf("%d bins of size %d for range [0,%d)\n", num_of_bins, bin_size, range);
    	for(int i = 0; i < num_of_bins; i++){
                collection[i] = 0;
        }

    	// checks the stdin is valid //
    	while (scanf("%d", &input) != EOF){
            	// checks if its outside the range//
            	while (input >= range){
                    	// if it is then it doubles the range and bin size//
                    	bin_size *= 2;
                    	range = bin_size * num_of_bins;
                            	printf("%d bins of size %d for range [0,%d)\n", num_of_bins, bin_size, range);
            	// compresses the bins //
                    	for(int i = 1; i < num_of_bins; i++){
                            	collection[i/2] += collection[i];
				collection[i] = 0;
                    	}
            	}
            	// updating the collection
            	int collection_update = input/bin_size;
            	collection[collection_update]++;
    	}
    	//creating the columns of data//
    	for(int i = 0; i < num_of_bins; i++){
            	printf("[%3d:%3d] ", i*bin_size, (i+1)*bin_size-1);
            	for(int j = 0; j < collection[i]; j++){
						printf("*");
				}
				printf("\n");
		}
		return 0;
}

