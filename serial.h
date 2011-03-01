#ifndef SERIAL_H
#define SERIAL_H

#define START_BYTE 'x' //0x46

// commands

#define SPEAD_CMD		'a' // 0x04
#define PID_CMD			'e'


struct sersetpid
{
	int p1;
	int i1;
	int d1;

	int p2;
	int i2;
	int d2;
} __attribute__((__packed__));

struct sergetpos
{
	int index1;
	unsigned int pos1;
	int index2;
	unsigned int pos2;
	int spead1;
	int spead2;
} __attribute__((__packed__));

struct sersetspead
{
	int spead1;
	int spead2;
} __attribute__((__packed__));


union packet
{
	struct sersetpid setpid;
	struct sergetpos getpos;
	struct sersetspead setspead;

};
#endif // SERIAL_H
