#include "chain_tableview.h"
#include "chain_table_model.h"
#include <QMenu>
#include <QCursor>
#include <QHeaderView>

// Special 6
//============================================================
Chain::Chain_Tableview::Chain_Tableview(QWidget *parent):
    QTableView(parent)
{
    // Enable a custom context menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    // Connect the signal requesting it to the function that generates it
    QObject::connect(this, &QTableView::customContextMenuRequested,
                     this, &Chain_Tableview::slot_customContextMenuRequested);

    // Set selection to cells only
    this->setSelectionBehavior(QAbstractItemView::SelectItems);

    // Set selection to one cell at a time
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    // Set scrollbar policies
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Hide the horizontal header as it contains nothing
    this->horizontalHeader()->hide();
}

Chain::Chain_Tableview::~Chain_Tableview() = default;

// Slots
//============================================================
// Connected to this->customContextMenuRequested
void Chain::Chain_Tableview::slot_customContextMenuRequested(QPoint const& pos)
{
    // Assume this has the right model type and cast to it
    Chain_Table_Model* true_model = static_cast<Chain_Table_Model*>(this->model());

    // Get the index at the given position
    QModelIndex index = this->indexAt(pos);

    // If the model correct and not nullptr, and the index we're at is within the chain data
    if (true_model && true_model->is_within_chain(index))
    {
        // Make a context menu
        QMenu context_menu{};

        // Add an action as a title that is the tooltip (date) of the given data point
        context_menu.addAction(true_model->get_tooltip(index))->setEnabled(false);
        context_menu.addSeparator();

        // Make an action for setting the data and capture the pointer to it
        auto did_stuff_action = context_menu.addAction("Did Stuff?");

        // Make that action checkable and set its state to that of the data
        did_stuff_action->setCheckable(true);
        did_stuff_action->setChecked(true_model->link_did_stuff(index));

        // Connect the action to a lambda that will set the data appropriately when the action is triggered
        QObject::connect(did_stuff_action, &QAction::toggled,
                         [true_model, &index] (bool state) { true_model->set_link_did_stuff(index, state); } );

        // Execute the menu at the cursor position
        context_menu.exec(QCursor::pos());
        // this one isn't putting the menu in the right place.
        //context_menu.exec(this->mapToGlobal(pos));
    }
}
