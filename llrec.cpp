#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    if (head == nullptr){ // receiving an empty list
        smaller = nullptr; 
        larger = nullptr; 
        return; 
    }

    Node* headTemp = head; 
    head = head->next; 

    if (headTemp->val > pivot){
        llpivot(head, smaller, larger, pivot);
        headTemp->next = larger; 
        larger = headTemp; 
    }
    else {
        llpivot(head, smaller, larger, pivot);
        headTemp->next = smaller;
        smaller = headTemp;
    }
}