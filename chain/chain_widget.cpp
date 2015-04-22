#include "chain_widget.h"

#include "chain_table_model.h"
#include "chain_tableview.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QtDebug>

Chain::Chain_Widget::Chain_Widget(QString const& title,
                                  QString const& description,
                                  QColor colour,
                                  QDate start,
                                  QList<bool> const& data,
                                  QWidget* parent) :
    Chain_Widget(Chain_Data(title, description, colour, start, data), parent)
{
}


Chain::Chain_Widget::Chain_Widget(Chain_Data && data, QWidget* parent) :
    QGroupBox(data.title(), parent),
    m_data(std::move(data)),
    m_description_label(make_quptr<QLabel>(m_data.description())),
    m_layout(make_quptr<QVBoxLayout>()),
    m_model(make_quptr<Chain_Table_Model>(m_data)),
    m_tableview(make_quptr<Chain_Tableview>())
{
    // build widgets for the chain
    m_layout->addWidget(m_description_label.get());

    m_tableview->setModel(m_model.get());
    m_tableview->resizeRowsToContents();
    m_tableview->resizeColumnsToContents();

    m_layout->addWidget(m_tableview.get());

    setLayout(m_layout.get());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

Chain::Chain_Widget::~Chain_Widget() = default;

Chain::Chain_Data const& Chain::Chain_Widget::data() const
{
    return m_data;
}
