# CPE-593-PROJECT
CPE-593 PROJECT: RSA

Project: Implement RSA using a Big Integer library
Team Members: Avro, Karan and Vincent.
Language: C++
Libraries: Big Integer, Math.h, stdlib

Assignment:
Implement RSA using a big integer library. It doesn’t have to be production quality, but you would need to implement Diffie-Hellman key exchange and use AES-256 (you don’t have to write that) to exchange secret messages.

Project sections:
- Big Integer prime numbers (generate prime numbers)
- implement backend to encrypt/decrypt (use prime numbers)
https://www.geeksforgeeks.org/rsa-algorithm-cryptography/
- add diffie hellman key exchange for initial rsa key (not our own code)
https://www.geeksforgeeks.org/implementation-diffie-hellman-algorithm/ 

Project Extension/Enhancement:
- add front end to exchange messages (webpage or sockets?)
- write our own big integer data structure
https://codeforces.com/blog/entry/16380 
https://paste.ubuntu.com/10270983/ 

Project Work Breakdown:

Vincent:
1.	Calculate prime numbers
2.	Documentation

Karan:
1.	Encrypt/decrypt a message using RSA encryption
2.	Create presentation

Avro:
1.	Git Repo and performance evaluation
2.	Implement key exchange(Diffie-Hellman)

Weekly Call: Wednesday: 8 pm

Goals (I = Independent, D = Dependent)

•	Setup git repo (D)
•	Calculate prime numbers  (I)
•	Encrypt/decrypt a message in the same program (I)
•	Implement big integer library (D)
•	Calculate large prime numbers with big integer (I)
•	Implement key exchange (I)Create presentation (along the way) (D)
•	Write paper (along the way) (D)


Compilation:
g++ -Wall .\PrimeGenerator.cpp  .\main.cpp -lgmp -lgmpxx