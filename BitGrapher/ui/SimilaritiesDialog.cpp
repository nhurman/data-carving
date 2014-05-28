#include "ui/SimilaritiesDialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

Similarities* SimilaritiesDialog::m_result;

SimilaritiesDialog::SimilaritiesDialog(QWidget *parent, DumpSet* ds, Dump const* selectedDump) :
    QDialog(parent), m_selectedDump(selectedDump), m_dumpSet(ds)
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
    m_dumpCBs.push_back(new DumpComboBox(this));
    m_layout->addWidget(m_dumpCBs[0]);
    m_layout->addWidget(m_dumpCBs[1]);

    QObject::connect(m_dumpCBs[0], SIGNAL(currentIndexChanged( int ) ),
                          this, SLOT(refreshComboBoxes( int )));
    QObject::connect(m_dumpCBs[1], SIGNAL(currentIndexChanged( int ) ),
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

Dump SimilaritiesDialog::getDump(const int index) const
{
    return *m_dumpSet->find(m_dumpCBs[index]->currentText().toUtf8().constData());
}

int SimilaritiesDialog::getMinSize() const
{
    return m_minSizeSpinBox->value();
}

void SimilaritiesDialog::refreshComboBoxes(int modifiedIndex)
{
    if(modifiedIndex <= 0)
        if(m_selectedDump != NULL)
            m_selectedDump = m_dumpCBs[0]->currentDump();

    for(unsigned int i = modifiedIndex+1; i < m_dumpCBs.size(); i++)
    {
        bool oldState = m_dumpCBs[i]->blockSignals(true);
        refreshComboBox(i);
        m_dumpCBs[i]->blockSignals(oldState);
    }
}

void SimilaritiesDialog::refreshComboBox(const int index)
{
    std::vector<Dump const*> dumpsVect = m_dumpSet->getDumpList();
    for(int i = 0; i < index; i++) //removing dumps selected in the boxes above
    {
        std::vector<Dump const*>::iterator it = std::find(dumpsVect.begin(), dumpsVect.end(), m_dumpCBs[i]->currentDump());
        if( it != dumpsVect.end())
            dumpsVect.erase(it);
    }

    m_dumpCBs[index]->setDumpList(dumpsVect);
}

void SimilaritiesDialog::addComboBox()
{
    if(m_dumpCBs.size() >= m_dumpSet->size()) //not enough dumps
    {
        return;
    }
    //else
    m_dumpCBs.push_back(new DumpComboBox(this));
    m_layout->insertWidget(m_layout->count()-1, m_dumpCBs.back());

    QObject::connect(m_dumpCBs.back(), SIGNAL(currentIndexChanged( int ) ),
                          this, SLOT(refreshComboBoxes( int )));

    refreshComboBox(m_dumpCBs.size()-1);
}

void SimilaritiesDialog::removeComboBox()
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

void SimilaritiesDialog::processAndClose()
{
    std::vector<Dump> v;
    for(unsigned int i = 0; i < m_dumpCBs.size(); i++)
        v.push_back(getDump(i));

    m_result = new Similarities(v, getMinSize());
    done(0);
}

void SimilaritiesDialog::cancelAndClose()
{
    m_result = NULL; //probably useless now
    done(0);
}

Similarities* SimilaritiesDialog::getSimilarities(DumpSet* ds, const Dump *selectedDump)
{
    SimilaritiesDialog dialog(0, ds, selectedDump);
    dialog.exec();
    Similarities* res = m_result;
    m_result = NULL;
    return res;
}

int SimilaritiesDialog::preferredStringSize() const
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

void SimilaritiesDialog::displayDefaultSize()
{
    m_minSizeSpinBox->setValue(preferredStringSize());
}
