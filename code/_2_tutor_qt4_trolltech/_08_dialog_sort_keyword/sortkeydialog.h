#ifndef SORTKEYDIALOG_H
#define SORTKEYDIALOG_H

#include <QDialog>

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

private:
    Ui::SortKeyDialog *ui;
};
#endif // SORTKEYDIALOG_H
