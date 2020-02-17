#ifndef LIST_TRAVERSE_H_
#define LIST_TRAVERSE_H_

#include "List.h"

template <typename T>
void List<T>::traverse(void (*visit)(T &)) {
    for (NodeP p = head->next(); p != tail; p = p->next())
        visit(p->_data);
}

#endif
