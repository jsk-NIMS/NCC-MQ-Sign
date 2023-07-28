#NCC-Sign and MQ-Sign from NIMS

This includes supporting documents of NCC-Sign and MQ-Sign and its implementation codes. They are submitted to 'Korean Post-Quantum Cryptography Competition' (www.kpqc.or.kr). Due to memory limitations, we upload KAT files of MQ-Sign at the security level 1.

 

##Updates

 

NCC-Sign and MQ-Sign version update (v1.0) are released.

 

The specifications of NCC-Sign has been modified as follows:

- We have added cost analysis on the Core-SVP model for all suggested parameter sets.

- We have added a new parameter set for the non-cyclotomic version and its reference implementation benchmarks.

- We have modified the parameter set for the cyclotomic trinomial case and have added a new parameter set for the use of NTT.

 

The specification of NCC-Sign has been modified as follows:

- We have removed SS and RS versions (recently cyptanalyzed by Trimoska et al. and Ikematsu et al.) of our four key generations from MQ-Sign leaving the two versions, MQ-Sign-RR and MQ-Sign-SR.

- We have added a binding technique so that a signature is identified with a unique public key and message to prevent potential attacks.


