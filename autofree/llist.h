/*!
 * \file list.h
 * \brief
 *
 * list (from linux kernel 2.4.x source)
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수  5월 10 10:20:01 KST 2006
 *
*/

#ifndef _LINUX_LIST_H_
#define _LINUX_LIST_H_


// define INLINE 
// if your compiler support inline function, define it INLINE.
#ifndef INLINE

#ifdef _SDT25_
#define INLINE __inline // for arm STD 2.5
#else
#define INLINE inline
#endif

#endif // INLINE

// define NULL
#ifndef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif


// define NULL
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


// define container_of
#ifndef container_of

#ifdef _SDT25_
// for arm STD 2.5 by saibi
#define container_of(ptr, type, member) \
	(type *)( (size_t)ptr - offsetof(type, member))

#else

// org linux implementation
#define container_of(ptr, type, member) ({	\
	const typeof( ((type *)0)->member ) *__mptr = (ptr); \
	(type *)( (char *)__mptr - offsetof(type,member) ) ;})
#endif

#endif // container_of



/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static INLINE void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static INLINE void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static INLINE void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static INLINE void __list_add_rcu(struct list_head * new,
	struct list_head * prev,
	struct list_head * next)
{
	new->next = next;
	new->prev = prev;
	next->prev = new;
	prev->next = new;
}

/**
 * list_add_rcu - add a new entry to rcu-protected list
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static INLINE void list_add_rcu(struct list_head *new, struct list_head *head)
{
	__list_add_rcu(new, head, head->next);
}

/**
 * list_add_tail_rcu - add a new entry to rcu-protected list
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static INLINE void list_add_tail_rcu(struct list_head *new, struct list_head *head)
{
	__list_add_rcu(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static INLINE void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is
 * in an undefined state.
 */
static INLINE void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = (struct list_head *)LIST_POISON1;
	entry->prev = (struct list_head *)LIST_POISON2;
}

/**
 * list_del_rcu - deletes entry from list without re-initialization
 * @entry: the element to delete from the list.
 *
 * Note: list_empty on entry does not return true after this, 
 * the entry is in an undefined state. It is useful for RCU based
 * lockfree traversal.
 *
 * In particular, it means that we can not poison the forward 
 * pointers that may still be used for walking the list.
 */
static INLINE void list_del_rcu(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = (struct list_head *)LIST_POISON2;
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static INLINE void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry); 
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static INLINE void list_move(struct list_head *list, struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static INLINE void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add_tail(list, head);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static INLINE int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/**
 * list_empty_careful - tests whether a list is
 * empty _and_ checks that no other CPU might be
 * in the process of still modifying either member
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 *
 * @head: the list to test.
 */
static INLINE int list_empty_careful(const struct list_head *head)
{
	struct list_head *next = head->next;
	return (next == head) && (next == head->prev);
}

static INLINE void __list_splice(struct list_head *list,
				 struct list_head *head)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;
	struct list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

/**
 * list_splice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static INLINE void list_splice(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static INLINE void list_splice_init(struct list_head *list,
				    struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)

/**
 * __list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 *
 * This variant differs from list_for_each() in that it's the
 * simplest possible list iteration code, no prefetching is done.
 * Use this for code that knows the list to be very short (empty
 * or 1 entry) most of the time.
 */
#define __list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); \
        	pos = pos->prev )
        	


// added by kimyoungmin
/// 리스트 갯수를 얻음
static INLINE int list_count(struct list_head *head) 
{
	struct list_head *p;
	int count = 0;

	list_for_each(p, head) {
		count++;
	}
	return count;
}

/// 리스트 앞으로 이동
/// \param head
/// \param count count >= 1
static INLINE struct list_head * list_forward(struct list_head *head, int count)
{
	struct list_head *p;
	int i = 0;

	list_for_each(p, head) {
		++i;
		if ( i == count ) {
			return p;
		}
	}
	return NULL;
}

/// 리스트 뒤로 이동
/// \param head
/// \param count
static INLINE struct list_head * list_backward(struct list_head *head, int count)
{
	struct list_head *p;
	int i = 0;

	list_for_each_prev(p, head) {
		++i;
		if ( i == count ) {
			return p;
		}
	}
	return NULL;
}


/// 리스트내 위치를 얻음
/// \param head
/// \param elm
static INLINE int list_pos(struct list_head *head, struct list_head * elm)
{
	struct list_head *p;
	int i = 0;

	list_for_each(p, head) {
		++i;
		if ( p == elm ) {
			return i;
		}
	}
	return -1;
}

/// 리스트내 위치를 얻음 (마지막 element 사용자 지정 가능) 
/// \param head
/// \param end_p 
/// \param elm
static INLINE int list_pos_e(struct list_head *head, struct list_head * end_p, struct list_head * elm)
{
	struct list_head *p;
	int i = 0;

	list_for_each(p, head) {
		++i;
		if ( p == elm ) {
			return i;
		}
		if ( p == end_p ) {
			break;
		}
	}
	return -1;
}


/**
 * list_for_each_safe	-	iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop counter.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member); \
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_entry((head)->prev, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.prev, typeof(*pos), member))

/**
 * list_prepare_entry - prepare a pos entry for use as a start point in
 *			list_for_each_entry_continue
 * @pos:	the type * to use as a start point
 * @head:	the head of the list
 * @member:	the name of the list_struct within the struct.
 */
#define list_prepare_entry(pos, head, member) \
	((pos) ? : list_entry(head, typeof(*pos), member))

/**
 * list_for_each_entry_continue -	iterate over list of given type
 *			continuing after existing point
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_continue(pos, head, member) 		\
	for (pos = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_for_each_rcu	-	iterate over an rcu-protected list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each_rcu(pos, head) \
	for (pos = (head)->next ; pos != (head); \
        	pos = pos->next, ({ smp_read_barrier_depends(); 0;}) )
        	
#define __list_for_each_rcu(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next, ({ smp_read_barrier_depends(); 0;}))
        	
/**
 * list_for_each_safe_rcu	-	iterate over an rcu-protected list safe
 *					against removal of list entry
 * @pos:	the &struct list_head to use as a loop counter.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe_rcu(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, ({ smp_read_barrier_depends(); 0;}), n = pos->next)

/**
 * list_for_each_entry_rcu	-	iterate over rcu list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_rcu(pos, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member),	\
		     ({ smp_read_barrier_depends(); 0;}))


/**
 * list_for_each_continue_rcu	-	iterate over an rcu-protected list 
 *			continuing after existing point.
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each_continue_rcu(pos, head) \
	for ((pos) = (pos)->next ; (pos) != (head); \
        	(pos) = (pos)->next, ({ smp_read_barrier_depends(); 0;}))

/* 
 * Double linked lists with a single pointer list head. 
 * Mostly useful for hash tables where the two pointer list head is 
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */ 

struct hlist_head { 
	struct hlist_node *first; 
}; 

struct hlist_node { 
	struct hlist_node *next, **pprev; 
}; 

#define HLIST_HEAD_INIT { .first = NULL } 
#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL) 
#define INIT_HLIST_NODE(ptr) ((ptr)->next = NULL, (ptr)->pprev = NULL)

static INLINE int hlist_unhashed(const struct hlist_node *h) 
{ 
	return !h->pprev;
} 

static INLINE int hlist_empty(const struct hlist_head *h) 
{ 
	return !h->first;
} 

static INLINE void __hlist_del(struct hlist_node *n) 
{
	struct hlist_node *next = n->next;
	struct hlist_node **pprev = n->pprev;
	*pprev = next;  
	if (next) 
		next->pprev = pprev;
}  

static INLINE void hlist_del(struct hlist_node *n)
{
	__hlist_del(n);
	n->next = (struct hlist_node *)LIST_POISON1;
	n->pprev = (struct hlist_node **)LIST_POISON2;
}

/**
 * hlist_del_rcu - deletes entry from hash list without re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: list_unhashed() on entry does not return true after this, 
 * the entry is in an undefined state. It is useful for RCU based
 * lockfree traversal.
 *
 * In particular, it means that we can not poison the forward
 * pointers that may still be used for walking the hash list.
 */
static INLINE void hlist_del_rcu(struct hlist_node *n)
{
	__hlist_del(n);
	n->pprev = (struct hlist_node **)LIST_POISON2;
}

static INLINE void hlist_del_init(struct hlist_node *n) 
{
	if (n->pprev)  {
		__hlist_del(n);
		INIT_HLIST_NODE(n);
	}
}  

#define hlist_del_rcu_init hlist_del_init

static INLINE void hlist_add_head(struct hlist_node *n, struct hlist_head *h) 
{ 
	struct hlist_node *first = h->first;
	n->next = first; 
	if (first) 
		first->pprev = &n->next;
	h->first = n; 
	n->pprev = &h->first; 
} 

static INLINE void hlist_add_head_rcu(struct hlist_node *n, struct hlist_head *h) 
{ 
	struct hlist_node *first = h->first;
	n->next = first;
	n->pprev = &h->first; 
	if (first) 
		first->pprev = &n->next;
	h->first = n; 
} 

/* next must be != NULL */
static INLINE void hlist_add_before(struct hlist_node *n, struct hlist_node *next)
{
	n->pprev = next->pprev;
	n->next = next; 
	next->pprev = &n->next; 
	*(n->pprev) = n;
}

static INLINE void hlist_add_after(struct hlist_node *n,
				       struct hlist_node *next)
{
	next->next	= n->next;
	*(next->pprev)	= n;
	n->next		= next;
}

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

/* Cannot easily do prefetch unfortunately */
#define hlist_for_each(pos, head) \
	for (pos = (head)->first; pos && ({ 1; }); \
	     pos = pos->next) 

#define hlist_for_each_safe(pos, n, head) \
	for (pos = (head)->first; n = pos ? pos->next : 0, pos; \
	     pos = n)

/**
 * hlist_for_each_entry	- iterate over list of given type
 * @tpos:	the type * to use as a loop counter.
 * @pos:	the &struct hlist_node to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry(tpos, pos, head, member)			 \
	for (pos = (head)->first;					 \
	     pos && ({ 1;}) &&			 \
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * hlist_for_each_entry_continue - iterate over a hlist continuing after existing point
 * @tpos:	the type * to use as a loop counter.
 * @pos:	the &struct hlist_node to use as a loop counter.
 * @member:	the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_continue(tpos, pos, member)		 \
	for (pos = (pos)->next;						 \
	     pos && ({ 1;}) &&			 \
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * hlist_for_each_entry_from - iterate over a hlist continuing from existing point
 * @tpos:	the type * to use as a loop counter.
 * @pos:	the &struct hlist_node to use as a loop counter.
 * @member:	the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_from(tpos, pos, member)			 \
	for (; pos && ({ 1;}) &&			 \
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * hlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @tpos:	the type * to use as a loop counter.
 * @pos:	the &struct hlist_node to use as a loop counter.
 * @n:		another &struct hlist_node to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_safe(tpos, pos, n, head, member) 		 \
	for (pos = (head)->first;					 \
	     pos && ({ n = pos->next; 1; }) && 				 \
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = n)



#endif
/********** end of file **********/
