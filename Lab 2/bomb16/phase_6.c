
int node0;

void phase_6(const char * _input)
{
	int val = strtol(_input);

	node0 = val;

	fun6(&node0);

	edx = 0x1;

	L1:
	eax = *(0x8 + eax);

	edx ++;

	if(edx != 0x9)
		goto L1;

	eax = *eax;

	if(node0 != eax)
		explode_bomb();
}

int node1;

void fun6(int * g)
{
	r8 = *(g + 0x8);
	*(g + 0x8) = 0;

	rax = rdi;
	rcx = rdi;

	if(r8 != 0)
		goto L1;
	goto L2;

	rcx = rdx;

	rdx = *(rcx + 0x8)

	if(rdx == 0)
		goto L3;
	if(rdx > 0)
		goto L4;

	rdi = rcx;
	rcx = rdx;

	if(rcx != rdi)
		goto L5;

	rax = r8;

	goto L6;

	*(rdi + 0x8) = r8;
	rdx = *(r8 + 0x8);
	*(r8 + 0x8) = rcx;

	if(rdx == 0)
		goto L2;

	r8 = rdx;
	rcx= rax;
	rdi = rax;

	if(rcx == 0)
		goto L7;

	
}

void phase_6(const char * _input)
{
	int val = strtol(_input);

	node0 = val;

	fun6(&node0);

	int i = 0x1;

	void * ptr = eax;

	do
	{
		ptr = *(0x8 + ptr);

		i ++;
	}
	while(i != 0x9);

	int avalue = *ptr;

	if(node0 != avalue)
		explode_bomb();
}

