#include "similaritesdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

Similarities* SimilaritesDialog::m_result;

SimilaritesDialog::SimilaritesDialog(QWidget *parent, DumpSet* ds, QString* selectedDump) :
    QDialog(parent), m_dumpSet(ds), m_selectedDump(selectedDump)
{
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    m_dump1CB = new QComboBox(this);
    m_dump2CB = new QComboBox(this);
    layout->addWidget(m_dump1CB);
    layout->addWidget(m_dump2CB);

    QHBoxLayout* sLayout = new QHBoxLayout;
    sLayout->addWidget(new QLabel("Minimum string size : "));
    sLayout->addWidget(m_minSizeSpinBox = new QSpinBox(this));
    layout->addLayout(sLayout);

    QObject::connect(m_dump1CB, SIGNAL(currentIndexChanged( QString ) ),
                          this, SLOT(refreshDumps2( QString )));

    QHBoxLayout* bLayout = new QHBoxLayout;
    layout->addLayout(bLayout);

    QPushButton* bOK = new QPushButton("OK");
    QPushButton* bCancel = new QPushButton("Cancel");
    bLayout->addWidget(bOK);
    bLayout->addWidget(bCancel);

    QObject::connect(bOK, SIGNAL(clicked()),
                          this, SLOT(processAndClose()));
    QObject::connect(bCancel, SIGNAL(clicked()),
                          this, SLOT(cancelAndClose()));

    refreshDumps1();
    //refreshDumps2(); //done thanks to the signal
}

Dump SimilaritesDialog::getDump1()
{
    return *m_dumpSet->find(m_dump1CB->currentText());
}
Dump SimilaritesDialog::getDump2()
{
    return *m_dumpSet->find(m_dump2CB->currentText());
}
int SimilaritesDialog::getMinSize()
{
    return m_minSizeSpinBox->value();
}

void SimilaritesDialog::refreshDumps1()
{
    QString selection = m_dump1CB->currentText();
    std::vector<QString> dumpsVect = m_dumpSet->getDumpNames();
    QStringList dumps;
    for(unsigned int i = 0; i < dumpsVect.size(); i++)
    {
        dumps.push_back(dumpsVect.at(i));
    }

    m_dump1CB->clear();
    m_dump1CB->addItems(dumps);

    //puts the selection back if possible
    int index = m_dump1CB->findData(selection);
    if ( index != -1 ) // -1 for not found
       m_dump1CB->setCurrentIndex(index);
    else
        m_dump1CB->setCurrentIndex(0);

}

void SimilaritesDialog::refreshDumps2(const QString dump1)
{
    QString selection = m_dump2CB->currentText();
    std::vector<QString> dumpsVect = m_dumpSet->getDumpNames();
    QStringList dumps;
    for(unsigned int i = 0; i < dumpsVect.size(); i++)
    {
        dumps.push_back(dumpsVect.at(i));
    }
    if(dump1 != "")
        dumps.removeOne(dump1);

    m_dump2CB->clear();
    m_dump2CB->addItems(dumps);

    //puts the selection back if possible
    int index = m_dump2CB->findData(selection);
    if ( index != -1 ) // -1 for not found
       m_dump2CB->setCurrentIndex(index);
    else
        m_dump2CB->setCurrentIndex(0);

    if(m_selectedDump != NULL)
        *m_selectedDump = dump1;
}

void SimilaritesDialog::processAndClose()
{
    std::vector<Dump> v;
    v.push_back(getDump1());
    v.push_back(getDump2());
    m_result = new Similarities(v, getMinSize());
    done(0);
}

void SimilaritesDialog::cancelAndClose()
{
    m_result = NULL; //probably useless now
    done(0);
}

Similarities* SimilaritesDialog::getSimilarities(DumpSet* ds, QString* selectedDump)
{
    SimilaritesDialog dialog(0, ds, selectedDump);
    dialog.exec();
    Similarities* res = m_result;
    m_result = NULL;
    return res;
}
