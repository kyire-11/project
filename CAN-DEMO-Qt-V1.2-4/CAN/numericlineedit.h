// numericlineedit.h
#ifndef NUMERICLINEEDIT_H
#define NUMERICLINEEDIT_H

#include <QLineEdit>
#include <QIntValidator>
#include <QMessageBox>

class NumericLineEdit : public QLineEdit {
    Q_OBJECT
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)

public:
    explicit NumericLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {
        init(0, 1000); // 默认范围
    }

    // 带参数的构造函数，方便代码中直接指定范围
    explicit NumericLineEdit(int min, int max, QWidget *parent = nullptr) : QLineEdit(parent) {
        init(min, max);
    }

    int minimum() const { return m_validator->bottom(); }
    int maximum() const { return m_validator->top(); }

public slots:
    void setMinimum(int min) {
        m_validator->setRange(min, qMax(min, maximum()));
        validateInput(); // 立即验证当前内容
    }

    void setMaximum(int max) {
        m_validator->setRange(qMin(minimum(), max), max);
        validateInput(); // 立即验证当前内容
    }

    void setRange(int min, int max) {
        m_validator->setRange(min, max);
        validateInput(); // 立即验证当前内容
    }

private slots:
    void validateInput() {
        QString text = this->text();
        bool ok;
        int value = text.toInt(&ok);

        if (ok && value >= minimum() && value <= maximum()) {
            // setStyleSheet(""); // 清除错误样式
        } else {
            // setStyleSheet("border: 1px solid red"); // 错误样式
            clear(); // 清除无效输入
        }
    }

private:
    QIntValidator* m_validator;

    void init(int min, int max) {
        m_validator = new QIntValidator(min, max, this);
        setValidator(m_validator);

        // 连接信号槽
        // connect(this, &QLineEdit::editingFinished, this, &NumericLineEdit::validateInput);
        connect(this, &QLineEdit::textChanged, this, [this]() {
            QString text = this->text();
            if (text.isEmpty()) {
                return;
            }
            bool ok;
            int value = text.toInt(&ok);

            if ( value < minimum() ||value > maximum()) {
                clear();
                QMessageBox::warning(this,"提示","请输入范围内的数字");

            }
        });
    }
};

#endif // NUMERICLINEEDIT_H
