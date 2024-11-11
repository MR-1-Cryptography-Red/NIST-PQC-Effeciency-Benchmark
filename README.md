This test file can be added to the main source code folder of a cryptographic algorithm that has been submitted to NIST's PQC submissions. This was done using a Virtualbox Ubuntu Linux VM.

Make sure to install libssl-dev on the machine.
Compile the program using:
gcc *.c -o tests -lcrypto -Wl,-Bstatic -lcrypto -Wl,-Bdynamic -ml

Then run:
./tests

