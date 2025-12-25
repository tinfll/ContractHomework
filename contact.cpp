#include "contact.h"
#include <QDebug>

bool Contact::parseFromString(const QString &line){

    //字符串切分可查手册！！！
    //
    QStringList parts = line.split(' ', Qt::SkipEmptyParts);

    if(parts.size() < 7){
        qWarning() << "联系人数据格式错误:" << line;
        return false;
    }

    bool ok;
    id = parts[0].toInt(&ok);
    if(!ok){
        qWarning() << "相位错误..." << parts[0];
        return false;
    }

    name = parts[1];
    gender = parts[2];
    age = parts[3];
    phone = parts[4];
    city = parts[5];
    company = parts[6];
    // 处理标签（可能有多个标签，用空格分隔）
    tags.clear();
    //切割....
    for (int i = 7; i < parts.size(); i++) {
        tags.append(parts[i]);
    }
    return true;
}

QString Contact::toString() const{
    QString result = QString("%1 %2 %3 %4 %5 %6 %7")
                         .arg(id)
                         .arg(name)
                         .arg(gender)
                         .arg(age)
                         .arg(phone)
                         .arg(city)
                         .arg(company);

    if (!tags.isEmpty()) {
        result += " " + tags.join(" ");
    }

    return result;
}

QString Contact::getShortInfo() const
{
    return QString("%1. %2").arg(id).arg(name);
}
