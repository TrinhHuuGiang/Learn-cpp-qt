#ifndef SORTKEYDIALOG_H
#define SORTKEYDIALOG_H

#include <QDialog>
#include <QChar>

QT_BEGIN_NAMESPACE
namespace Ui {
class SortKeyDialog;
}
QT_END_NAMESPACE

class SortKeyDialog : public QDialog
{
    Q_OBJECT

public:
    SortKeyDialog(QWidget *parent = nullptr);
    ~SortKeyDialog();

    void setColumnRange(QChar first, QChar last);

private:
    Ui::SortKeyDialog *ui;
};
#endif // SORTKEYDIALOG_H
