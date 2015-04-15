#include "chain_tableview.h"
#include "chain_table_model.h"
#include <QMenu>

// Special 6
//============================================================
Chain::Chain_Tableview::Chain_Tableview(QWidget *parent):
    QTableView(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, &QTableView::customContextMenuRequested,
                     this, &Chain_Tableview::slot_customContextMenuRequested);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

Chain::Chain_Tableview::~Chain_Tableview() = default;

// Slots
//============================================================
// Connected to this->customContextMenuRequested
void Chain::Chain_Tableview::slot_customContextMenuRequested(QPoint const& pos)
{
    Chain_Table_Model* true_model = dynamic_cast<Chain_Table_Model*>(this->model());
    QModelIndex index = this->indexAt(pos);
    if (true_model && true_model->within_chain(index))
    {
        QMenu context_menu{};
        //context_menu.setTitle(true_model->get_tooltip(index));
        context_menu.addAction(true_model->get_tooltip(index))->setEnabled(false);
        context_menu.addSeparator();
        auto did_stuff_action = context_menu.addAction("Did Stuff?");
        did_stuff_action->setCheckable(true);
        did_stuff_action->setChecked(true_model->link_did_stuff(index));

        QObject::connect(did_stuff_action, &QAction::toggled,
                         [true_model, &index] (bool state) { true_model->set_link_did_stuff(index, state); } );

        context_menu.exec(this->mapToGlobal(pos));
    }
}
