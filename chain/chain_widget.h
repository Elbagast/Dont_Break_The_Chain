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

    class Chain_Widget :
            public QGroupBox
    {
        Q_OBJECT
    public:
        Chain_Widget(std::string const& title, std::string const& description, boost::gregorian::date const& start, QWidget* parent = nullptr);
        ~Chain_Widget() override;

    signals:

    public slots:

    private:
        Chain_Data m_data;
        QUptr<QLabel> m_description_label;
        QUptr<QVBoxLayout> m_layout;
        QUptr<Chain_Table_Model> m_model;
        QUptr<Chain_Tableview> m_tableview;
    };

} // namespace Chain

#endif // CHAIN_WIDGET_H