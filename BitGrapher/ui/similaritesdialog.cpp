#include "ui/similaritesdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

Similarities* SimilaritesDialog::m_result;

SimilaritesDialog::SimilaritesDialog(QWidget *parent, DumpSet* ds, QString* selectedDump) :
    QDialog(parent), m_dumpSet(ds), m_selectedDump(selectedDump)
{
    setWindowTitle("Similarities");

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

    //+  -
    QHBoxLayout* pmLayout = new QHBoxLayout;
    m_layout->addLayout(pmLayout);

    QPushButton* bPlus = new QPushButton("Add dump");
    QPushButton* bMinus = new QPushButton("Remove dump");
    pmLayout->addWidget(bPlus);
    pmLayout->addWidget(bMinus);

    QObject::connect(bPlus, SIGNAL(clicked()),
                          this, SLOT(addComboBox()));
    QObject::connect(bMinus, SIGNAL(clicked()),
                          this, SLOT(removeComboBox()));

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

Dump SimilaritesDialog::getDump(int index)
{
    return *m_dumpSet->find(m_dumpCBs[index]->currentText());
}

int SimilaritesDialog::getMinSize()
{
    return m_minSizeSpinBox->value();
}

void SimilaritesDialog::refreshComboBoxes(int modifiedIndex)
{
    if(modifiedIndex <= 0)
        if(m_selectedDump != NULL)
            *m_selectedDump = m_dumpCBs[0]->currentText();

    for(unsigned int i = modifiedIndex+1; i < m_dumpCBs.size(); i++)
    {
        refreshComboBox(i);
    }
}

void SimilaritesDialog::refreshComboBox(int index)
{
    QString selection = m_dumpCBs[index]->currentText();
    std::vector<QString> dumpsVect = m_dumpSet->getDumpNames();
    QStringList dumps;
    for(unsigned int i = 0; i < dumpsVect.size(); i++) //std::list to QStringList
    {
        dumps.push_back(dumpsVect.at(i));
    }
    for(int i = 0; i < index; i++) //removind dumps selected in the boxes above
    {
        dumps.removeOne(m_dumpCBs[i]->currentText());
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

void SimilaritesDialog::addComboBox()
{
    if(m_dumpCBs.size() >= m_dumpSet->getDumpCount()) //not enough dumps
    {
        return;
    }
    //else
    m_dumpCBs.push_back(new DumpComboBox(this, m_dumpCBs.size()));
    m_layout->insertWidget(m_layout->count()-1, m_dumpCBs.back());

    QObject::connect(m_dumpCBs.back(), SIGNAL(currentDumpChanged( int ) ),
                          this, SLOT(refreshComboBoxes( int )));

    refreshComboBox(m_dumpCBs.size()-1);
}

void SimilaritesDialog::removeComboBox()
{
    if(m_dumpCBs.size() <= 2) //you have to leave at least 2 dumps
    {
        return;
    }
    //else
    m_layout->removeWidget(m_dumpCBs.back());
    delete m_dumpCBs.back();
    m_dumpCBs.pop_back();
}

void SimilaritesDialog::processAndClose()
{
    std::vector<Dump> v;
    for(unsigned int i = 0; i < m_dumpCBs.size(); i++)
        v.push_back(getDump(i));

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

int SimilaritesDialog::preferredStringSize()
{
    std::list<int> sizes;
    for(unsigned int i = 0; i < m_dumpCBs.size(); i++)
    {
        sizes.push_back(getDump(i).getSize());
    }

    int s = Similarities::minStringSize(sizes);
    if(s > 0)
        return s;
    return 1;
}

void SimilaritesDialog::displayDefaultSize()
{
    m_minSizeSpinBox->setValue(preferredStringSize());
}
