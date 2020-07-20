To run the java file.
java <CACHE_SIZE> <ASSOC> <REPLACEMENT> <WB> <TRACE_FILE>
<CACHE_SIZE> is the size of the simulated cache in bytes ex. 8192, 16384, 32768, 65536...
<ASSOC> is the associativity: Powers of 2 ex. 1, 2, 4, 8, 16...
<REPLACEMENT> replacement policy: 0 means LRU, 1 means FIFO
<WB> Write-back policy: 0 means write-through, 1 means write-back
<TRACE_FILE> trace file name with full path
Example:
java 32768 8 0 1 home/TRACES/XSBench.t
or
java 32768 8 0 1 XSBench.t
Depends on where you store your trace file when running

Takes a bit of time depending on the system to parse through the trace file