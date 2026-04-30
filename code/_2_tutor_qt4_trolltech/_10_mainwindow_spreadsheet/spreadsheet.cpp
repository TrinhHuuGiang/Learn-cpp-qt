#include "spreadsheet.h"

#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QRegularExpression>
#include <QClipboard>

#include <algorithm>
#include <QDebug>

/**
 * ==========================================================
 * Spreedsheet class
 * - QTableWidget: Displaying Cell of Spreedsheet application
 * ==========================================================
 */
Spreadsheet::Spreadsheet(QWidget *parent)
    : QTableWidget{parent}
{
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);


    setRowCount(RowCount);
    setColumnCount(ColumnCount);


    connect(this, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(somethingChanged()));
}

void Spreadsheet::somethingChanged()
{
    qDebug()<< tr("TableWidget data changed !!");
}


/**
 * ==========================================================
 * Cell class
 * - using QTableWidgetItem
 * ==========================================================
 */

Cell::Cell()
{
    setDirty();
}

void Cell::setDirty()
{
    cacheIsDirty = true;
}


QTableWidgetItem *Cell::clone() const   // override QTableWidgetItem::clone()
{
    return new Cell(*this);
}


void Cell::setFormula(const QString &formula)
{
    setData(Qt::EditRole, formula);
}

QString Cell::formula() const
{
    return data(Qt::EditRole).toString();
}

void Cell::setData(int role, const QVariant &value) // override QTableWidgetItem::setData()
{
    QTableWidgetItem::setData(role, value); // base QTableWidgetItem::setData()
    if (role == Qt::EditRole)
        setDirty();
}

// data() will get data follow role ( enum Qt::ItemDataRole )
QVariant Cell::data(int role) const // override QTableWidgetItem::data()
{
    if (role == Qt::DisplayRole) {
        if (value().isValid()) {
            return value().toString();
        } else {
            return "####";
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (value().type() == QVariant::String) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        } else {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    } else {
        return QTableWidgetItem::data(role);
    }
}


const QVariant Invalid;
QVariant Cell::value() const
{
    if (cacheIsDirty) {
        cacheIsDirty = false;
        QString formulaStr = formula();
        if (formulaStr.startsWith('\'')) {
            cachedValue = formulaStr.mid(1);
        } else if (formulaStr.startsWith('=')) {
            cachedValue = Invalid;
            QString expr = formulaStr.mid(1);
            expr.replace(" ", "");
            expr.append(QChar::Null);
            int pos = 0;
            cachedValue = evalExpression(expr, pos);
            if (expr[pos] != QChar::Null)
                cachedValue = Invalid;
        } else {
            bool ok;
            double d = formulaStr.toDouble(&ok);
            if (ok) {
                cachedValue = d;
            } else {
                cachedValue = formulaStr;
            }
        }
    }
    return cachedValue;
}


QVariant Cell::evalExpression(const QString &str, int &pos) const
{
    // logic here

    return Invalid;
}
