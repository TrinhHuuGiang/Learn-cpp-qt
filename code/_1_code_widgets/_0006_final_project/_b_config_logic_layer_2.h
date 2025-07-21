#ifndef _B_CONFIG_LOGIC_LAYER_2_H
#define _B_CONFIG_LOGIC_LAYER_2_H

/*
 * Note:
 * - About Close event: https://doc.qt.io/qt-6.5/qwidget.html#closeEvent
 */

/* =============================================================
 * Definitions
============================================================= */
#include <QWidget>

#include <QCloseEvent> // handle how close by X

#include "_b_config_logic_layer.h"

namespace Ui {
class _b__preview_and_config;
}


/* =============================================================
 * Classes
============================================================= */
class _b__preview_and_config : public QWidget
{
    Q_OBJECT

public:
    explicit _b__preview_and_config(const board_info_t& board_info_origin,
                                    const QString& final_json_str,
        QWidget *parent = nullptr);
    ~_b__preview_and_config();

signals:
    void preview_page_closed();


private slots:
    void on_btn_exit_clicked();




private:
    Ui::_b__preview_and_config *ui;

    board_info_t board_info_origin;

    QString final_json_str;


protected:
    void closeEvent(QCloseEvent *event) override;  // this function auto callback by qt when user click X
                                                    // button X is designed call back this handle

};

#endif // _B_CONFIG_LOGIC_LAYER_2_H
