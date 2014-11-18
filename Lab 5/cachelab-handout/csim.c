//Cody Herndon
//A01393116

//David Petrizze
//A01625825

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "cachelab.h"

#define OP_BUF_LEN 4098
#define IN_BUF_LEN 4098

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

/********************************/
/* GLOBALS :DDDD */
_Bool verbose = false;


size_t nsets = 0;
uint64_t set_mask = 0;
uint64_t set_mask_n = 0;
uint64_t set_bits = 0;

size_t block_size = 0;
uint64_t block_mask = 0;
uint64_t block_mask_n = 0;
uint64_t block_bits = 0;

uint64_t tag_mask = 0;
uint64_t tag_mask_n = 0;

size_t associativity = 0;

Set* sets = 0;
size_t set_num = 0;


size_t num_evictions = 0;
size_t num_misses = 0;
size_t num_hits = 0;

/*******************************/

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
	set_num = nsets;

	for(size_t i = 0;i < nsets;i ++)
	{
		sets[i] = SET_INITIALIZER;

		sets[i].lines = malloc(sizeof(Line)*associativity);
		sets[i].line_num = associativity;

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

void address_info(int* _block, int* _set, int* _tag, uint64_t address)
{
  //set_bits
  //block_bits
  //tag_bits

  //set_mask
  //block_mask
  //tag_mask

  int set = 0;
  int block = 0;
  int tag = 0;
 

  block = (address & block_mask);
  set = (address & set_mask)>>block_bits;
  tag = (address & tag_mask)>>(block_bits+set_bits);

  *_set = set;
  *_block = block;
  *_tag = tag;

}

// Hit or miss
_Bool in_cache(uint64_t _addr)
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

_Bool line_free(uint64_t _addr)
{
	int set_id, block, tag;

	address_info(&set_id, &block, &tag, _addr);

	for(size_t i = 0;i < associativity;i ++)
	{
		if(!sets[set_id].lines[i].valid_bit)
		{
			return true;
		}
	}

	return false;
}

int global_timestamp = 0;

size_t get_oldest_line(int set_id)
{
	size_t oldest_id;
	size_t oldest_timestamp = ~0;

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].age < oldest_timestamp)
		{
			oldest_id = i;
			oldest_timestamp = sets[set_id].lines[i].age;
		}
	}

	return oldest_id;
}

typedef enum CacheOpStatus { CACHE_HIT, CACHE_MISS, CACHE_MISS_EVICTION } CacheOpStatus;

CacheOpStatus do_op(uint64_t _address, uint64_t _size)
{
	int set_id, block, tag;

	address_info(&set_id, &block, &tag, _address);

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].tag == tag)
		{
			num_hits ++;
			sets[set_id].lines[i].age = (global_timestamp++);

			return CACHE_HIT;
		}
	}

	printf(" miss");
	num_misses ++;

	for(size_t i = 0;i < associativity;i ++)
	{
		if(sets[set_id].lines[i].valid_bit == false)
		{
			sets[set_id].lines[i].valid_bit = true;
			sets[set_id].lines[i].age = (global_timestamp++);
			sets[set_id].lines[i].tag = tag;

			printf("\n");

			return CACHE_MISS;
		}
	}

	int oldest_line = get_oldest_line(set_id);

	//Evict and load
	sets[set_id].lines[oldest_line].age = (global_timestamp++);
	sets[set_id].lines[oldest_line].tag = tag;
	printf(", evicted\n");
	num_evictions ++;

	return CACHE_MISS_EVICTION;
}

void load_address(uint64_t _address, uint64_t _size)
{
	printf("L %ld,%ld", _address, _size);

	CacheOpStatus result = do_op(_address, _size);

	if(result == CACHE_HIT)
	{
		printf(" hit\n");
	}
	else if(result == CACHE_MISS)
	{
		printf(" miss\n");
	}
	else if(result == CACHE_MISS_EVICTION)
	{
		printf(" miss eviction\n");
	}
}
void store_address(uint64_t _address, uint64_t _size)
{
	printf("S %ld,%ld", _address, _size);

	CacheOpStatus result = do_op(_address, _size);

	if(result == CACHE_HIT)
	{
		printf(" hit\n");
	}
	else if(result == CACHE_MISS)
	{
		printf(" miss\n");
	}
	else if(result == CACHE_MISS_EVICTION)
	{
		printf(" miss eviction\n");
	}
}

void modify_address(uint64_t _address, uint64_t _size)
{
	printf("M %ld,%ld", _address, _size);

	CacheOpStatus result1 = do_op(_address, _size);
	/*CacheOpStatus result2 = */do_op(_address, _size);

	if(result1 == CACHE_HIT)
	{
		printf(" hit hit\n");
	}
	else if(result1 == CACHE_MISS)
	{
		printf(" miss hit\n");
	}
	else if(result1 == CACHE_MISS_EVICTION)
	{
		printf(" miss eviction hit\n");
	}
}

void parse_input(char** operation, uint64_t** address, uint64_t** size, size_t* ops, char* input)
{
  int index = 0;
  int hash = 0;
  char* delimiters = " ,\n\r";
  char* token;

  char* res_op = (char*)malloc(OP_BUF_LEN*sizeof(char));
  uint64_t* res_addr = (uint64_t*)malloc(OP_BUF_LEN*sizeof(uint64_t));
  uint64_t* res_size = (uint64_t*)malloc(OP_BUF_LEN*sizeof(uint64_t));
  size_t res_ops = 0;

  token = strtok(input, delimiters);
  while(token != NULL)
    {
      hash = index%3;
      //printf("index: %d\n\r", index);

      switch(hash)
	{
	case 0:
	  //instruction character
	  res_op[res_ops] = *token;
	  //printf("instruction: %c\n\r", res_op[res_ops]);
	  break;

	case 1:
	  //address (64-bit, hex)
	  res_addr[res_ops] = (uint64_t)strtoul(token, NULL, 16);
	  //printf("address: 0x%lx\n\r", res_addr[res_ops]);
	  break;

	case 2:
	  //size in bytes, decimal
	  res_size[res_ops] = (uint64_t)strtoul(token, NULL, 10);
	  //printf("size: %d\n\r", res_size[res_ops]);
	  res_ops++;
	  break;

	default:
	  //???!!!?!?!!!
	  break;

	}
      
      index++;
      token = strtok(NULL, delimiters);

    }

  //finish up
  *operation = res_op;
  *address = res_addr;
  *size = res_size;
  *ops = res_ops;

}

void report(int mode)
{
  switch(mode)
    {
    case 0:
      printf("hit ");
      break;
    case 1:
      printf("miss ");
      break;
    case 2:
      printf("eviction ");
      break;
    default:
      printf("unknown\n\r");
      break;

    }

}

int main(int argc, char** argv)
{
  uint64_t lSize;
  FILE *fp;

  int arg_id = 1;

  enum { ARG_NONE, ARG_SETBITS, ARG_ASSOCIATIVITY, ARG_BLOCKBITS, ARG_TRACEFILE } next_arg;

  char trace_file[30] = "";

  uint64_t set_bits = 1, block_bits = 1, associativity = 1;

  while(argc > arg_id)
    {
      if(argv[arg_id][0] == '-')
	{
	  if(argv[arg_id][1] == 'v')
	    {
	      //verbose
	      verbose = true;
	      //printf("verbose!\n");
	    }
	  else if(argv[arg_id][1] == 's')
	    {
	      //int, set index bits
	      next_arg = ARG_SETBITS;
	      //printf("setbits!\n");
	    }
	  else if(argv[arg_id][1] == 'E')
	    {
	      //int, associativity
	      next_arg = ARG_ASSOCIATIVITY;
	      //printf("associativity!!\n");
	    }
	  else if(argv[arg_id][1] == 'b')
	    {
	      //int, block bits
	      next_arg = ARG_BLOCKBITS;
	      //printf("blockbits!!\n");
	    }
	  else if(argv[arg_id][1] == 't')
	    {
	      //trace file, cstring
	      next_arg = ARG_TRACEFILE;
	      //printf("tracefile!\n");
	    }
	  else if(argv[arg_id][1] == 'h')
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
		  set_bits = atoi(argv[arg_id]);
		  break;
		case ARG_ASSOCIATIVITY:
		  associativity = atoi(argv[arg_id]);
		  break;
		case ARG_BLOCKBITS:
		  block_bits = atoi(argv[arg_id]);
		  break;
		case ARG_TRACEFILE:
		  strncpy(trace_file, argv[arg_id], 30);
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

  fp = fopen(trace_file, "r");

  if(fp == NULL)
    {
      perror("failed to read file...");
      exit(1);

    }

  fseek(fp, 0L, SEEK_END);
  lSize = ftell(fp);
  rewind(fp); //be kind,

  printf("lSize: %ld\n\r", lSize);

  char* op = NULL;
  uint64_t* addr = NULL;
  uint64_t* size = NULL;
  size_t ops = 0;
  char* input = NULL;

  uint64_t inSize = 0;

  init_cache(set_bits, associativity, block_bits);

  while(lSize > 0)
    {
      inSize = (lSize > IN_BUF_LEN) ? IN_BUF_LEN : lSize;

      printf("inSize: %ld\n\r", (unsigned long)inSize);

      input = (char*)calloc(1, lSize+1);

      if(input == NULL)
	{
	  perror("failed to allocate memory for input...");
	  fclose(fp);
	  exit(1);

	}

      lSize = lSize - fread(input, 1, inSize, fp);

      printf("lSize: %ld\n\r", (unsigned long)lSize);

      parse_input(&op, &addr, &size, &ops, input);

      printf("num ops: %u\n\r", (unsigned int)ops);
      printf("first instruction: %c\n\r", op[0]);

    }

  fclose(fp);
  free(input);

  init_cache(set_bits, associativity, block_bits);

  load_address(0x00, 4);
  load_address(0x00, 4);
  load_address(0x00, 4);
  load_address(0x00, 4);

  deinit_cache();

  printSummary(num_hits, num_misses, num_evictions);

  return 0;

}
