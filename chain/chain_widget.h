#ifndef CHAIN_WIDGET_H
#define CHAIN_WIDGET_H

#include <QGroupBox>
#include <array>
#include "quptr.h"
#include "chain_data.h"

class QVBoxLayout;
class QLabel;
class QScrollArea;
class QGridLayout;

namespace Chain
{
    class Link_Widget;
    class Chain_Table_Model;
    class Chain_Tableview;

    /*
    Chain_Widget
    ====================================================================================================
    QGroupBox subclass (so the widget has a frame) that contains a chain's data and the widgets required
    to display and edit it. This class is not responsible for saving or loading chain data, but provides
    access to it for that to be done elsewhere.
    */
    class Chain_Widget :
            public QGroupBox
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        Chain_Widget(QString const& title,
                     QString const& description,
                     QColor colour,
                     QDate start_date = QDate::currentDate(),
                     QWidget* parent = nullptr);

        Chain_Widget(QString const& title,
                     QString const& description,
                     QColor colour,
                     QDate start_date,
                     QList<bool> const& data,
                     QWidget* parent = nullptr);

        // This constructor is does all the work.
        explicit Chain_Widget(Chain_Data && data, QWidget* parent = nullptr);

        ~Chain_Widget() override;

        // No copying
        Chain_Widget(Chain_Widget const& other) = delete;
        Chain_Widget& operator=(Chain_Widget const& other) = delete;

        // Implicit default move
        //Chain_Widget(Chain_Widget && other) = default;
        //Chain_Widget& operator=(Chain_Widget && other) = default;

        // Interface
        //============================================================
        Chain_Data const& data() const;

    signals:

    public slots:

    private:
        // Data Members
        //============================================================
        Chain_Data m_data;
        QUptr<QLabel> m_description_label;
        QUptr<QVBoxLayout> m_layout;
        QUptr<Chain_Table_Model> m_model;
        QUptr<Chain_Tableview> m_tableview;
    };

} // namespace Chain

#endif // CHAIN_WIDGET_H
