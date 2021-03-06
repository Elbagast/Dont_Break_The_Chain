#include "new_chain_dialog.h"
#include "ui_new_chain_dialog.h"
#include <QColorDialog>

// Special 6
//============================================================
Chain::New_Chain_Dialog::New_Chain_Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(std::make_unique<Ui::New_Chain_Dialog>()),
    m_colour()
{
    m_ui->setupUi(this);

    this->setWindowTitle("New Chain");

    // can't start a chain after today
    m_ui->date_calender->setMaximumDate(QDate::currentDate());
    m_ui->date_calender->setSelectedDate(QDate::currentDate());

    QObject::connect(m_ui->colour_pick_button, &QPushButton::clicked,
                     this, &New_Chain_Dialog::slot_pick_colour);

    QObject::connect(m_ui->colour_red_spinbox, &QSpinBox::editingFinished,
                     [this](){ this->slot_set_colour_red_level(this->m_ui->colour_red_spinbox->value()); });
    QObject::connect(m_ui->colour_green_spinbox, &QSpinBox::editingFinished,
                     [this](){ this->slot_set_colour_green_level(this->m_ui->colour_green_spinbox->value()); });
    QObject::connect(m_ui->colour_blue_spinbox, &QSpinBox::editingFinished,
                     [this](){ this->slot_set_colour_blue_level(this->m_ui->colour_blue_spinbox->value()); });

    QObject::connect(m_ui->title_line_edit, &QLineEdit::textChanged,
                     [this](){ this->update_title_error(); });

    update_colour_display();
    update_title_error();
}

Chain::New_Chain_Dialog::~New_Chain_Dialog() = default;

// Interface
//============================================================
bool Chain::New_Chain_Dialog::has_valid_selections() const
{
    return !title().isEmpty()
            //&& !description().isEmpty()
            //&& colour().isValid()
            && colour() != QColor(255,255,255) // don't want a white chain
            && !(date() > QDate::currentDate());
}

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
    return m_colour;
}

QDate Chain::New_Chain_Dialog::date() const
{
    return m_ui->date_calender->selectedDate();
}

void Chain::New_Chain_Dialog::slot_pick_colour()
{
    QColorDialog colour_picker{this};
    colour_picker.setCurrentColor(colour());
    if (colour_picker.exec() == QDialog::Accepted)
    {
        slot_set_colour(colour_picker.selectedColor());
    }
}

void Chain::New_Chain_Dialog::slot_set_colour(QColor colour)
{
    m_colour = colour;
    m_ui->colour_red_spinbox->setValue(m_colour.red());
    m_ui->colour_green_spinbox->setValue(m_colour.green());
    m_ui->colour_blue_spinbox->setValue(m_colour.blue());
    update_colour_display();
}

void Chain::New_Chain_Dialog::slot_set_colour_red_level(int red)
{
    m_colour.setRed(red);
    update_colour_display();
}

void Chain::New_Chain_Dialog::slot_set_colour_green_level(int green)
{
    m_colour.setGreen(green);
    update_colour_display();
}

void Chain::New_Chain_Dialog::slot_set_colour_blue_level(int blue)
{
    m_colour.setBlue(blue);
    update_colour_display();
}

// Helpers
//============================================================
// Whenever the selected colour changes, update the widget that displays it
void Chain::New_Chain_Dialog::update_colour_display()
{
    m_ui->colour_display_widget;

    QPalette palette{m_ui->colour_display_widget->palette()};
    palette.setColor(m_ui->colour_display_widget->backgroundRole(), m_colour);
    m_ui->colour_display_widget->setPalette(palette);
    m_ui->colour_display_widget->setAutoFillBackground(true);

    update_colour_error();
}

// Determine if the current colour is valid
void Chain::New_Chain_Dialog::update_colour_error()
{
    bool ok_enabled{false};

    // Check that the colour is valid
    if (m_colour == QColor(255,255,255) || m_colour == QColor(200,200,200))
    {
        m_ui->colour_error_label->show();
        ok_enabled = false;
    }
    else
    {
        m_ui->colour_error_label->hide();
        ok_enabled = true;
    }

    update_ok_enabled(ok_enabled);
}

// Determine if the title is valid
void Chain::New_Chain_Dialog::update_title_error()
{
    bool ok_enabled{false};

    // Check that the title has been set
    if (m_ui->title_line_edit->text().isEmpty())
    {
        m_ui->title_error_label->show();
        ok_enabled = false;
    }
    else
    {
        m_ui->title_error_label->hide();
        ok_enabled = true;
    }

    update_ok_enabled(ok_enabled);
}

// Set whether the OK button is enabled
void Chain::New_Chain_Dialog::update_ok_enabled(bool state)
{
    m_ui->button_box->button(QDialogButtonBox::Ok)->setEnabled(state);
}
