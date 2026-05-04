For all the container classes seen so far, the value type **T** can be a basic type
like: int or double, a pointer type, **or** a class that has:
- a default constructor (a constructor that takes no arguments)
- a copy constructor
- and an assignment operator. 

The value type T can also be a container, in which case we must remember to
separate consecutive angle brackets with spaces; otherwise, the compiler will
choke on what it thinks is a >> operator. For example:

```cpp
    QList<QVector<double> > list;
```

In Qt, the Qt classes that **inherit from QObject** do not qualify, because they
lack a copy constructor and an assignment operator.

Basic classes that qualify in Qt include: QByteArray, QDateTime, QRegExp, QString and QVariant. 

## Content
1. C++ container (see more at *https://cplusplus.com/reference/stl/*)
- Sequential Containers: items store at adjacent positions in memory.
    - array
    - vector
    - list
    - forward_list
    - queue
    - deque
    - stack
- Associative Containers:  The items have the same type, may store or not adjacent in memory
    but indexed by a key.
    - map == unique hey|value
    - unordered_map == hash by unique key
    - set == unique value
    - unordered_set == hash by unique value

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
    - is a list (maybe linkedlist :V) that provides enqueue(), dequeue(), and head()

- QMap<K, T> 
    - is a data structure that stores key–value pairs in **ascending** key (**K**) order.
    - search by inside AVL binary tree structure.
    - The **key type** of a QMap **must provide operator<()** specifying a total order. 

- QHash<K, T>
    - The key type of a QHash must provide **operator==()** and a global **qHash(Key) function**.
    - **QHash** class has same style member function with **QMap** but different the data structure inside:
        - Hash using for fast data look up with key. Example: topic, random event, ...
        - Map using when require key with order. Example: timeline, task list, ...

---