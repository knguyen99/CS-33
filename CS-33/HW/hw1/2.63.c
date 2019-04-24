unsigned long srl(unsigned long x, int k) {

	/* Perform shift arithmetically */
	unsigned long xsra = (int) x >> k;

	//creates mask with 1's in the unimportant bits and 0's in important bits
	unsigned long mask = -1 << ((sizeof(unsigned long)*8)-k);

	//reversing mask puts 0's in unimportant bits and 1's in important bits
	//by using & only copies the 1's that are important
	//important meaning that aren't just fill bits
	return xsra & ~mask;
}

long sra(long x, int k) {
	/*Perform shift logically */
	long xsrl = (unsigned long)x >> k;

	//finds out number of bits in long
	int w = sizeof(long)*8;

	//creates mask with 1's in bits that may or may not to be changed
	long mask = -1 << (w-k);

	//creates a filter to check the sign of x
	long m = 1 << (w-1);

	// checks if x is neg or pos, if x is neg, newmask will all be ones
	long newmask = !(x&m)-1;

	//fixing mask
	mask = mask & newmask;

	return xsrl | mask;
} 
