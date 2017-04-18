/*!
  \file autofree_alloc.c
  \brief


  creation date : 2014/06/02 18:36:18 (KST)

*/
#include <stdio.h>
#include <string.h>

#include <llist.h>

struct autofree_list_rec 
{
	struct list_head list;
};

static LIST_HEAD(autofree_list);


void * autofree_alloc(unsigned int size)
{
	struct autofree_list_rec *entry;

	entry = (struct autofree_list_rec *)malloc( size + sizeof(struct autofree_list_rec) );
	if ( entry )
	{
		list_add( &(entry->list), &autofree_list);
		return (void*)(entry + sizeof(struct autofree_list_rec));
	}
	return NULL;
}

void * autofree_calloc(unsigned int nmemb, unsigned int size)
{
	void *addr;

	addr = autofree_alloc( nmemb * size);
	if ( addr ) 
	{
		memset(addr, nmemb * size, 0);
	}
	return addr;
}

void autofree_free(void)
{
	struct list_head *p;
	struct autofree_list_rec *entry = NULL;

	list_for_each( p, &autofree_list)
	{
		if ( entry ) 
			free(entry);

		entry = list_entry(p, struct autofree_list_rec, list);
	}
	if ( entry ) 
		free(entry);
	
	INIT_LIST_HEAD(&autofree_list);
}

void autofree_dump(void)
{
	struct list_head *p;
	struct autofree_list_rec *entry = NULL;
	int i = 0;

	list_for_each( p, &autofree_list)
	{
		entry = list_entry(p, struct autofree_list_rec, list);
		printf("[%d] %p\n", i++, entry);
	}
}


int main(void)
{
	char *str;
	unsigned int i = 0;

	while(1)
	{

		str = autofree_alloc(128*1024);
		if ( str ) {
			snprintf(str, 128, "#%d string", i++);
			printf("autofree test [%s]\n", str);

		}

		if ( i % 100000 == 0 ) 
		{
			autofree_dump();
			autofree_free();
		}
	}


}

/********** end of file **********/
