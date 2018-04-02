/******************************************
* Student name: Liz Aharonian
* Course Exercise Group: 01
* Exercise name: ex6
******************************************/

#include "GADT.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

//declarations of not-generic functions
ELM CreateChar();
ELM CreatePoint();
ELM ScanChars();
ELM ScanPoint();
void CopyChar(ELM elm1, ELM elm2);
int CmpChar(ELM elm1, ELM elm2);
void FreeChars(ELM elm);
void PrintChars(ELM elm);
ELM AddCharToChar(ELM elm1, ELM elm2);
void CopyPoint(ELM elm1, ELM elm2);
int CmpPoint(ELM elm1, ELM elm2);
void FreePoint(ELM elm);
void PrintPoint(ELM elm);
ELM AddPointToPoint(ELM elm1, ELM elm2);
void LinkedCharList(HEAD* head);
void LinkedPointList(HEAD* head);
RESULT CaseT(HEAD* head, int charOrPointOperation);
int SelectOperationsOfList(HEAD head, int charOrPointOperation);
//point struct
typedef struct
{
    int x;
    int y;
    int d;
}point;

/*

* function name: main
* The Input: no input
* The output: return 0
* The Function operation: the main function, start point of the program.
  calls diffrent functions acording to selected option

*/

int main()
{
    //declaration of variables
    int charOrPointOperation;
    char dummy;
    //head of SLN
    HEAD head = NULL;
    //scan option from user
    scanf("%d", &charOrPointOperation);
    //dummy recieves the '/n' char
    scanf("%c", &dummy);
    //switch calls the rellevant func acording to user's choice
    switch (charOrPointOperation)
    {
        //in case user chose list of strings
        case 0:
            //call LinkedCharList to create head of list
            LinkedCharList(&head);
            break;
            //in case user chose list of points
        case 1:
            //call LinkedPointList to create head of list
            LinkedPointList(&head);
            break;
        default:
            break;
    }//end of switch-case
    //call SelectOperationsOfList func to get user's operations
    SelectOperationsOfList(head, charOrPointOperation);
    return 0;
}
/*

* function name: SelectOperationsOfList
* The Input: HEAD* head,int charOrPointOperation
* The output: return 0
* The Function operation: operate diffrent options on SLN.
  calls diffrent functions acording to selected option

*/
int SelectOperationsOfList(HEAD head,int charOrPointOperation)
{
    //element inside SLN
    ELM element = NULL;
    char option;
    char dummy;
    do
    {
        //scan option from user
        scanf("%c", &option);
        //dummy recieves the '/n' char
        scanf("%c", &dummy);
        //scan input string or point from user
        if ((charOrPointOperation == 0) && (option=='a'||option=='d' || option == 's'))
        {
            //call ScanChars func in order to scan string from user
            element = ScanChars();
        }
        else if ((charOrPointOperation == 1) && (option == 'a' || option == 'd'||option=='s'))
        {
            //call ScanPoint func in order to scan point from user
            element = ScanPoint();
        }
        //switch calls the rellevant func acording to user's choice
        switch (option)
        {
            //call SLAddListElement in order to add new element to SLN
            case 'a':
                SLAddListElement(&head, element);
                //free of memory allocation
                free(element);
                break;
                //call SLSize in order to print size of SLN
            case 'l':
                SLSize(head);
                break;
                //call SLPrint in order to print SLN's elements
            case 'p':
                SLPrint(head);
                break;
                //call SLFindElement in order to know if element exist inside SLN
            case 's':
                SLFindElement(head, element);
                //free of memory allocation
                free(element);
                break;
                //call SLRemoveElement in order to remove element from SLN
            case 'd':
            {
                SLRemoveElement(&head, element);
                //free of memory allocation
                free(element);
                //close the program in case the last element of list was deleted
                if (head==NULL)
                {
                    //exit function, return to main func
                    return 0;
                }
                break;
            }
                //call CaseT in order to add element to element of SLN
            case 't':
                CaseT(&head, charOrPointOperation);
                break;
                //call SLDestroy in order to delete SLN
            case 'e':
                SLDestroy(head);
                break;
            default:
                break;
        }//end of switch-case
    } while (option != 'e'); //end of while loop
    return 0;
}
/*

* function name: CaseT
* The Input: HEAD* head, int charOrPointOperation
* The output: return result ENUM
* The Function operation: operate option T.
  call SLAddToElement function in order to add element to element of SLN

*/
RESULT CaseT(HEAD* head, int charOrPointOperation)
{
    char dummy;
    //if user chose SLN of strings
    if (charOrPointOperation == 0)
    {
        //memory allocation
        char *element = CreateChar();
        char *addElement = CreateChar();
        //check if memory allocation was failed
        if (element == NULL || addElement == NULL)
        {
            return outOfMem;
        }
        //scan element and add element from user
        scanf("%s %s", element, addElement);
        //dummy recieves the '/n' char
        scanf("%c", &dummy);
        //call SLAddToElement function in order to add element to element of SLN
        SLAddToElement(head, element, addElement);
        //free of memory allocation
        free(element);
        free(addElement);
    }
        //if user chose SLN of points
    else if (charOrPointOperation == 1)
    {
        //memory allocation
        point *element = CreatePoint();
        point *addElement = CreatePoint();
        //check if memory allocation was failed
        if (element == NULL || addElement == NULL)
        {
            return outOfMem;
        }
        //scan element and add element from user
        scanf("%c%d%c%d%c %c%d%c%d%c", &dummy, &element->x, &dummy, &element->y,
              &dummy, &dummy, &addElement->x, &dummy, &addElement->y, &dummy);
        //dummy recieves the '/n' char
        scanf("%c", &dummy);
        //call SLAddToElement function in order to add element to element of SLN
        SLAddToElement(head, element, addElement);
        //free of memory allocation
        free(element);
        free(addElement);
    }
}
/*

* function name: CreatePoint
* The Input: no input
* The output: return ELM
* The Function operation: allocate memory for point

*/
ELM  CreatePoint()
{
    return ((point*)malloc(sizeof(point)));
}
/*

* function name: ScanPoint
* The Input: no input
* The output: return ELM
* The Function operation: scan point

*/
ELM ScanPoint()
{
    point* point = CreatePoint();
    char dummy;
    if (point != NULL)
    {
        scanf("%c%d%c%d%c", &dummy, &point->x, &dummy, &point->y, &dummy);
        //dummy recieves the '/n' char
        scanf("%c", &dummy);
        point->d = abs(point->x) + abs(point->y);
        return point;
    }
}
/*

* function name: CopyPoint
* The Input: ELM elm1, ELM elm2
* The output: no output (void)
* The Function operation: copy point

*/
void CopyPoint(ELM elm1, ELM elm2)
{
    point* firstElm =(point*)elm1;
    point* secondElm = (point*)elm2;
    firstElm->x = secondElm->x;
    firstElm->y = secondElm->y;
    firstElm->d = secondElm->d;
}
/*

* function name: CmpPoint
* The Input: ELM elm1, ELM elm2
* The output: int val
* The Function operation: compare points distance

*/
int CmpPoint(ELM elm1, ELM elm2)
{
    //cast from (void*) to (point*)
    point* firstElm = (point*)elm1;
    point* secondElm = (point*)elm2;
    firstElm->d = abs(firstElm->x) + abs(firstElm->y);
    secondElm->d=abs(secondElm->x) + abs(secondElm->y);
    if (firstElm->d == secondElm->d)
    {
        //return 0 if sum of absulute value is the same
        return 0;
    }
    else if (firstElm->d > secondElm->d)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
/*

* function name: FreePoint
* The Input: ELM elm
* The output: no output (void)
* The Function operation: free point

*/
void FreePoint(ELM elm)
{
    //cast from (void*) to (point*)
    point* element = (point*)elm;
    free(element);
}
/*

* function name: PrintPoint
* The Input: ELM elm
* The output: no output (void)
* The Function operation: print point

*/
void PrintPoint(ELM elm)
{
    //cast from (void*) to (point*)
    point* element = (point*)elm;
    //print positive numbers
    if ((element->x) >= 0)
    {
        printf("%03d", element->x);
    }
        //print negative numbers
    else
    {
        printf("%.3d", element->x);
    }
    printf("%c", '|');
    //print positive numbers
    if ((element->y) >= 0)
    {
        printf("%03d\n", element->y);
    }
        //print negative numbers
    else
    {
        printf("%.3d\n", element->y);
    }
}

/*

* function name: AddPointToPoint
* The Input: ELM elm1, ELM elm2
* The output: return ELM
* The Function operation: sums points

*/
ELM AddPointToPoint(ELM elm1, ELM elm2)
{
    point* firstElm = (point*)elm1;
    point* secondElm = (point*)elm2;
    firstElm->x = (firstElm->x) + (secondElm->x);
    firstElm->y = (firstElm->y) + (secondElm->y);
    return firstElm;
}
/*

* function name: CreateChar
* The Input: no input
* The output: return ELM
* The Function operation: allocate memory for string

*/
ELM CreateChar()
{
    return ((char*)malloc(16 * sizeof(char)));
}
/*

* function name: ScanChars
* The Input: no input
* The output: return ELM
* The Function operation: scan string

*/
ELM ScanChars()
{
    char *element = CreateChar();
    char dummy;
    if (element != NULL)
    {
        scanf("%s", element);
        scanf("%c", &dummy);
        return element;
    }
}
/*

* function name: CopyChar
* The Input: ELM elm1, ELM elm2
* The output: no output (void)
* The Function operation: copy string

*/
void CopyChar(ELM elm1, ELM elm2)
{
    strcpy(elm1, elm2);
}
/*

* function name: CmpChar
* The Input: ELM elm1, ELM elm2
* The output: int val
* The Function operation: compare strings

*/
int CmpChar(ELM elm1, ELM elm2)
{
    //cast from (void*) to (char*)
    char * firstElm = (char*)elm1;
    char * secondElm = (char*)elm2;
    return (strcmp(firstElm, secondElm));
}
/*

* function name: FreeChars
* The Input: ELM elm
* The output: no output (void)
* The Function operation: free string

*/
void FreeChars(ELM elm)
{
    //cast from (void*) to (char*)
    char* element = (char*)elm;
    free(element);
}
/*

* function name: PrintChars
* The Input: ELM elm
* The output: no output (void)
* The Function operation: print string

*/
void PrintChars(ELM elm)
{
    //cast from (void*) to (char*)
    char * element = (char*)elm;
    printf("%s\n", element);
}
/*

* function name: AddCharToChar
* The Input: ELM elm1, ELM elm2
* The output: return ELM
* The Function operation: sums strings

*/
ELM AddCharToChar(ELM elm1, ELM elm2)
{
    //cast from (void*) to (char*)
    char* firstElm = (char*)elm1;
    char* secondElm = (char*)elm2;
    return(strcat(firstElm, secondElm));
}
/*

* function name: LinkedCharList
* The Input: HEAD* head
* The output: no output (void)
* The Function operation: create head of list

*/
void LinkedCharList(HEAD* head)
{
    char dummy;
    char *headOfList = (char*)malloc(16 * sizeof(char));
    if (headOfList!=NULL)
    {
        scanf("%s", headOfList);
        scanf("%c", &dummy);
        //call SLCreate to create head of SLN
        *head = SLCreate(headOfList, CreateChar, CopyChar,
                         CmpChar, FreeChars,
                         PrintChars, AddCharToChar);
        free(headOfList);
    }
}
/*

* function name: LinkedPointList
* The Input: HEAD* head
* The output: no output (void)
* The Function operation: create head of list

*/
void LinkedPointList(HEAD* head)
{
    char dummy;
    point *headerpoint= (point*)malloc(sizeof(point));
    if (headerpoint != NULL)
    {
        scanf("%c%d%c%d%c", &dummy, &headerpoint->x, &dummy, &headerpoint->y, &dummy);
        //dummy recieves the '/n' char
        scanf("%c", &dummy);
        //call SLCreate to create head of SLN
        *head = SLCreate(headerpoint, CreatePoint, CopyPoint,
                         CmpPoint, FreePoint,
                         PrintPoint, AddPointToPoint);
        free(headerpoint);

    }
}

