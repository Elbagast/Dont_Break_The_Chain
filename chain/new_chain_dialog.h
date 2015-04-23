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
    QDialog to collect user inputs to create a new chain.

    It takes a while to load the first time...?
    */
    class New_Chain_Dialog :
            public QDialog
    {
        Q_OBJECT

    public:
        // Special 6
        //============================================================
        explicit New_Chain_Dialog(QWidget *parent = 0);
        ~New_Chain_Dialog() override;

        // No copying
        New_Chain_Dialog(New_Chain_Dialog const& other) = delete;
        New_Chain_Dialog& operator=(New_Chain_Dialog const& other) = delete;

        // Implicit default move
        //New_Chain_Dialog(New_Chain_Dialog && other) = default;
        //New_Chain_Dialog& operator=(New_Chain_Dialog && other) = default;

        // Interface
        //============================================================
        // Allow access to the selected data

        bool has_valid_selections() const;

        QString title() const;
        QString description() const;
        QColor colour() const;
        QDate date() const;

    private slots:
        // Slots
        //============================================================
        // Connected to the colour input widgets

        void slot_pick_colour();
        void slot_set_colour(QColor colour);
        void slot_set_colour_red_level(int red);
        void slot_set_colour_green_level(int green);
        void slot_set_colour_blue_level(int blue);

    private:
        // Helpers
        //============================================================
        // Whenever the selected colour changes, update the widget that displays it
        void update_colour_display();

        // Determine if the current colour is valid
        void update_colour_error();

        // Determine if the title is valid
        void update_title_error();

        // Set whether the OK button is enabled
        void update_ok_enabled(bool state);

        // Data Members
        //============================================================
        std::unique_ptr<Ui::New_Chain_Dialog> m_ui;
        QColor m_colour;
    };

} // namespace Chain

#endif // NEW_CHAIN_DIALOG_H
