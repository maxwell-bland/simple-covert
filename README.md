# DeadDrop - A Reliable, High Speed, Multicore Covert Channel via TRNG Contention
A course project for [Chris Fletcher](http://cwfletcher.net/)'s Processor  Security Course
### Team Members
[Maxwell Bland](https://acsweb.ucsd.edu/~mbland/) (email: XXX@illinois.edu)
[Jaron Mink](https://github.com/JaronMink) (email: jaronmm2@illinois.edu)
## Hardware Requirements
Intel Broadwell (5th generation) Processor or newer
## How to use
### Sender->Receiver Mode (available on *Master* Branch):
**Speed:** ~7,000 Bytes/sec
**Message limit:** No limit
**Usage:**
1. *Build Executable*:  ``make Makefile_receiver; make Makefile_sender``
2. *Run program*:  open two terminals and execute the created sender and receiver binaries via **./sender** and **./receiver**
3. *Send Message*: When ready to begin sending messages, press enter in receiver program. From there, type any ascii input into sender command line and type enter. The sender will output the speed of the transmission and the receiver will receive and output the message.

### Two-way Communication Mode (available on *two-way* Branch):
**Speed:** ~??? Bytes/sec
**Message limit:** 128 Bytes per message
**Usage:**
1. *Build Executable*:  ``make Makefile_receiver; make Makefile_sender``
2. *Run program*: open two terminals and execute the created sender and receiver binaries via **./sender** and **./receiver**
3. *Send Message*: When ready to begin sending messages, press enter in receiver program. Type up to 128 ascii characters into sender and press enter. The receiver will receive and output the characters. The receiver will now accept 128 characters of input from the terminal and the sender will now wait for a messages to be received via the covert channel. Once text has been transmitted via the receiver, the sender will output any transmitted text and the sender will then be ready for terminal input to be transmitted to the receiver once again.

## Completed Extra Credit
### SpeedRun: Achieve a speed of >6,100 Bytes/sec
### TRX: Achieve two-way communication



## How it works
Magic. But also based on the work of [D Evtyushkin et al.](http://www.cs.binghamton.edu/~devtyushkin/evtyushkin-rng-ccs16.pdf)
