#include "TextCommand.h"
#include "Canvas.h"
#include "History.h"
#include "MainWindow.h"

void TextCommand::Execute()
{
    auto pMW = MainWindow::GetInstance();
    auto pEditor = pMW->GetEditor();

    bool isFirstSave = m_pHistory->IsUndoEmpty();

    auto center = m_points[1];

    auto text = new TextItem();
    text->SetCenter(center);
    text->SetText(pMW->GetText());
    text->SetFont(pEditor->GetFont());

    if (isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
        isFirstSave = false;
    }

    text->SetPen(pEditor->GetPen());

    m_pCanvas->AddShape(text);

    if (!isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
    }
}

void TextCommand::TempExecute()
{
    if (m_pTempText == nullptr)
    {
        m_pTempText = new TextItem();
    }

    if (m_tempShapes.empty())
    {
        m_tempShapes.push_back(m_pTempText);
    }

    m_pTempText->SetCenter(m_tempPoints[1]);
}