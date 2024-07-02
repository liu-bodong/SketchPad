#pragma once
#include "ShapeBase.h"

class TextItem :
    public ShapeBase
{
public:
    TextItem() = default;
    ~TextItem() = default;

    void Paint(QPainter&) override;

    bool Selectable(QPointF) const override;
    bool Transform(QPoint) override;
    void Serialize(QDataStream&) const override;
    void Deserialize(QDataStream&) override;

    TextItem* Clone() const final;

    QPointF GetCenter() const { return m_center; }
    QString GetText() const { return m_text; }

    void SetCenter(QPointF pt) { m_center = pt; }
    void SetText(const QString& text) { m_text = text; }

    QString GetType() override { return "Text"; }

private:
    QPointF m_center;
    QString m_text = "Text";

    static int m_idGenerator;
    int id;

    std::string Name() override { return "Text"; }
    int Id() override { return id; }

};

