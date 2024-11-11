#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "api.h"
// Make sure that you change the api.h to match the file location of the crypto api.

#define TEST_RUN 1000

int main(void) {
    printf("%s\n", CRYPTO_ALGNAME );
    printf("sk size: %d\n", CRYPTO_SECRETKEYBYTES );
    printf("pk size: %d\n", CRYPTO_PUBLICKEYBYTES );
    printf("signature overhead: %d\n\n", CRYPTO_BYTES );

    unsigned char sm[256 + CRYPTO_BYTES];
    unsigned char m[256];
    strcpy((char*) m, "CryptoRed"); //Change the message to whatever you wish
    unsigned long long mlen = 256;
    unsigned long long smlen;
    unsigned char *pk = (unsigned char *)malloc( CRYPTO_PUBLICKEYBYTES );
    unsigned char *sk = (unsigned char *)malloc( CRYPTO_SECRETKEYBYTES );
    
    //Open up the file and name it based on the crypto name
    FILE *fpt;
    char name[100];
    strcpy(name, CRYPTO_ALGNAME);
    strcat(name, ".csv");
    fpt = fopen(name, "w+");



    printf("===========  test crypto_sign_keypair(), crypto_sign(), and crypto_sign_open()  ================\n\n");
    
    for (unsigned i = 0; i < TEST_RUN; i++) {
    // In each rep, take the clock cycle number from before and after the functions. Then divide by CLOCKS_PER_SEC.
        clock_t begin_keygen = clock();
        crypto_sign_keypair( pk, sk);
        clock_t end_keygen = clock();
        
        clock_t begin_sign = clock();
        crypto_sign( sm, &smlen, m, mlen, sk );
        clock_t end_sign = clock();
        
        clock_t begin_verify = clock();
        crypto_sign_open( m, &mlen, sm, smlen, pk );
        clock_t end_verify = clock();
        
        fprintf(fpt, "%d, %f, %f, %f\n", (i+1), ((double) (end_keygen - begin_keygen)) / CLOCKS_PER_SEC, 
            ((double) (end_sign - begin_sign)) / CLOCKS_PER_SEC, ((double) (end_verify - begin_verify)) / CLOCKS_PER_SEC);
    }
    
    free( pk );
    free( sk );
    printf("all (%d) tests passed.\n\n", TEST_RUN);

    return 0;
}

