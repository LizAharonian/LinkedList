/******************************************
* Student name: Liz Aharonian
* Course Exercise Group: 01
* Exercise name: ex6
******************************************/

#include "GADT.h"

//SLN struct
typedef struct SLN_S
{
    ELM val;
    struct SLN_S * next;
    void(*cpy_elm) (ELM, ELM);
    int(*cmp_elm)(ELM, ELM);
    void(*free_elm) (ELM);
    ELM(*create_elm)();
    void(*print_elm)(ELM);
    ELM(*add_elm_to_elm)(ELM, ELM);
} SLN_T;
/*

* function name: SLCreate
* The Input: ELM head_val, ELM(*create_elm)(), void(*cpy_elm)(ELM, ELM),
	int(*cmp_elm)(ELM, ELM), void(*free_elm)(ELM),
	void(*print_elm)(ELM), ELM(*add_elm_to_elm)(ELM, ELM)
* The output: return head of SLN
* The Function operation: create headNode of SLN.

*/
HEAD SLCreate(ELM head_val, ELM(*create_elm)(), void(*cpy_elm)(ELM, ELM),
              int(*cmp_elm)(ELM, ELM), void(*free_elm)(ELM),
              void(*print_elm)(ELM), ELM(*add_elm_to_elm)(ELM, ELM))
{
    //allocate memory for head element
    SLN_T *head = (SLN_T*)malloc(sizeof(struct SLN_S));
    if (NULL != head)
    {
        //allocate memory for head value
        head->val = (ELM)create_elm();
        if (head->val!=NULL)
        {
            //copy point/string to head->val field
            cpy_elm(head->val, head_val);
            head->next = NULL;
            head->cpy_elm = cpy_elm;
            head->cmp_elm = cmp_elm;
            head->free_elm = free_elm;
            head->print_elm = print_elm;
            head->add_elm_to_elm = add_elm_to_elm;
            head->create_elm = create_elm;
        }
    }
    return head;
}
/*

* function name: SLAddListElement
* The Input: HEAD* head, ELM node
* The output: return RESUSLT ENUM
* The Function operation: create newNode of SLN.

*/
RESULT SLAddListElement(HEAD* head, ELM node)
{
    //create new entry
    SLN_T *new_entry = (SLN_T *)malloc(sizeof(SLN_T));
    //check if memory allocation was failed
    if (NULL == new_entry)
    {
        return outOfMem;
    }
    //casting of head
    SLN_T* headNode = ((SLN_T*)*head);
    SLN_T *prev = NULL;
    //copy the relevant functions from head
    new_entry->cpy_elm = headNode->cpy_elm;
    new_entry->cmp_elm = headNode->cmp_elm;
    new_entry->free_elm = headNode->free_elm;
    new_entry->print_elm = headNode->print_elm;
    new_entry->add_elm_to_elm = headNode->add_elm_to_elm;
    new_entry->create_elm = headNode->create_elm;
    //allocate memory for new val of new entery
    new_entry->val = new_entry->create_elm();
    //check if memory allocation was failed
    if (new_entry->val==NULL)
    {
        return outOfMem;
    }
    //copy node to val field
    new_entry->cpy_elm(new_entry->val, node);
    //new element is lower than head val
    if (new_entry->cmp_elm(new_entry->val, headNode->val) < 0)
    {
        //make new element to be the new head
        new_entry->next = *head;
        *head = new_entry;
        return success;
    }
    //loop runs as long as head is not null
    while (headNode != NULL)
    {
        //compare val of new element with other values to place the new element
        if (new_entry->cmp_elm(new_entry->val, headNode->val) > 0)
        {
            prev = headNode;
            headNode = headNode->next;
        }
        else
        {
            break;
        }
    }
    //place the new element
    new_entry->next = prev->next;
    prev->next = new_entry;
    return success;
}
/*

* function name: SLSize
* The Input: HEAD head
* The output: return counter val (size of SLN)
* The Function operation: count and print SLN size

*/
int SLSize(HEAD head)
{
    int counter = 0;
    SLN_T* headNode = ((SLN_T*)head);
    //while runs as long as headnode!=null
    while (headNode!=NULL)
    {
        //increase counter value
        counter++;
        headNode = headNode->next;
    }
    //print SLN size
    printf("%d\n", counter);
    return counter;
}
/*

* function name: SLFindElement
* The Input: HEAD head, ELM node
* The output: return ELM
* The Function operation: search val inside the list
  print "TRUE" if exist or "FALSE" if not

*/
ELM SLFindElement(HEAD head, ELM node)
{
    //casting of head
    SLN_T* headNode = ((SLN_T*)head);
    //while runs as long as headnode!=null
    while (headNode != NULL)
    {
        //if node value exist in SLN print 'TRUE' and exit
        if (headNode->cmp_elm(node, headNode->val) == 0)
        {
            printf("TRUE\n");
            return node;
        }
            //no match was founded
        else
        {
            headNode = headNode->next;
        }
    }
    //node value doesn't exist in SLN - print 'FALSE' and exit
    printf("FALSE\n");
    return node;
}
/*

* function name: SLRemoveElement
* The Input: HEAD* head, ELM node
* The output: return RESULT ENUM
* The Function operation: remove element from SLN

*/
RESULT SLRemoveElement(HEAD* head, ELM node)
{
    //casting of head
    SLN_T* headNode = ((SLN_T*)*head);
    //the removable node is the head and it is the only member
    if (headNode->cmp_elm(node, headNode->val) == 0 && headNode->next==NULL)
    {
        *head = NULL;
        //free of memory allocation
        free(headNode->val);
        free(headNode);
        return success;
    }
    //the removable node is the head but it isn't the only element
    if (headNode->cmp_elm(node,headNode->val)==0)
    {
        //copy headNode functions
        headNode->next->cpy_elm = headNode->cpy_elm;
        headNode->next->cmp_elm = headNode->cmp_elm;
        headNode->next->free_elm = headNode->free_elm;
        headNode->next->print_elm = headNode->print_elm;
        headNode->next->add_elm_to_elm = headNode->add_elm_to_elm;
        headNode->next->create_elm = headNode->create_elm;
        //change head
        *head = headNode->next;
        headNode->next = NULL;
        //free of memory allocation
        free(headNode->val);
        free(headNode);
        return success;
    }
    SLN_T* current = headNode->next;
    SLN_T* prev = headNode;
    //the removable node is not the head
    while (current!=NULL)
    {
        if (headNode->cmp_elm(node, current->val) == 0)
        {
            prev->next = current->next;
            current->next = NULL;
            //free of memory allocation
            free(current->val);
            free(current);
            return success;
        }
        prev = current;
        current = current->next;
    }//end of while loop
    //no match - the removable node doesn't exist inside SLN
    printf("FALSE\n");
    return failure;
}
/*

* function name: SLPrint
* The Input: HEAD head
* The output: no output (void)
* The Function operation: print SLN

*/
void SLPrint(HEAD head)
{
    int i;
    //casting of head
    SLN_T* headNode = ((SLN_T*)head);
    //counter counts number of tabs
    int counter = 0;
    //while runs as long as headnode!=null
    while (headNode != NULL)
    {
        for (i = 0; i < counter; i++)
        {
            printf("\t");
        }
        headNode->print_elm(headNode->val);
        headNode = headNode->next;
        counter++;
    }
}
/*

* function name: SLAddToElement
* The Input: HEAD* head, ELM toEl, ELM addEl
* The output: no output (void)
* The Function operation: the func add element to element

*/
void SLAddToElement(HEAD* head, ELM toEl, ELM addEl)
{
    //casting of head value
    SLN_T* headNode = ((SLN_T*)*head);
    SLN_T* temp = headNode;
    int isExist = 0;
    //while runs as long as temp is not null
    while (temp != NULL)
    {
        //if 'toEl' exist in SLN break
        if (temp->cmp_elm(toEl, temp->val) == 0)
        {
            isExist = 1;
            break;
        }
            //no match was founded
        else
        {
            temp = temp->next;
        }
    }
    if (isExist == 1)
    {
        SLN_T *element = (SLN_T *)malloc(sizeof(SLN_T));
        if (element != NULL)
        {
            //allocate memory for val of element
            element->val = headNode->create_elm();
            //copy node to val field
            headNode->cpy_elm(element->val, toEl);
            SLN_T* sumNode = (SLN_T *)malloc(sizeof(SLN_T));
            sumNode->val = headNode->create_elm();
            headNode->cpy_elm(sumNode->val, headNode->add_elm_to_elm(toEl, addEl));
            //add sumNode to SLN
            SLAddListElement(head, sumNode->val);
            //remove toEl from SLN
            SLRemoveElement(head, element->val);
            //free of memory allocation
            free(element->val);
            free(element);
            free(sumNode->val);
            free(sumNode);
        }
    }
}
/*

* function name: SLDestroy
* The Input: HEAD head
* The output: no output (void)
* The Function operation: the func clear all SLN elements

*/
void SLDestroy(HEAD head)
{
    SLN_T* headNode = (HEAD)head;
    SLN_T* temp;
    //while runs as long as headNode != NULL
    while (headNode != NULL)
    {
        temp = headNode;
        headNode = headNode->next;
        //free of memory allocation
        temp->free_elm(temp->val);
        free(temp);
    }
}