#include "chain_widget.h"

#include "chain_table_model.h"
#include "chain_tableview.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QtDebug>

Chain::Chain_Widget::Chain_Widget(std::string const& title, std::string const& description, boost::gregorian::date const& start, QWidget* parent) :
    QGroupBox(title.c_str(), parent),
    m_data(title, description, start),
    m_description_label(make_quptr<QLabel>(description.c_str())),
    m_layout(make_quptr<QVBoxLayout>()),
    m_model(make_quptr<Chain_Table_Model>(m_data)),
    m_tableview(make_quptr<Chain_Tableview>())
{
    // build widgets for the chain
    assert(m_data.day_count() >= 1);
    m_layout->addWidget(m_description_label.get());

    m_tableview->setModel(m_model.get());
    m_tableview->resizeRowsToContents();
    m_tableview->resizeColumnsToContents();

    m_layout->addWidget(m_tableview.get());

    setLayout(m_layout.get());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

Chain::Chain_Widget::~Chain_Widget() = default;

