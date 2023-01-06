/*
 * cache.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "cache.h"
#include "main.h"

/* cache configuration parameters */
static int cache_split;
static int cache_usize = DEFAULT_CACHE_SIZE;
static int cache_isize = DEFAULT_CACHE_SIZE; 
static int cache_dsize = DEFAULT_CACHE_SIZE;
static int cache_block_size = DEFAULT_CACHE_BLOCK_SIZE;
static int words_per_block = DEFAULT_CACHE_BLOCK_SIZE / WORD_SIZE;
static int cache_assoc = DEFAULT_CACHE_ASSOC;
static int cache_writeback = DEFAULT_CACHE_WRITEBACK;
static int cache_writealloc = DEFAULT_CACHE_WRITEALLOC;

/* cache model data structures */
static Pcache icache;
static Pcache dcache;
static cache c1;
static cache c2;
static cache_stat cache_stat_inst;
static cache_stat cache_stat_data;

/************************************************************/
void set_cache_param(param, value)
  int param;
  int value;
{
	// 确定是否分data cache, inst cahce
  cache_split = 1;
  switch (param) {
  case CACHE_PARAM_BLOCK_SIZE:
    cache_block_size = value;
    words_per_block = value / WORD_SIZE;
    break;
  case CACHE_PARAM_USIZE:
    cache_split = FALSE;
    cache_usize = value;
    break;
  case CACHE_PARAM_ISIZE:
    cache_split = TRUE;
    cache_isize = value;
    break;
  case CACHE_PARAM_DSIZE:
    cache_split = TRUE;
    cache_dsize = value;
    break;
  case CACHE_PARAM_ASSOC:
    cache_assoc = value;
    break;
  case CACHE_PARAM_WRITEBACK:
    cache_writeback = TRUE;
    break;
  case CACHE_PARAM_WRITETHROUGH:
    cache_writeback = FALSE;
    break;
  case CACHE_PARAM_WRITEALLOC:
    cache_writealloc = TRUE;
    break;
  case CACHE_PARAM_NOWRITEALLOC:
    cache_writealloc = FALSE;
    break;
  default:
    printf("error set_cache_param: bad parameter value\n");
    exit(-1);
  }

}
/************************************************************/

/************************************************************/
void init_cache()
{
  /* initialize the cache, and cache statistics data structures */
  // direct mapped cache
  // 结构体内的参数初始化
  if (cache_split==1){
  	c1.size = cache_dsize;
  	c1.associativity = cache_assoc;
  	c1.n_sets = cache_dsize/(cache_block_size*cache_assoc);
	c1.index_mask_offset = LOG2(cache_block_size);
	c1.index_mask = (((1<<(LOG2(c1.n_sets)))-1)<<(LOG2(cache_block_size)));
  	c1.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
	c1.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
	c1.set_contents = (int *)malloc(sizeof(int)*c1.n_sets);

	for (int i=0;i<c1.n_sets;i++){
		c1.LRU_head[i] = NULL;
		c1.LRU_tail[i] = NULL;
		c1.set_contents[i] = 0;
	}

	c2.size = cache_isize;
  	c2.associativity = cache_assoc;
  	c2.n_sets = cache_isize/(cache_block_size*cache_assoc);
	c2.index_mask_offset = LOG2(cache_block_size);
	c2.index_mask = (((1<<(LOG2(c2.n_sets)))-1)<<(LOG2(cache_block_size)));
  	c2.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
	c2.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
	c2.set_contents = (int *)malloc(sizeof(int)*c2.n_sets);

	for (int i=0;i<c2.n_sets;i++){
		c2.LRU_head[i] = NULL;
		c2.LRU_tail[i] = NULL;
		c2.set_contents[i] = 0;
	}

  }
  else{
  	c1.size = cache_usize;
  	c1.associativity = cache_assoc;
  	c1.n_sets = cache_usize/(cache_block_size*cache_assoc);
	c1.index_mask_offset = LOG2(cache_block_size);
	c1.index_mask = (((1<<(LOG2(c1.n_sets)))-1)<<(LOG2(cache_block_size)));
  	c1.LRU_head = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
	c1.LRU_tail = (Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
	c1.set_contents = (int *)malloc(sizeof(int)*c1.n_sets);

	for (int i=0;i<c1.n_sets;i++){
		c1.LRU_head[i] = NULL;
		c1.LRU_tail[i] = NULL;
		c1.set_contents[i] = 0;
	}
  }
  
  cache_stat_data.accesses=0;
  cache_stat_data.misses=0;
  cache_stat_data.replacements=0;
  cache_stat_data.demand_fetches=0;
  cache_stat_data.copies_back=0;
  
  cache_stat_inst.accesses=0;
  cache_stat_inst.misses=0;
  cache_stat_inst.replacements=0;
  cache_stat_inst.demand_fetches=0;
  cache_stat_inst.copies_back=0;
  printf("finish init.\n");
}
/************************************************************/

void data_load_reference(Pcache c, unsigned tag, unsigned index){
	// NULL cache line
 
	cache_stat_data.accesses++;
	// 找寻cache是否有一致的tag
	// 使用LRU_tmp遍历LRU_head[index]是否存在tag一致
	Pcache_line LRU_tmp;
	LRU_tmp = c->LRU_head[index];
	int flag=0;
	while (1){
		if (LRU_tmp==NULL)
			break;

		if (LRU_tmp->tag==tag){
			flag=1;
			break;
		}
		if (LRU_tmp->LRU_next==NULL){
			break;
		}
		if (c->associativity==1)
			break;
		LRU_tmp = LRU_tmp->LRU_next;
	}
	if (flag==0){ // cache miss
		cache_stat_data.misses++;
		int* contents = &(c->set_contents[index]);
		// demand_fetch
		// 从内存中申请一段空间
		cache_stat_data.demand_fetches += cache_block_size/WORD_SIZE;
		Pcache_line data_from_ram = (Pcache_line)malloc(sizeof(Pcache_line));
		data_from_ram->LRU_next = NULL;
		data_from_ram->LRU_prev = NULL;
		data_from_ram->tag = tag;
		data_from_ram->dirty = 0;
		
		if ((*contents)==c->associativity){ // 若已满,则需要删除最近没使用的数据
			// replacement		
			cache_stat_data.replacements++;
				
			// check dirty bit of c->LRU_tail[index]
			// 如果数据之前被修改过且使用writeback策略
			// 需要把这段数据烤回内存
			if (c->LRU_tail[index]->dirty==1 && cache_writeback)
				cache_stat_data.copies_back += cache_block_size/WORD_SIZE;

			delete(&c->LRU_head[index],&c->LRU_tail[index],c->LRU_tail[index]);
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
		}
		else{
			// insert
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
			(*contents)++;
		}
	}else{
		// change the order
		delete(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);
		insert(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);
	}
}

void data_store_reference(Pcache c, unsigned tag, unsigned index){

	cache_stat_data.accesses++;
	Pcache_line LRU_tmp;
	LRU_tmp = c->LRU_head[index];
	int flag=0;
	while (1){
		if (LRU_tmp==NULL)
			break;

		if (LRU_tmp->tag==tag){
			flag=1;
			break;
		}
		if (LRU_tmp->LRU_next==NULL){
			break;
		}
		if (c->associativity==1)
			break;
		LRU_tmp = LRU_tmp->LRU_next;
	}
	if (flag==1){ // cache hit
		//LRU_tmp->dirty=1;
		// 如果cache hit,且策略为writeback则需要修改此处数据,dirty置1
		// 若策略为write through，则直接将修改的内容写进主存
		if (cache_writeback)
			LRU_tmp->dirty=1;
		else
			cache_stat_data.copies_back += 1;
		
		delete(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);
		insert(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);

	}else{  // cache miss
		cache_stat_data.misses++;
		int* contents = &(c->set_contents[index]);
		
		// demand_fetch
		// 若writealloc，则需要从内存中拷一段空间到cache
	
		if (cache_writealloc)
			cache_stat_data.demand_fetches += cache_block_size/WORD_SIZE;
		
		Pcache_line data_from_ram = (Pcache_line)malloc(sizeof(Pcache_line));
		data_from_ram->tag = tag;
		data_from_ram->dirty = 0;
		data_from_ram->LRU_next = NULL;
		data_from_ram->LRU_prev = NULL;

		if ((*contents)==c->associativity && cache_writealloc){
			
			// replacement		
			cache_stat_data.replacements++;
			
			if (cache_writeback) 
				data_from_ram->dirty = 1;
			else // write through
				cache_stat_data.copies_back += 1;
			
			// 判断被替换的数据之前是否被修改过
			if (c->LRU_tail[index]->dirty==1 && cache_writeback)
				cache_stat_data.copies_back += cache_block_size/WORD_SIZE;
		
			delete(&c->LRU_head[index],&c->LRU_tail[index],c->LRU_tail[index]);
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
		}else if (cache_writealloc){
			// not full and write alloc 
			// insert
			if (cache_writeback)
				data_from_ram->dirty = 1;
			else
				cache_stat_data.copies_back += 1;
			// delete(&c->LRU_head[index],&c->LRU_tail[index],c->LRU_tail[index]);
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
			(*contents)++;
		}
		else if (!cache_writealloc){ 	// 若write no alloc，则可以直接将内容写进主存
		 	cache_stat_data.copies_back += 1;
		}
	}	

}

void inst_load_reference(Pcache c, unsigned tag, unsigned index){	
	// NULL cache line 
	
	// printf("inst_load_reference."); 
	cache_stat_inst.accesses++;
	Pcache_line LRU_tmp;
	LRU_tmp = c->LRU_head[index];
	int flag=0;
	while (1){
		if (LRU_tmp==NULL){
			// printf("inst LRU_tmp.\n");
			break;
		}
			
		if (LRU_tmp->tag==tag){
			flag=1;
			// printf("cache hit.\n");
			break;
		}
		if (LRU_tmp->LRU_next==NULL){
		//	printf("LRU_tmp->LRU_next==NULL.\n");
			break;
		}
		LRU_tmp = LRU_tmp->LRU_next;
		if (c->associativity==1)
			break;
	}
	if (flag==0){ // cache miss
		cache_stat_inst.misses++;
		int* contents = &(c->set_contents[index]);
		
		// demand_fetch
		cache_stat_inst.demand_fetches += cache_block_size/WORD_SIZE;
		Pcache_line data_from_ram = (Pcache_line)malloc(sizeof(Pcache_line));
		data_from_ram->tag = tag;
		data_from_ram->dirty = 0;
		data_from_ram->LRU_next = NULL;
		data_from_ram->LRU_prev = NULL;

		if ((*contents)==c->associativity){
			// replacement		
			cache_stat_inst.replacements++;
						
			if (c->LRU_tail[index]->dirty==1 && cache_writeback)
				cache_stat_inst.copies_back += cache_block_size/WORD_SIZE;

			delete(&c->LRU_head[index],&c->LRU_tail[index],c->LRU_tail[index]);
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
			
		}
		else{
			// insert
			// delete(&c->LRU_head[index],&c->LRU_tail[index],c->LRU_tail[index]);
			insert(&c->LRU_head[index],&c->LRU_tail[index],data_from_ram);
			(*contents)++;
		}
	}else{
		// change the order
		delete(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);
		insert(&c->LRU_head[index],&c->LRU_tail[index],LRU_tmp);
	}
	
}

/************************************************************/
void perform_access(addr, access_type)
	unsigned addr, access_type;
{
  /* handle an access to the cache */

  // 计算data cache的index和inst cache的index
  unsigned tag_data,tag_inst,index_data,index_inst;
  index_data = (addr&c1.index_mask)>>c1.index_mask_offset;
  index_inst = (addr&c2.index_mask)>>c2.index_mask_offset;

  // 计算data cache和index cache的tag
  unsigned tag_mask_offset = LOG2(cache_block_size)+LOG2(c1.n_sets);
  unsigned tag_mask = ~((1<<tag_mask_offset)-1);
  tag_data = (addr&tag_mask)>>tag_mask_offset;
  
  tag_mask_offset = LOG2(cache_block_size)+LOG2(c2.n_sets);
  tag_mask = ~((1<<tag_mask_offset)-1);
  tag_inst = (addr&tag_mask)>>tag_mask_offset;
  
  // 根据不同的access_type调用不同的函数
  // 若不缺分data/inst cache时,inst_load_reference也是用c1结构体
  // 若区分,则data使用c1结构体,inst使用c2结构体
  	if (access_type==0) 
		data_load_reference(&c1, tag_data, index_data);
	else if (access_type==1) 
		data_store_reference(&c1, tag_data, index_data);
  	else if (access_type==2 && cache_split==1){ 
		inst_load_reference(&c2, tag_inst, index_inst);
	}else if (access_type==2 && cache_split==0){
		inst_load_reference(&c1, tag_data, index_data);
	}

}
/************************************************************/

/************************************************************/
void flush()
{

  /* flush the cache */
  // 将c1结构体中dirty位为1的全部清零
  Pcache_line tmp;
  for (int i=0;i<c1.n_sets;i++){
  	tmp = c1.LRU_head[i];
	if (tmp==NULL)
		continue;

  	for (int j=0;j<c1.set_contents[i];j++){
		if (tmp->dirty==1){
			cache_stat_data.copies_back += cache_block_size/WORD_SIZE;
			// printf("fuck the dirty");
		}
		tmp=tmp->LRU_next;	
	}	
  }
  /*
  if (cache_split){
 	for (int i=0;i<c2.n_sets;i++){
  		tmp = c2.LRU_head[i];
		if (tmp==NULL)
			continue;

  		for (int j=0;j<c2.set_contents[i];j++){
			if (tmp->dirty==1)
				cache_stat_inst.copies_back += cache_block_size/WORD_SIZE;
			tmp=tmp->LRU_next;	
		}
	}	
  }*/
}
/************************************************************/

/************************************************************/
void delete(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  if (item->LRU_prev) {
    item->LRU_prev->LRU_next = item->LRU_next;
  } else {
    /* item at head */
    *head = item->LRU_next;
  }

  if (item->LRU_next) {
    item->LRU_next->LRU_prev = item->LRU_prev;
  } else {
    /* item at tail */
    *tail = item->LRU_prev;
  }
}
/************************************************************/

/************************************************************/
/* inserts at the head of the list */
void insert(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  item->LRU_next = *head;
  item->LRU_prev = (Pcache_line)NULL;

  if (item->LRU_next)
    item->LRU_next->LRU_prev = item;
  else
    *tail = item;

  *head = item;
}
/************************************************************/

/************************************************************/
void dump_settings()
{
  printf("*** CACHE SETTINGS ***\n");
  if (cache_split) {
    printf("  Split I- D-cache\n");
    printf("  I-cache size: \t%d\n", cache_isize);
    printf("  D-cache size: \t%d\n", cache_dsize);
  } else {
    printf("  Unified I- D-cache\n");
    printf("  Size: \t%d\n", cache_usize);
  }
  printf("  Associativity: \t%d\n", cache_assoc);
  printf("  Block size: \t%d\n", cache_block_size);
  printf("  Write policy: \t%s\n", 
	 cache_writeback ? "WRITE BACK" : "WRITE THROUGH");
  printf("  Allocation policy: \t%s\n",
	 cache_writealloc ? "WRITE ALLOCATE" : "WRITE NO ALLOCATE");
}
/************************************************************/

/************************************************************/
void print_stats()
{
  printf("\n*** CACHE STATISTICS ***\n");

  printf(" INSTRUCTIONS\n");
  printf("  accesses:  %d\n", cache_stat_inst.accesses);
  printf("  misses:    %d\n", cache_stat_inst.misses);
  if (!cache_stat_inst.accesses)
    printf("  miss rate: 0 (0)\n"); 
  else
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses,
	 1.0 - (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses);
  printf("  replace:   %d\n", cache_stat_inst.replacements);

  printf(" DATA\n");
  printf("  accesses:  %d\n", cache_stat_data.accesses);
  printf("  misses:    %d\n", cache_stat_data.misses);
  if (!cache_stat_data.accesses)
    printf("  miss rate: 0 (0)\n"); 
  else
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_data.misses / (float)cache_stat_data.accesses,
	 1.0 - (float)cache_stat_data.misses / (float)cache_stat_data.accesses);
  printf("  replace:   %d\n", cache_stat_data.replacements);

  printf(" TRAFFIC (in words)\n");
  printf("  demand fetch:  %d\n", cache_stat_inst.demand_fetches + 
	 cache_stat_data.demand_fetches);
  printf("  copies back:   %d\n", cache_stat_inst.copies_back +
	 cache_stat_data.copies_back);
}
/************************************************************/
