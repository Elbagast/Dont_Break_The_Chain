#ifndef NEW_CHAIN_DIALOG_H
#define NEW_CHAIN_DIALOG_H

#include <QDialog>
#include <memory>

namespace Ui
{
    class New_Chain_Dialog;
}

namespace Chain
{
    /*
    New_Chain_Dialog
    ====================================================================================================
    Dialog to setup a new chain.

    It takes a while to load the first time...?
    */
    class New_Chain_Dialog :
            public QDialog
    {
        Q_OBJECT

    public:
        explicit New_Chain_Dialog(QWidget *parent = 0);
        ~New_Chain_Dialog() override;

        bool has_valid_selections() const;

        QString title() const;
        QString description() const;
        QColor colour() const;
        QDate date() const;

    private slots:
        void slot_pick_colour();
        void slot_set_colour(QColor colour);
        void slot_set_colour_red_level(int red);
        void slot_set_colour_green_level(int green);
        void slot_set_colour_blue_level(int blue);

    private:
        void update_colour_display();

        std::unique_ptr<Ui::New_Chain_Dialog> m_ui;

        QColor m_colour;
    };

} // namespace Chain

#endif // NEW_CHAIN_DIALOG_H
