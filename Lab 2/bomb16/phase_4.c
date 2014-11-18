
int eax;
int edi;
int ebx;

void func4()
{
	ebx = edi;
	eax = 1;

	if(edi <= 1)
		return;

	edi = ebx - 1;

	func4();

	ebp = eax;

	edi = ebx - 2;

	func4();

	eax += ebp;
}

void phase_4(char * input)
{
	int val = 0;

	int result = sscanf(input, "%d", &val);

	if(result != 1 || val <= 0)
	{
		explode_bomb();
	}

	edi = val;

	func4();

	if(eax != 0x2AC2)
	{
		explode_bomb();
	}
}
