
## RSA and Diffie Hellman Key exchange

RSA : 

1) Generate prime numbers p and q
2) find out n(p*q) and phi(n) = (p-1)*(q-1)
3) find e such that gcd(phi,e)=1
4) find d such that de=1mod(phi)
5) for encryption m^e % n
6) for decryption c^d % n

Diffie Hellman : 

1) Input q and alpha
2) Input alice private key a
3) alice public key A = alpha^a mod q
4) Input bob private key b
5) bob public key B = alpha^b mod q
6) exchange public keys
7) alice key = alpha^B mod q
8) bob key = alpha^A mod q
