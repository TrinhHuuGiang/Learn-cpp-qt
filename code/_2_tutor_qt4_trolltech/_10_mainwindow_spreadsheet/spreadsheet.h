#ifndef SPREADSHEET_H
#define SPREADSHEET_H


#include <QTableWidget>
#include <QTableWidgetItem>

#include <QString>
#include <QVariant>

/**
 * ==========================================================
 * Forward declaration classes
 * ==========================================================
 */
class Cell;
class SpreadsheetCompare;

/**
 * ==========================================================
 * Spreadsheet class
 * - QTableWidget: Displaying Cell of Spreedsheet application
 * ==========================================================
 */
class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit Spreadsheet(QWidget *parent = nullptr);

public slots:


signals:
    void modified();

private slots:
    void somethingChanged();

private:
    enum { MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26 };
    Cell *cell(int row, int column) const;

};


/**
 * ==========================================================
 * Cell class
 * - using QTableWidgetItem (do not a QObject)
 * ==========================================================
 */
class Cell : public QTableWidgetItem
{
public:
    Cell();
    QTableWidgetItem *clone() const;    // copy constructor inside

    void setDirty();    // init cache is dirty

    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString formula() const;


private:
    QVariant value() const;

    QVariant evalExpression(const QString &str, int &pos) const;


    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;

};


#endif // SPREADSHEET_H
