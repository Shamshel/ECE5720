//Cody Herndon
//A01393116

//David Petrizze
//A01625825

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cachelab.h"

#define OP_BUFF_LEN 256

uint64_t block_bits = 0;
uint64_t tag_bits = 0;
uint64_t set_bits = 0;

uint64_t block_mask = 0;
uint64_t tag_mask = 0;
uint64_t set_mask = 0;

void parse_input(char** operation, uint64_t** address, uint64_t** size, size_t* ops, char* input)
{
  int index = 0;
  int hash = 0;
  char* delimiters = " ,\n\r";
  char* token;

  char* res_op = (char*)malloc(OP_BUFF_LEN*sizeof(char));
  uint64_t* res_addr = (uint64_t*)malloc(OP_BUFF_LEN*sizeof(uint64_t));
  uint64_t* res_size = (uint64_t*)malloc(OP_BUFF_LEN*sizeof(uint64_t));
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

void hit_detect(uint64_t address)
{
  

}

int main()
{
  long lSize;
  FILE *fp;
  fp = fopen("traces/yi.trace", "r");

  if(fp == NULL)
    {
      perror("failed to read file...");
      exit(1);

    }

  fseek(fp, 0L, SEEK_END);
  lSize = ftell(fp);
  rewind(fp); //be kind,

  char* op = NULL;
  uint64_t* addr = NULL;
  uint64_t* size = NULL;
  size_t ops = 0;
  char* input = NULL;

  input = (char*)calloc(1, lSize+1);

  if(input == NULL)
    {
      perror("failed to allocate memory for input...");
      exit(1);

    }

  fread(input, lSize, 1, fp);

  parse_input(&op, &addr, &size, &ops, input);

  printf("num ops: %u\n\r", (unsigned int)ops);
  printf("first instruction: %c\n\r", op[0]);

  fclose(fp);
  free(input);

  printSummary(0, 0, 0);
  return 0;

}
