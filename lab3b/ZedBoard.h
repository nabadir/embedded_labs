
#ifndef _ZEDBOARD_
#define _ZEDBOARD_


class ZedBoard
{
private:
	int fd;
	char *pBase;

public:
	ZedBoard();
	~ZedBoard();

	void RegisterWrite(int offset, int value);
	int RegisterRead(int offset);

}; //Methods for ZedBoard on lines 000-000



/*
   Initialize general-purpose I/O
 * - Opens access to physical memory /dev/mem
 * - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param fd File descriptor passed by reference, where the result
 * of function 'open' will be stored.
 * @return Address to virtual memory which is mapped to physical,
 * or MAP_FAILED on error.
 */
ZedBoard::ZedBoard()
{
	fd = open( "/dev/mem", O_RDWR);


	pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, gpio_address);

	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1); // Returns 1 to the operating system;
	}
}

/*
 * Close general-purpose I/O.
 *
 * @param pBase Virtual address where I/O was mapped.
 * @param fd File descriptor previously returned by 'open'.
 */
ZedBoard::~ZedBoard()
{
	munmap(pBase, gpio_size);
	close(fd);
}

/*
 * Write a 4-byte value at the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @parem offset Offset where device is mapped.
 * @param value Value to be written.
 */ 
void ZedBoard::RegisterWrite(int offset, int value)
{
	* (int *) (pBase + offset) = value;
} 

/*
 * Read a 4-byte value from the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @param offset Offset where device is mapped.
 * @return Value read.
 */
int ZedBoard::RegisterRead(int offset)
{
	return * (int *) (pBase + offset);
}


#endif


