#ifndef CHAIN_TABLE_MODEL_H
#define CHAIN_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QColor>

namespace Chain
{
    class Chain_Data;

    /*
    Chain_Table_Model
    ====================================================================================================
    Model class to represent Chain_Data in view classes.

    Note:
    In Chain_Data a weekday spans 1 - 7, in the model it spans 0 - 6
    */

    class Chain_Table_Model :
            public QAbstractTableModel
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        explicit Chain_Table_Model(Chain_Data& chain_data, QObject* parent = nullptr);
        ~Chain_Table_Model() override;

        Chain_Table_Model(Chain_Table_Model const& other) = delete;
        Chain_Table_Model& operator=(Chain_Table_Model const& other) = delete;

        //Chain_Table_Model(Chain_Table_Model && other) = default;
        //Chain_Table_Model& operator=(Chain_Table_Model && other) = default;

        // Virtual Overrides
        //============================================================
        // Read functions
        //----------------------------------------
        // Get the flags for the given QModelIndex.
        Qt::ItemFlags flags(QModelIndex const& index) const override;
        // Get the data for the given QModelIndex.
        QVariant data(QModelIndex const& index, int role) const override;
        // Get the header data for a given section and orientation
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        // Always returns 7
        int rowCount(QModelIndex const& index = QModelIndex()) const override;
        // The number of weeks the chain spans
        int columnCount(QModelIndex const& index = QModelIndex()) const override;

        // Write functions
        //----------------------------------------
        // Set the data at a given index with value, using role
        bool setData (QModelIndex const& index, QVariant const& value, int role = Qt::EditRole ) override;
        bool setHeaderData ( int section, Qt::Orientation orientation, QVariant const& value, int role = Qt::EditRole ) override;

        QColor get_colour(QModelIndex const& index) const;
        QColor get_colour(int column, int row) const;

        QString get_tooltip(QModelIndex const& index) const;
        QString get_tooltip(int column, int row) const;

        bool within_chain(QModelIndex const& index) const;
        bool within_chain(int column, int row) const;

        bool link_did_stuff(QModelIndex const& index) const;
        bool link_did_stuff(int column, int row) const;
        // TableView context menu should call this method to set the data
        void set_link_did_stuff(QModelIndex const& index, bool state);

    private:
        Chain_Data& mr_chain_data;

        static QColor const s_color_blank;
        static QColor const s_color_nothing;
    };

} // namespace Chain

#endif // CHAIN_TABLE_MODEL_H
