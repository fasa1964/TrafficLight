
#include "classarduinoboard.h"


#include <QSerialPortInfo>

#include <QDebug>

ClassArduinoBoard::ClassArduinoBoard(QObject *parent)
    : QObject{parent}
{
    // Initialize the serial port
    arduino = new QSerialPort();

    // Set presettings when starting this app
    setIsWriteable(false);
    setIsAvailable(false);

}

ClassArduinoBoard::~ClassArduinoBoard()
{
    if(arduino->isOpen())
        arduino->close();
}

void ClassArduinoBoard::checkAvailableBoards()
{
    //qDebug() << "Check for arduino board";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        qDebug() << info.portName();
//        qDebug() << info.systemLocation();
//        qDebug() << info.manufacturer();
//        qDebug() << info.serialNumber();
//        qDebug() << "Description: " << info.description();

        if(info.hasProductIdentifier() && info.hasVendorIdentifier())
            setIsAvailable(true);
        else
            setIsAvailable(false);

        if(isAvailable()){

            // Update the properties for qml
            setPortName(  info.portName() );
            setBoardManufacturer( info.manufacturer() );
            setBoardDescription( info.description() );
            if(info.hasVendorIdentifier())
                setVendorID(  QString("%1").arg( info.vendorIdentifier() ) );

            if(info.hasProductIdentifier())
                setProductID(  QString("%1").arg( info.productIdentifier() )  );

            // Setup the serial port -> arduino
            arduino->setPortName( info.portName() );
            arduino->open(QSerialPort::WriteOnly);
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);

            setIsWriteable( arduino->isWritable() );

        }

//        if(info.hasVendorIdentifier()){
//            qDebug() << "Vendor-ID" << QByteArray::number(info.vendorIdentifier(),16);
//        }else{
//            qDebug() << "Vendor-ID" << QByteArray();
//        }

//        if(info.hasProductIdentifier()){
//            qDebug() << "Product-ID" << QByteArray::number(info.productIdentifier(),16);
//        }else{
//            qDebug() << "Product-ID" << QByteArray();
//        }

    }
}

void ClassArduinoBoard::setCommand(const QString &command)
{
    if(arduino->isWritable()){

        arduino->write( command.toStdString().c_str()  );

    }
//    qDebug() << command;
}


// Properties for QML
// -----------------------------------------
bool ClassArduinoBoard::isAvailable() const
{
    return m_isAvailable;
}

void ClassArduinoBoard::setIsAvailable(bool newIsAvailable)
{
    if (m_isAvailable == newIsAvailable)
        return;
    m_isAvailable = newIsAvailable;
    emit isAvailableChanged();
}

QString ClassArduinoBoard::boardName() const
{
    return m_boardName;
}

void ClassArduinoBoard::setBoardName(const QString &newBoardName)
{
    if (m_boardName == newBoardName)
        return;
    m_boardName = newBoardName;
    emit boardNameChanged();
}

QString ClassArduinoBoard::boardDescription() const
{
    return m_boardDescription;
}

void ClassArduinoBoard::setBoardDescription(const QString &newBoardDescription)
{
    if (m_boardDescription == newBoardDescription)
        return;
    m_boardDescription = newBoardDescription;
    emit boardDescriptionChanged();
}

QString ClassArduinoBoard::boardManufacturer() const
{
    return m_boardManufacturer;
}

void ClassArduinoBoard::setBoardManufacturer(const QString &newBoardManufacturer)
{
    if (m_boardManufacturer == newBoardManufacturer)
        return;
    m_boardManufacturer = newBoardManufacturer;
    emit boardManufacturerChanged();
}

QString ClassArduinoBoard::portName() const
{
    return m_portName;
}

void ClassArduinoBoard::setPortName(const QString &newPortName)
{
    if (m_portName == newPortName)
        return;
    m_portName = newPortName;
    emit portNameChanged();
}

QString ClassArduinoBoard::vendorID() const
{
    return m_vendorID;
}

void ClassArduinoBoard::setVendorID(const QString &newVendorID)
{
    if (m_vendorID == newVendorID)
        return;
    m_vendorID = newVendorID;
    emit vendorIDChanged();
}

QString ClassArduinoBoard::productID() const
{
    return m_productID;
}

void ClassArduinoBoard::setProductID(const QString &newProductID)
{
    if (m_productID == newProductID)
        return;
    m_productID = newProductID;
    emit productIDChanged();
}

QString ClassArduinoBoard::serialNumber() const
{
    return m_serialNumber;
}

void ClassArduinoBoard::setSerialNumber(const QString &newSerialNumber)
{
    if (m_serialNumber == newSerialNumber)
        return;
    m_serialNumber = newSerialNumber;
    emit serialNumberChanged();
}

bool ClassArduinoBoard::isWriteable() const
{
    return m_isWriteable;
}

void ClassArduinoBoard::setIsWriteable(bool newIsWriteable)
{
    if (m_isWriteable == newIsWriteable)
        return;
    m_isWriteable = newIsWriteable;
    emit isWriteableChanged();
}
//!------------------------------------------
