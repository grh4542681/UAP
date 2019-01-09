#include "rlist.h"


/**
 * ͨ��������ָ���ȡ����ָ��
 * @param data [������ָ��]
 * @param list [����ָ��]
 */
void RList_entry_by_date(void** data,RList** list)
{
	DList* dlist=DList_entry(data,typeof(*dlist),data);
	*list=&(dlist->list);
}

/**
 * ͨ������ָ���ȡ������ָ��
 * @param list [����ָ��]
 * @param data [������ָ��]
 */
void RData_entry_by_list(RList* list,void** data)
{
	DList* dlist=DList_entry(list,typeof(*dlist),list);
	*data=dlist->data;
}

/**
 * �������ڵ�
 * @param new  [������ڵ�]
 * @param prev [����λ������ڵ�ǰָ��]
 * @param next [����λ������ڵ��ָ��]
 */
void __Rlist_add(struct RList *new,struct RList *prev,struct RList *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * ɾ������ڵ�
 * @param prev [ɾ���ڵ�����ڵ�ǰָ��]
 * @param next [ɾ���ڵ�����ڵ��ָ��]
 */
void __Rlist_del(struct RList * prev, struct RList * next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * ��ʼ������ڵ�
 * @param list [����ڵ�ָ��]
 */
void INIT_LIST_HEAD(struct RList *list)
{
	list->next = list;
	list->prev = list;
}

/**
 * ͨ�����ݽڵ㴴����������ڵ��Ԫ�ڵ�
 * @param Dlist [Ԫ�ڵ�ָ���ַ]
 * @param data  [���ݽڵ�ָ��]
 */
void Build_Dlist(DList** Dlist,void* data)
{
	DList* dlist = (DList*)malloc(sizeof(DList));
	memset(dlist, 0,sizeof(DList));
	INIT_LIST_HEAD(&(dlist->list));

	dlist->data = malloc(sizeof(*data));
	memcpy(dlist->data, data,sizeof(*data));

	*Dlist=dlist;
}

/**
 * ��֪���ݽڵ㣬��ǰλ��ǰ��������
 * @param head [��ǰλ������ڵ�ָ��]
 * @param data [���ݽڵ�ָ��]
 */
void RList_add_head(struct RList* head,void* data)
{
	DList* dlist = (DList*)malloc(sizeof(DList));
	memset(dlist, 0,sizeof(DList));
	INIT_LIST_HEAD(&(dlist->list));

	dlist->data = malloc(sizeof(*data));
	memcpy(dlist->data, data,sizeof(*data));

	__Rlist_add(&(dlist->list),head,head->next);
}

/**
 * ��֪���ݽڵ㣬��ǰλ�ú��������
 * @param head [��ǰλ������ڵ�ָ��]
 * @param data [���ݽڵ�ָ��]
 */
void RList_add_tail(struct RList* head,void* data)
{
	DList* dlist = (DList*)malloc(sizeof(DList));
	memset(dlist, 0,sizeof(DList));

	dlist->data = malloc(sizeof(*data));
	memcpy(dlist->data, data,sizeof(*data));

	__Rlist_add(&(dlist->list),head->prev,head);
}

/**
 * ɾ������ڵ㣬���ͷ�����Ԫ�ڵ�
 * @param head [ɾ������ڵ�ָ��]
 */
void RList_del(struct RList* head)
{
	__Rlist_del(head->prev,head->next);

	DList* entry=DList_entry(head,typeof(*entry),list);
	free(entry->data);
	free(entry);
}

/**
 * �滻�ɽڵ㣬���ɽڵ㲻�ͷ�
 * @param old [������ڵ�ָ��]
 * @param new [������ڵ�ָ��]
 */
void Rlist_replace(struct RList *old,struct RList *new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
	INIT_LIST_HEAD(old);
}

/**
 * �滻�ɽڵ㣬�ɽڵ��ͷ�
 * @param old [������ڵ�ָ��]
 * @param new [������ڵ�ָ��]
 */
void Rlist_replace_del(struct RList *old,struct RList *new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;

	INIT_LIST_HEAD(old);
	RList_del(old);
}

/**
 * �ƶ��ڵ㵽Ŀ��ڵ�ǰ
 * @param list [�ƶ�����ڵ�ָ��]
 * @param head [Ŀ��λ�ýڵ�ָ��]
 */
void Rlist_move_head(struct RList *list, struct RList *head)
{
	__Rlist_del(list->prev,list->next);
	__Rlist_add(list,head,head->next);
}

/**
 * �ƶ��ڵ㵽Ŀ��ڵ��
 * @param list [�ƶ�����ڵ�ָ��]
 * @param head [Ŀ��λ�ýڵ�ָ��]
 */
void Rlist_move_tail(struct RList *list,struct RList *head)
{
	__Rlist_del(list->prev,list->next);
	__Rlist_add(list,head->prev,head);
}

/**
 * Ŀ��ڵ��Ƿ�Ϊ���һ���ڵ�
 * @param  list [Ŀ������ڵ�ָ��]
 * @param  head [����ͷ�ڵ�ָ��]
 * @return      [true or false]
 */
int Rlist_is_last(const struct RList *list,const struct RList *head)
{
	return list->next == head;
}

/**
 * �����Ƿ�Ϊ��
 * @param  head [����ͷ�ڵ�ָ��]
 * @return      [true or false]
 */
int Rlist_empty(const struct RList *head)
{
	struct RList *next = head->next;
	return (next == head) && (next == head->prev);
}

/**
 * �ϲ�����
 * @param list [����1�ϲ�λ������ڵ�ָ��]
 * @param prev [����2�ϲ�λ������ڵ�ǰָ��]
 * @param next [����2�ϲ�λ������ڵ��ָ��]
 */
void __Rlist_splice(const struct RList *list,struct RList *prev,struct RList *next)
{
	struct RList *first = list->next;
	struct RList *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

/**
 * �ϲ�����Ŀ��ڵ�ǰ
 * @param list [����1�ϲ�λ������ڵ�ָ��]
 * @param head [����2�ϲ�λ������ڵ�ָ��]
 */
void Rlist_splice_head(struct RList *list,struct RList *head)
{
	if (!Rlist_empty(list))
	{
		__Rlist_splice(list, head, head->next);
		INIT_LIST_HEAD(list);
	}
}

/**
 * �ϲ�����Ŀ��ڵ��
 * @param list [����1�ϲ�λ������ڵ�ָ��]
 * @param head [����2�ϲ�λ������ڵ�ָ��]
 */
void Rlist_splice_tail(struct RList *list,struct RList *head)
{
	if (!Rlist_empty(list))
	{
		__Rlist_splice(list, head->prev, head);
		INIT_LIST_HEAD(list);
	}
}
