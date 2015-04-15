#ifndef CHAIN_TABLEVIEW_H
#define CHAIN_TABLEVIEW_H

#include <QTableView>

namespace Chain
{
    class Chain_Tableview :
            public QTableView
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        explicit Chain_Tableview(QWidget *parent = nullptr);
        ~Chain_Tableview() override;

    public slots:
        // Slots
        //============================================================
        // Connected to this->customContextMenuRequested
        void slot_customContextMenuRequested(QPoint const& pos);
    };

} // namespace Chain


#endif // CHAIN_TABLEVIEW_H
