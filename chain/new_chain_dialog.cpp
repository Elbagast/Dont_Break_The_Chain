#include "new_chain_dialog.h"
#include "ui_new_chain_dialog.h"

Chain::New_Chain_Dialog::New_Chain_Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(std::make_unique<Ui::New_Chain_Dialog>())
{
    m_ui->setupUi(this);

    this->setWindowTitle("New Chain");

    // can't start a chain after today
    m_ui->date_calender->setMaximumDate(QDate::currentDate());
    m_ui->date_calender->setSelectedDate(QDate::currentDate());
}

Chain::New_Chain_Dialog::~New_Chain_Dialog() = default;

QString Chain::New_Chain_Dialog::title() const
{
    return m_ui->title_line_edit->text();
}

QString Chain::New_Chain_Dialog::description() const
{
    return m_ui->desc_text_edit->toPlainText();
}

QColor Chain::New_Chain_Dialog::colour() const
{
    return QColor(m_ui->colour_r_spinbox->value(), m_ui->colour_g_spinbox->value(), m_ui->colour_b_spinbox->value());
}

QDate Chain::New_Chain_Dialog::date() const
{
    return m_ui->date_calender->selectedDate();
}

