
#include "sortedlinkedlist.h"

Node::Node() {
    id = 0;
	rate = 0;
    next = NULL;
};

Node::Node(int d, float rt) {
	id = d;
	rate = rt;
    next = NULL;
}

void sortedLinkeList::insert(Node* item) {

	if (head == nullptr) {
		head = item;
		tail = head;
	}
	else {

		Node* temp = head;
		if (count == 1) {
			if (head->rate < item->rate) {
				head = item;
				head->next = temp;
				tail = temp;
			}
			else {
				head->next = item;
				tail = item;
			}
		}
		else {

			if (tail->rate >= item->rate) {
				tail->next = item;
				tail = item;
			}
			else if (head->rate <= item->rate) {
				head = item;
				head->next = temp;
			}
			else {

				while ((temp->next != nullptr) && temp->next->rate >= item->rate) {
					temp = temp->next;
				}
				item->next = temp->next;
				temp->next = item;
			}
		}
	}
	count++;
}
