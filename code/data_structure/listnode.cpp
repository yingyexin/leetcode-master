#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <limits>
#include <set>

struct ListNode{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *ptr): val(x), next(ptr){}
};

class Solution {
public:
    // Problem 203E
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyNode = new ListNode();
        dummyNode->next = head;
        ListNode* cur = dummyNode;
        while(cur->next!=nullptr){
            if(cur->next->val == val){
                ListNode* temp = cur->next;
                cur->next = cur->next->next;
                delete temp;
            }
            else
                cur = cur->next;
        }
        head = dummyNode->next;
        delete dummyNode;
        return head;
    }

    // Problem 26E
    ListNode* reverseList(ListNode* head) {
        ListNode* temp;
        ListNode* cur = head;
        ListNode* pre = nullptr; // TODO: note: different from cur
        while(cur!=nullptr){//TODO: note
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
    ListNode* reverseList2(ListNode* head) {
        return reverse(nullptr, head);
    }
    ListNode* reverse(ListNode* pre, ListNode* cur){
        if(cur==nullptr) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        return reverse(cur, temp);
    }

    // Problem 24M
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyNode = new ListNode(-1, head);
        ListNode* cur = dummyNode;
        ListNode* temp1;
        ListNode* temp3;
        while(cur->next!=nullptr && cur->next->next!=nullptr){ //TODO:NOTE null->next invalid
            temp1 = cur->next;
            temp3 = cur->next->next->next;
            
            cur->next = cur->next->next;
            cur = cur->next;
            cur->next = temp1;

            cur = cur->next;
            cur->next =temp3;
        }
        head = dummyNode->next;
        delete dummyNode;
        return head;
    }

    // Problem 19M
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyNode = new ListNode(-1, head);//TODO: note make it static
        ListNode* pre = dummyNode;
        ListNode* cur = head;
        int idx=0;
        while(cur->next!=nullptr){
            cur = cur->next;
            idx++;
            if(pre->next!=head)
                pre = pre->next;
            if(idx==n)
                pre = pre->next;
        }
        ListNode* temp = pre->next;
        pre->next = pre->next->next;
        delete temp;
        return dummyNode->next;
    }

    // Problem interview 02.07E
    ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {//TODO: idea 
        ListNode* curA = headA;
        ListNode* curB = headB;
        while(curA != curB){
            curA = curA ? curA->next : headB;//TODO: note use curA, no common, A=B=null
            curB = curB ? curB->next : headA;
        }
        return curA;
    }

    // Problem 142M
    ListNode* detectCycle(ListNode *head) {
        ListNode* dummyNode = new ListNode(-1, head);
        ListNode* fast = dummyNode;
        ListNode* slow = dummyNode;
        while(fast && fast->next){//TODO: note no cycle && at the beginning the same fast & slow
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow){
                ListNode* index1 = dummyNode;
                ListNode* index2 = fast;
                while(index1 != index2){
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return nullptr;
    }
    
    // Problem 2M
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addTwo(l1, l2, 0);
    }
    ListNode* addTwo(ListNode* l1, ListNode* l2, bool flag){
        int m=0, n=0;
        if(!l1 && !l2) return flag ? new ListNode(1) : nullptr;
        if(l2) n = l2->val;
        if(l1) m = l1->val;

        int num = 0;
        if(flag){
            num = m + n + 1;
            flag = 0;
        } else num = m + n;
        if(num>9) flag = 1;

        ListNode* l3 = new ListNode(num%10);
        if(l1 && l2) l3->next = addTwo(l1->next, l2->next, flag);
        else if(!l1) l3->next = addTwo(nullptr, l2->next, flag);
        else if(!l2) l3->next = addTwo(l1->next, nullptr, flag);
        return l3;        
    }
    
    
};



// Problem 707M
class MyLinkedList {
public:
    struct ListNode{
        int val;
        ListNode* next;
        ListNode(): val(0), next(nullptr) {}
        ListNode(int x): val(x), next(nullptr) {}
        ListNode(int x, ListNode *ptr): val(x), next(ptr){}
    };
    
    MyLinkedList() {
        dummyNode_ = new MyLinkedList::ListNode(-1);
        size_ = 0;
    }
    
    int get(int index) {
        int idx = 0;
        ListNode* cur = dummyNode_;
        while(cur!=nullptr && idx<size_){
            if (idx == index){
                return cur->next->val;
            } else{
                cur = cur->next;
                idx++;
            }
        }
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode* node = new ListNode(val);
        ListNode* head = dummyNode_->next;
        dummyNode_->next = node;
        node->next = head;
        size_++;
    }
    
    void addAtTail(int val) {
        addAtIndex(size_, val);
    }
    
    void addAtIndex(int index, int val) {
        ListNode* node = new ListNode(val);
        int idx = 0;
        ListNode* cur = dummyNode_;
        while(cur!=nullptr && idx<=size_){
            if (idx == index){
                node->next = cur->next;
                cur->next = node;
                size_++;
                break;
            } else{
                cur = cur->next;
                idx++;
            }
        }
    }
    
    void deleteAtIndex(int index) {
        ListNode* cur = dummyNode_;
        int idx = 0;
        while(cur->next!=nullptr && idx<size_){
            if(idx == index){
                ListNode* temp = cur->next;
                cur->next = cur->next->next;
                size_--;
                delete temp;
                break;
            }
            else{
                cur = cur->next;
                idx++;
            }
        }
    }

private:
    int size_;
    ListNode* dummyNode_;
};
