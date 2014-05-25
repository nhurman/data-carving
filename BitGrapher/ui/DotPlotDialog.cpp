#include "ui/DotPlotDialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DotPlotResult* DotPlotDialog::m_result;

DotPlotDialog::DotPlotDialog(QWidget *parent, DumpSet* ds, QString* selectedDump) :
    QDialog(parent), m_dumpSet(ds), m_selectedDump(selectedDump)
{
    setWindowTitle("DotPlot");

    m_layout = new QVBoxLayout;
    setLayout(m_layout);

    //min size
    QHBoxLayout* sLayout = new QHBoxLayout;
    sLayout->addWidget(new QLabel("Minimum string size : "));
    sLayout->addWidget(m_minSizeSpinBox = new QSpinBox(this));
    m_minSizeSpinBox->setMinimum(1);
    m_layout->addLayout(sLayout);

    QPushButton* defaultButton = new QPushButton("Default", this);
    sLayout->addWidget(defaultButton);
    QObject::connect(defaultButton, SIGNAL( clicked() ),
                          this, SLOT( displayDefaultSize() ));

    //dumps
    m_dumpCBs.push_back(new DumpComboBox(this));
    m_dumpCBs.push_back(new DumpComboBox(this, 1));
    m_layout->addWidget(m_dumpCBs[0]);
    m_layout->addWidget(m_dumpCBs[1]);

    QObject::connect(m_dumpCBs[0], SIGNAL(currentDumpChanged( int ) ),
                          this, SLOT(refreshComboBoxes( int )));
    QObject::connect(m_dumpCBs[1], SIGNAL(currentDumpChanged( int ) ),
                          this, SLOT(refreshComboBoxes( int )));

    //ok cancel
    QHBoxLayout* bLayout = new QHBoxLayout;
    m_layout->addLayout(bLayout);

    QPushButton* bOK = new QPushButton("OK");
    QPushButton* bCancel = new QPushButton("Cancel");
    bLayout->addWidget(bOK);
    bLayout->addWidget(bCancel);
    bOK->setDefault(true); //when you hit enter, this button is pressed

    QObject::connect(bOK, SIGNAL(clicked()),
                          this, SLOT(processAndClose()));
    QObject::connect(bCancel, SIGNAL(clicked()),
                          this, SLOT(cancelAndClose()));

    refreshComboBoxes(-1);
}

Dump DotPlotDialog::getDump(int index)
{
    return *m_dumpSet->find((m_dumpCBs[index]->currentText()).toStdString());
}

int DotPlotDialog::getMinSize() const
{
    return m_minSizeSpinBox->value();
}

DotPlotResult* DotPlotDialog::getResult() const
{
    return m_result;
}

void DotPlotDialog::refreshComboBoxes(int modifiedIndex)
{
    if(modifiedIndex <= 0)
        if(m_selectedDump != NULL)
            *m_selectedDump = m_dumpCBs[0]->currentText();

    for(unsigned int i = modifiedIndex+1; i < m_dumpCBs.size(); i++)
    {
        refreshComboBox(i);
    }
}

void DotPlotDialog::refreshComboBox(int index)
{
    QString selection = m_dumpCBs[index]->currentText();
    std::vector<std::string> dumpsVect = m_dumpSet->getDumpNames();
    QStringList dumps;
    for(unsigned int i = 0; i < dumpsVect.size(); i++) //std::list to QStringList
    {
        dumps.push_back(QString::fromStdString(dumpsVect.at(i)));
    }

    m_dumpCBs[index]->clear();
    m_dumpCBs[index]->addItems(dumps);

    //puts the selection back if possible
    int i = m_dumpCBs[index]->findText(selection);
    if ( i != -1 ) // -1 for not found
        m_dumpCBs[index]->setCurrentIndex(i);
    else
        m_dumpCBs[index]->setCurrentIndex(0);

}

void DotPlotDialog::processAndClose()
{
    std::vector<Dump> v;
    for(unsigned int i = 0; i < m_dumpCBs.size(); i++)
        v.push_back(getDump(i));

    m_result = new DotPlotResult(v.at(0), v.at(1), m_minSizeSpinBox->value());
    done(0);
}

void DotPlotDialog::cancelAndClose()
{
    m_result = NULL;
    done(0);
}

/*Similarities* DotPlotDialog::getSimilarities(DumpSet* ds, QString* selectedDump)
{
    SimilaritesDialog dialog(0, ds, selectedDump);
    dialog.exec();
    Similarities* res = m_result;
    m_result = NULL;
    return res;
}*/

int DotPlotDialog::preferredStringSize()
{
    std::list<int> sizes;
    for(unsigned int i = 0; i < m_dumpCBs.size(); i++)
    {
        sizes.push_back(getDump(i).getSize());
    }

    int s = MIN_DIAG_SIZE;
    if(s > 0)
        return s;
    return 1;
}

void DotPlotDialog::displayDefaultSize()
{
    m_minSizeSpinBox->setValue(preferredStringSize());
}
