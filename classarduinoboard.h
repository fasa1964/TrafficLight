
#ifndef CLASSARDUINOBOARD_H
#define CLASSARDUINOBOARD_H


#include <QObject>
#include <QQmlProperty>
#include <QSerialPort>

class ClassArduinoBoard : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isAvailable READ isAvailable WRITE setIsAvailable NOTIFY isAvailableChanged)
    Q_PROPERTY(QString boardName READ boardName WRITE setBoardName NOTIFY boardNameChanged)
    Q_PROPERTY(QString boardDescription READ boardDescription WRITE setBoardDescription NOTIFY boardDescriptionChanged)
    Q_PROPERTY(QString boardManufacturer READ boardManufacturer WRITE setBoardManufacturer NOTIFY boardManufacturerChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(QString vendorID READ vendorID WRITE setVendorID NOTIFY vendorIDChanged)
    Q_PROPERTY(QString productID READ productID WRITE setProductID NOTIFY productIDChanged)
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(bool isWriteable READ isWriteable WRITE setIsWriteable NOTIFY isWriteableChanged)

public:
    explicit ClassArduinoBoard(QObject *parent = nullptr);
    ~ClassArduinoBoard();
    Q_INVOKABLE void checkAvailableBoards();
    Q_INVOKABLE void setCommand(const QString &command);

    bool isAvailable() const;
    void setIsAvailable(bool newIsAvailable);

    QString boardName() const;
    void setBoardName(const QString &newBoardName);

    QString boardDescription() const;
    void setBoardDescription(const QString &newBoardDescription);

    QString boardManufacturer() const;
    void setBoardManufacturer(const QString &newBoardManufacturer);

    QString portName() const;
    void setPortName(const QString &newPortName);

    QString vendorID() const;
    void setVendorID(const QString &newVendorID);

    QString productID() const;
    void setProductID(const QString &newProductID);

    QString serialNumber() const;
    void setSerialNumber(const QString &newSerialNumber);

    bool isWriteable() const;
    void setIsWriteable(bool newIsWriteable);

signals:

    void isWriteableChanged();
    void isAvailableChanged();
    void boardNameChanged();
    void boardDescriptionChanged();
    void boardManufacturerChanged();
    void portNameChanged();
    void vendorIDChanged();
    void productIDChanged();
    void serialNumberChanged();

private:
    bool m_isAvailable;
    QString m_boardName;
    QString m_boardManufacturer;
    QString m_boardDescription;
    QString m_portName;
    QString m_vendorID;
    QString m_productID;
    QString m_serialNumber;

    QSerialPort *arduino;   // Pointer to serial port
    bool m_isWriteable;


};

#endif // CLASSARDUINOBOARD_H
