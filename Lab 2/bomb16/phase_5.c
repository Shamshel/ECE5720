

long long int ebx;

void phase_5(char * _input)
{
	ebx = edi;

	string_length();

	if(eax != 0x6)
		explode_bomb();

	eax = esp;

	esi = ebx + 0x6;

	edx = 0x401bf0;

	L1:
	ecx = (char)(*ebx)

	ecx &= 0xf;

	ecx = (char)*(edx + ecx*1)

	eax = ecx & 0xFF;

	rbx ++;

	rax ++;

	if(esi == ebx)
	{
		*(esp + 0x6) = 0;
		edi = esp;
		esi = 0x401b9c;

		strings_not_equal();

		if(eax != 0)
			explode_bomb();
	}
	else
	{
		goto L1;
	}
}


void phase_5(char * _input)
{
	// this is rsp
	char [6] str;
	// this is rsp + 0x6
	// ebx is _input
	char * c = _input;

	int len = string_length();

	if(len != 0x6)
		explode_bomb();

	// eax is a
	char * a = str;
	// esi is end
	// esi = ebx + 0x6;
	char * end = _input + 6;

	// edx is crypto-string
	// edx = 0x401bf0;
	const char * crpypto = "isrveawhobpnutfg";

	13, 0, 13, 5, 11, 1

	0xD0D5B1

	-@-EKA

	do
	{
		char i = *(char*)c;

		i &= 0xf;

		unsigned int l = *(unsigned char *)(crypto + i)

		*a = i & 0xFF;

		c ++; // top kek 2014

		a ++;
	}
	while(end != c)

	*(esp + 0x6) = 0;
	edi = esp;
	esi = 0x401b9c;

	strings_not_equal();

	if(eax != 0)
		explode_bomb();
}
