#include "parsetext.h"
#define MIN(a, b) (a < b) ? a : b

ParseText::ParseText()
{
    text = "";
    preText = "";
    pos = 0;
}

bool ParseText::change(QString istr)
{
    qint32 length = MIN(MIN(text.length(), istr.length()), pos);
    preText = "";
    for (qint32 i = 0; i < length; i++)
        {
            if (text[i] != istr[i])
                {
                    pos = i;
                    break;
                }
        }

    const QChar *arStr = istr.constData();
    qint32 ppos = 0, lastp = -1;
    bool chg = false;

    for (
            qint32 fnd = istr.indexOf("#@", pos);
            fnd != -1 && lastp != pos;
            fnd = istr.indexOf("#@", pos)
        )
            {
                preText.insert(preText.length(), &arStr[ppos], fnd);
                lastp = pos;
                pos = fnd;
                int r = istr.indexOf(';', fnd);
                int space = istr.indexOf(' ', fnd);
                if ((r < space || space == -1) && r != -1)
                    {
                        QString exampl = "";
                        exampl.insert(0, &arStr[fnd + 2], r - fnd - 2);
                        QString rez = calc(exampl);
                        preText += rez;
                        pos = r + 1;
                        chg = true;
                    }

                preText.insert(preText.length(), &arStr[pos], istr.length() - pos);
            }
    return chg;
}

QString ParseText::calc(QString example)
{
    QString str = example;

    str.replace("rub", "\u20BD");
    str.replace("coryright", "\u00A9");
    str.replace("euro", "\u20AC");
    str.replace("dollar", "\u0024");
    str.replace("promille", "\u2030");

    return str;
}

QString ParseText::getText()
{
    text = preText;
    return text;
}
