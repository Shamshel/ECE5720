
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
_Bool verbose = false;

typedef struct Line
{
	_Bool valid_bit;
	uint64_t tag;
	size_t age;
} Line;

#define LINE_INITIALIZER ((Line){ .valid_bit = false, .tag = 0})

typedef struct Set
{
	Line * lines;
	size_t line_num;
	size_t last_line;
} Set;

#define SET_INITIALIZER ((Set){ .lines = 0, .line_num = 0, .last_line = 0})

size_t nsets = 0;
uint64_t set_mask = 0;
uint64_t set_bits = 0;

size_t block_size = 0;
uint64_t block_mask = 0;
uint64_t block_bits = 0;

uint64_t tag_mask = 0;

size_t associativity = 0;

Set * sets = 0;
size_t set_num = 0;

void init_cache(int _set_bits, int _associativity, int _block_bits)
{
	nsets = (1 << _set_bits);
	block_size = (1 << _block_bits);

	set_mask = (nsets - 1) << _block_bits;
	set_mask_n = _set_bits;
	block_mask = block_size - 1;
	block_mask_n = 0;

	tag_mask = ~(set_mask | block_mask);
	tag_mask_n = _set_bits + _block_bits;

	associativity = _associativity;

	printf("nsets: %lu\n", nsets);
	printf("set_mask: %016lX\n", set_mask);
	printf("block_size: %lu\n", block_size);
	printf("block_mask: %016lX\n", block_mask);
	printf("tag_mask: %016lX\n", tag_mask);
	printf("associativity: %lu\n", associativity);

	sets = malloc(sizeof(Set)*nsets);

	for(size_t i = 0;i < nsets;i ++)
	{
		sets[i] = SET_INITIALIZER;

		sets[i].lines = malloc(sizeof(Line)*associativity);

		for(size_t j = 0;j < associativity;j ++)
		{
			sets[i].lines[j] = LINE_INITIALIZER;

			sets[i].lines[j].age = j;
		}
	}
}
void deinit_cache()
{
	for(size_t i = 0;i < nsets;i ++)
	{
		free(sets[i].lines);
	}

	free(sets);
}


extern void address_info(int * _block, int * _set, int * _tag, uint64_t _addr);

// Hit or miss
_Bool check(uint64_t _addr)
{
	int set_id, block, tag;

	address_info(&set_id, &block, &tag, _addr);

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].tag == tag)
		{
			//cache hit
			return true;
		}
	}

	return false;
}

//Returns whether the old set was evicted
_Bool ensure(uint64_t _addr)
{
	int set_id, block, tag;

	address_info(&set_id, &block, &tag, _addr);

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].tag == tag)
		{
			//cache hit
			return false;
		}
	}

	for(size_t i = 0;i < associativity;i ++)
	{
		sets[set_id].lines[i].age ++;
	}

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].age == sets[set_id].line_num)
		{
			sets[set_id].lines[i].age = 0;
			sets[set_id].lines[i].tag = tag;

			return true;
		}
	}

	printf("Cant get here!  Bad!\n");

	return false;
}

void load_address(uint64_t _address, uint64_t _size)
{
	printf("----load_address()----\n");

	if(check(_address))
	{
		printf("Address in cache!\n");
	}
	else
	{
		printf("Address not in cache!\n");
	}
}
void store_address(uint64_t _address, uint64_t _size)
{
	uint64_t set_id = ((_address) & (set_mask)) >> set_mask_n;

	assert(set_id < nsets);

	printf("----store_address()----\n");

	printf("set_id: %lX\n", set_id);
}
void modify_address(uint64_t _address, uint64_t _size)
{
	uint64_t set_id = (_address) & (set_mask);

	assert(set_id < nsets);

	printf("----modify_address()----\n");

	printf("set_id: %lX\n", set_id);
}

int main(int _argc, char ** _argv)
{
	int arg_id = 1;

	enum { ARG_NONE, ARG_SETBITS, ARG_ASSOCIATIVITY, ARG_BLOCKBITS, ARG_TRACEFILE } next_arg;

	char trace_file[30] = "";

	uint64_t set_bits = 1, block_bits = 1, associativity = 1;

	while(_argc > arg_id)
	{
		if(_argv[arg_id][0] == '-')
		{
			if(_argv[arg_id][1] == 'v')
			{
				//verbose
				verbose = true;
				//printf("verbose!\n");
			}
			else if(_argv[arg_id][1] == 's')
			{
				//int, set index bits
				next_arg = ARG_SETBITS;
				//printf("setbits!\n");
			}
			else if(_argv[arg_id][1] == 'E')
			{
				//int, associativity
				next_arg = ARG_ASSOCIATIVITY;
				//printf("associativity!!\n");
			}
			else if(_argv[arg_id][1] == 'b')
			{
				//int, block bits
				next_arg = ARG_BLOCKBITS;
				//printf("blockbits!!\n");
			}
			else if(_argv[arg_id][1] == 't')
			{
				//trace file, cstring
				next_arg = ARG_TRACEFILE;
				//printf("tracefile!\n");
			}
			else if(_argv[arg_id][1] == 'h')
			{
				printf("haha you're on your own!\n");
			}
		}
		else
		{
			if(next_arg != ARG_NONE)
			{
				switch(next_arg)
				{
					case ARG_SETBITS:
						set_bits = atoi(_argv[arg_id]);
						break;
					case ARG_ASSOCIATIVITY:
						associativity = atoi(_argv[arg_id]);
						break;
					case ARG_BLOCKBITS:
						block_bits = atoi(_argv[arg_id]);
						break;
					case ARG_TRACEFILE:
						strncpy(trace_file, _argv[arg_id], 30);
						trace_file[29] = '\0';
						break;
					default:
						break;
				}
			}
		}

		arg_id ++;
	}

	printf("trace file: \"%s\"\n", trace_file);

	init_cache(set_bits, associativity, block_bits);
	deinit_cache();

	load_address(0x00012341234, 4);
}
*/

#define BLOCK_SIZE 8
#define X 16
#define Y 16

int U[X][Y];
int V[Y][X];

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, k, l, tmp;

  for(k = 0; k < M/BLOCK_SIZE; k++)
    {
      for(l = 0; l < N/BLOCK_SIZE; l++)
	{

	  for(i = 0; i < BLOCK_SIZE; i++)
	    {
	      for(j = 0; j < i; j++)
		{
		  tmp = A[i+k*BLOCK_SIZE][j+l*BLOCK_SIZE];
		  A[i+k*BLOCK_SIZE][j+l*BLOCK_SIZE] = A[j+k*BLOCK_SIZE][i+l*BLOCK_SIZE];
		  A[j+k*BLOCK_SIZE][i+l*BLOCK_SIZE] = tmp;

		}

	    }
	  
	  for(i = 0; i < X; i++)
	  {
	    for(j = 0; j < Y; j++)
		{
		  printf("%d ",U[j][i]);

		}

	    printf("\n\r");

	  }

	  printf("\n\r");


	}

    }

  for(l = 0; l < N/BLOCK_SIZE; l++)
    {
	for(k = 0; k < l; k++)
	{

	  for(i = 0; i < BLOCK_SIZE; i++)
		{
		  for(j = BLOCK_SIZE-1; j >= 0; j--)
		{
		  B[i+k*BLOCK_SIZE][j+l*BLOCK_SIZE] = A[j+k*BLOCK_SIZE][i+l*BLOCK_SIZE];
		}

		}
	}
	}

}

int main(int _argc, char ** _argv)
{
  for(int i = 0; i < X; i++)
    {
      for(int j = 0; j < Y; j++)
	{
	  U[i][j] = i;
	  V[i][j] = 0;

	}

    }

  for(int i = 0; i < X; i++)
    {
      for(int j = 0; j < Y; j++)
	{
	  printf("%d ",U[j][i]);

	}

      printf("\n\r");

    }

  printf("\n\r");

  transpose_submit(Y, X, U, V);

printf("Final:\n");
	for(int i = 0; i < Y; i++)
	{
		for(int j = 0; j < X; j++)
		{
			printf("%d ",V[j][i]);
		}

		printf("\n\r");
	}

	printf("\n\r");


}
