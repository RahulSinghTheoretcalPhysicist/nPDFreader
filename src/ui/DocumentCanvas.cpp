#include "DocumentCanvas.h"

#include <QFileInfo>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>

DocumentCanvas::DocumentCanvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(640, 420);
    setAutoFillBackground(false);
    setFocusPolicy(Qt::StrongFocus);
}

void DocumentCanvas::setOpenedFile(const QString &filePath)
{
    m_filePath = filePath;
    update();
}

void DocumentCanvas::clearDocument()
{
    m_filePath.clear();
    update();
}

void DocumentCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QColor workspaceColor(42, 44, 48);
    const QColor pageColor(250, 250, 250);
    const QColor borderColor(155, 155, 155);
    const QColor primaryText(45, 45, 45);
    const QColor secondaryText(105, 105, 105);

    painter.fillRect(rect(), workspaceColor);

    const int margin = 48;
    const int availableWidth = qMax(100, width() - margin * 2);
    const int availableHeight = qMax(100, height() - margin * 2);

    // A4-like placeholder page. Real PDF page geometry arrives in Phase 2.
    constexpr double a4Aspect = 595.0 / 842.0;

    int pageHeight = qMin(availableHeight, 900);
    int pageWidth = static_cast<int>(pageHeight * a4Aspect);

    if (pageWidth > availableWidth) {
        pageWidth = availableWidth;
        pageHeight = static_cast<int>(pageWidth / a4Aspect);
    }

    const QRect pageRect(
        (width() - pageWidth) / 2,
        (height() - pageHeight) / 2,
        pageWidth,
        pageHeight
    );

    // Small shadow gives the document area visual separation without a heavy UI.
    painter.fillRect(pageRect.translated(5, 7), QColor(0, 0, 0, 80));
    painter.fillRect(pageRect, pageColor);
    painter.setPen(QPen(borderColor, 1));
    painter.drawRect(pageRect.adjusted(0, 0, -1, -1));

    painter.setPen(primaryText);
    QFont titleFont = font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    painter.setFont(titleFont);

    QString title = "PDF Reader";
    if (!m_filePath.isEmpty()) {
        title = QFileInfo(m_filePath).fileName();
    }

    QRect titleRect = pageRect.adjusted(36, 48, -36, -48);
    painter.drawText(titleRect, Qt::AlignHCenter | Qt::AlignTop, title);

    painter.setPen(secondaryText);
    QFont bodyFont = font();
    bodyFont.setPointSize(10);
    painter.setFont(bodyFont);

    const QString message = m_filePath.isEmpty()
        ? QStringLiteral("Open a PDF to begin.\n\nPhase 1: application shell and Windows build pipeline are active.")
        : QStringLiteral(
              "The file has been selected successfully.\n\n"
              "PDF rendering is intentionally not faked in this phase. "
              "Phase 2 will connect this viewport to PDFium and render the actual first page."
          );

    QRect messageRect = pageRect.adjusted(58, 115, -58, -70);
    painter.drawText(messageRect,
                     Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap,
                     message);
}
