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

    class New_Chain_Dialog :
            public QDialog
    {
        Q_OBJECT

    public:
        explicit New_Chain_Dialog(QWidget *parent = 0);
        ~New_Chain_Dialog() override;

        QString title() const;
        QString description() const;
        QColor colour() const;
        QDate date() const;

    private:
        std::unique_ptr<Ui::New_Chain_Dialog> m_ui;
    };

} // namespace Chain

#endif // NEW_CHAIN_DIALOG_H
