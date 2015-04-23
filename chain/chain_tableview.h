#ifndef CHAIN_TABLEVIEW_H
#define CHAIN_TABLEVIEW_H

#include <QTableView>

namespace Chain
{
    /*
    Chain_Tableview
    ====================================================================================================
    Subclass of QTableView that configures itself on construction and has a custom context menu.
    */
    class Chain_Tableview :
            public QTableView
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        explicit Chain_Tableview(QWidget *parent = nullptr);
        ~Chain_Tableview() override;

        // No copying
        Chain_Tableview(Chain_Tableview const& other) = delete;
        Chain_Tableview& operator=(Chain_Tableview const& other) = delete;

        // Implicit default move
        //Chain_Tableview(Chain_Tableview && other) = default;
        //Chain_Tableview& operator=(Chain_Tableview && other) = default;

    public slots:
        // Slots
        //============================================================
        void slot_customContextMenuRequested(QPoint const& pos);
    };

} // namespace Chain


#endif // CHAIN_TABLEVIEW_H
