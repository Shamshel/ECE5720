


void phase_3(char * _input)
{
	int a = 0;
	int b = 0;

	int valid = sscanf("%d %d", &a, &b);

	if(valid <= 1)
		explode_bomb();

	int eax = a;

	switch(a)
	{
		case 1:
			eax = 0x177;
			break;
		case 0:
			eax = 0x365;
			break;
		case 2:
			eax = 0x3dc;
			break;
		case 3:
			eax = 0x174;
			break;
		case 4:
			eax = 0x317;
			break;
		case 5:
			eax = 0x358;
			break;
		case 6:
			eax = 0x1b4;
			break;
		case 7:
			eax = 0x17d;
			break;
		default:
			explode_bomb();
			eax = 0;
	}

	if(eax != b)
		explode_bomb();
}

(gdb) x/8xg 0x401bb0
0x401bb0 <__dso_handle+440>:    0x0000000000401174      0x000000000040116d
0x401bc0 <__dso_handle+456>:    0x000000000040117b      0x0000000000401182
0x401bd0 <__dso_handle+472>:    0x0000000000401189      0x0000000000401190
0x401be0 <__dso_handle+488>:    0x0000000000401197      0x000000000040119e

0 - 0x0000000000401174
1 - 0x000000000040116d
2 - 0x000000000040117b
3 - 0x0000000000401182
4 - 0x0000000000401189
5 - 0x0000000000401190
6 - 0x0000000000401197
7 - 0x000000000040119e

input of "1 375" should work
