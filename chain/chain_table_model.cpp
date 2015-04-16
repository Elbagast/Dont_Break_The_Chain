#include "chain_table_model.h"
#include "chain_data.h"
#include <QBrush>
#include <QDebug>


QColor const Chain::Chain_Table_Model::s_color_blank = QColor(200,200,200,255);
QColor const Chain::Chain_Table_Model::s_color_nothing = QColor(255,255,255,255);

// Special 6
//============================================================
Chain::Chain_Table_Model::Chain_Table_Model(Chain_Data& chain_data, QObject* parent):
    QAbstractTableModel(parent),
    mr_chain_data(chain_data)
{

}

Chain::Chain_Table_Model::~Chain_Table_Model() = default;

// Virtual Overrides
//============================================================
// Read functions
//----------------------------------------
// Get the flags for the given QModelIndex.
Qt::ItemFlags Chain::Chain_Table_Model::flags(QModelIndex const& index) const
{
    // if index is valid
    if (index.isValid() && within_chain(index))
    {
        return Qt::ItemIsEnabled;// | Qt::ItemIsSelectable; // editing will be indirect...
    }

    // else no flags
    return Qt::NoItemFlags;
}

// Get the data for the given QModelIndex.
QVariant Chain::Chain_Table_Model::data(QModelIndex const& index, int role) const
{
    if (role == Qt::BackgroundRole || role == Qt::BackgroundColorRole)
    {
        // get the background colour for this index
        QColor background_colour = get_colour(index);
        return QVariant(QBrush(background_colour));
    }
    else if (role == Qt::DisplayRole)
    {
        // If you want text in the cells, do it here
        return QVariant();
    }
    else if (role == Qt::ToolTipRole)
    {
        // get the tooltip for this index
        QString tooltip = get_tooltip(index);
        return QVariant(tooltip);
    }
    return QVariant();
}

// Get the header data for a given section and orientation
QVariant Chain::Chain_Table_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Orientation::Vertical && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0:     return QVariant("Mon");
        case 1:     return QVariant("Tue");
        case 2:     return QVariant("Wed");
        case 3:     return QVariant("Thu");
        case 4:     return QVariant("Fri");
        case 5:     return QVariant("Sat");
        case 6:     return QVariant("Sun");
        default:    return QVariant();
        }
    }
    return QVariant();
}

// Always returns 7
int Chain::Chain_Table_Model::rowCount(QModelIndex const& /*index*/) const
{
    return 7;
}

// The number of weeks the chain spans
int Chain::Chain_Table_Model::columnCount(QModelIndex const& /*index*/) const
{
    return mr_chain_data.week_count();
}


// Write functions
//----------------------------------------
// Set the data at a given index with value, using role
bool Chain::Chain_Table_Model::setData(QModelIndex const& /*index*/, QVariant const& /*value*/, int /*role*/)
{
    return false;
}

bool Chain::Chain_Table_Model::setHeaderData(int /*section*/, Qt::Orientation /*orientation*/, QVariant const& /*value*/, int /*role*/)
{
    return false;
}

QColor Chain::Chain_Table_Model::get_colour(QModelIndex const& index) const
{
    return get_colour(index.column(), index.row());
}

QColor Chain::Chain_Table_Model::get_colour(int column, int row) const
{
    if (within_chain(column, row))
    {
        // calculate the index from column and row
        if (mr_chain_data.link(column, row + 1))
        {
            return mr_chain_data.colour();
        }
        else
        {
            return s_color_nothing;
        }
    }
    else
    {
        return s_color_blank;
    }
}


QString Chain::Chain_Table_Model::get_tooltip(QModelIndex const& index) const
{
    return get_tooltip(index.column(), index.row());
}

QString Chain::Chain_Table_Model::get_tooltip(int column, int row) const
{
    if (within_chain(column, row))
    {
        return mr_chain_data.link_date(column, row + 1).toString();
    }
    else
    {
        return QString();
    }
}

bool Chain::Chain_Table_Model::within_chain(QModelIndex const& index) const
{
    if (index.isValid())
    {
        return within_chain(index.column(), index.row());
    }
    else
    {
        return false;
    }
}

bool Chain::Chain_Table_Model::within_chain(int column, int row) const
{
    // if the inputs are invalid
    if (column < 0 || row < 0)
    {
        return false;
    }
    // if in days before the chain
    else if (column == 0 && row + 1 < mr_chain_data.first_day_weekday())
    {
        return false;
    }
    // else if in days after the chain
    else if (column == columnCount() - 1 && row + 1 > mr_chain_data.last_day_weekday())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Chain::Chain_Table_Model::link_did_stuff(QModelIndex const& index) const
{
    return link_did_stuff(index.column(), index.row());
}

bool Chain::Chain_Table_Model::link_did_stuff(int column, int row) const
{
    if (within_chain(column, row))
    {
        // convert row to weekday in the data
        return mr_chain_data.link(column, row + 1);
    }
    else
    {
        return false;
    }
}

// TableView context menu should call this method to set the data
void Chain::Chain_Table_Model::set_link_did_stuff(QModelIndex const& index, bool state)
{
    if (within_chain(index))
    {
        mr_chain_data.set_link(index.column(), index.row() + 1, state);
        emit dataChanged(index, index, {Qt::BackgroundRole});
    }
}
