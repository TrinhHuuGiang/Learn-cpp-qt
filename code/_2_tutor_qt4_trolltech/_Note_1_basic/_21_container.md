

## Content
1. C++ container (see more at *https://cplusplus.com/reference/stl/*)
- array
- vector
- list
- forward_list
- queue
- deque
- stack
- map
- unordered_map
- set
- unordered_set

---

2. Qt container (see more in example *_21_container*)
- QVector<T>    (**Recommended**)
    - is an array-like data structure that stores its items at adjacent
    positions in memory, access element by **[]** operator.
    - Inserting items at the beginning or in the middle of a QVector<T>, or removing items from these positions, can be inefficient for large vectors.
    - Search by algorithm.
    - Reduce memory fragmentation.
- QLinkedList<T>    (**Deprecated Qt6**)
    - a data structure that stores its items at non-adjacent locations in memory.
    - linked lists don’t support random access, but they provide *constant time* insertions and removals.
    - Search by iterator.
    - Risk memory fragmentation.
    - Note availabe in Qt6: https://forum.qt.io/topic/143626/is-there-a-version-of-qlinkedlist-in-qt6/5
- QList<T> :  sequential container is an *array-list* that combines  benefits of QVector<T> and QLinkedList<T> in a single class.
    - It supports random access
    - Inserting or removing  at either end very fast. 
    - Inserting in the middle is fast for lists with up to about one thousand items.
    - Infact it same with QVector<T>

- QStack<T> 
    - is a vector that provides push(), pop(), and top(). 
- QQueue<T> 
    - is a list that provides enqueue(), dequeue(), and head()

    
---