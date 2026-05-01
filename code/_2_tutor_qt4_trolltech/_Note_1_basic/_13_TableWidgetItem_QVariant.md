Follow project: **Spreadsheet**

- Comming soon : QVariant
- addition note: virtual `clone()`, `setData()`, `data()`

## Content
- [QTableWidgetItem](#qtablewidgetitem)
- [QTableWidget method](#qtablewidget-method)

---

## QTableWidgetItem
It **is not** a *QObject*, so it life cycle depend on:
- scope if static allocation
- set a child of **QTableWidget** if dynamic allocation with **setItem()** method.

**QTableWidgetItem** can hold some data type or using QVariant for custem type

A **QTableWidgetItem** can set role when showing in **QTableWidget**:
- *Qt::EditRole*  is used for data that is to be edited
- *Qt::DisplayRole* is for data that is to be displayed



- Note `clone()`, `setData()`, `data()`

---
