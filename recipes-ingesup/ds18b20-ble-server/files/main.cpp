#include <QCoreApplication>
#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
#include <QtCore/qtimer.h>

#include <QtEndian>
#include <QFile>

uint32_t float754tofloat11073(float value)
{
    uint8_t  exponent = 0xFE; //exponent is -2
    uint32_t mantissa = (uint32_t)(value * 100);

    return (((uint32_t)exponent) << 24) | mantissa;
}

QString readValueFromFile(QString filePath)
{
    QString data;
    QStringList response;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        response = data.split("t=");
        data.remove(data.length() - 1, 1);
        data = response.at(1);
        file.close();
    }

    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLowEnergyAdvertisingData advertisingData;                                              //serveur
    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);  //Mode d'accessibilité
    advertisingData.setLocalName("INGESUP : BLE on C.H.I.P");                                             //Nom du serveur
    advertisingData.setServices(QList<QBluetoothUuid>() <<
								QBluetoothUuid::HeartRate <<
                                QBluetoothUuid::HealthThermometer
                                );                         //Ajout des services prédéfinis
                                
     //Création de la caractéristique
    QLowEnergyCharacteristicData charData;
    //spécification de la caractéristique
    charData.setUuid(QBluetoothUuid::HeartRateMeasurement);
    charData.setValue(QByteArray(2, 0));
    //spécifique à la documentation bluetooth
    charData.setProperties(QLowEnergyCharacteristic::Notify);
    //Ajout d'un descripteur
    const QLowEnergyDescriptorData clientConfig(QBluetoothUuid::ClientCharacteristicConfiguration, QByteArray(2, 0));
    charData.addDescriptor(clientConfig);
    //Couplage du service avec la caractéristique créée.
    QLowEnergyServiceData serviceData;
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(QBluetoothUuid::HeartRate);
    serviceData.addCharacteristic(charData);


    //Création de la charactéristique
    QLowEnergyCharacteristicData charTemperature;
    //spécification de la caractéristique voulue
    charTemperature.setUuid(QBluetoothUuid::TemperatureMeasurement);
    charTemperature.setValue(QByteArray(2, 0));
    //spécifique à la documentation bluetooth
    charTemperature.setProperties(QLowEnergyCharacteristic::Indicate);
    //Ajout d'un descripteur
    const QLowEnergyDescriptorData clientConfigTemp(QBluetoothUuid::ClientCharacteristicConfiguration,  QByteArray(2, 0));
    charTemperature.addDescriptor(clientConfigTemp);
    //Couplage du service avec la caractéristique créée.
    QLowEnergyServiceData serviceTemperatureData;
    serviceTemperatureData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceTemperatureData.setUuid(QBluetoothUuid::HealthThermometer);
    serviceTemperatureData.addCharacteristic(charTemperature);

    //advertise
    const QScopedPointer<QLowEnergyController> leController(QLowEnergyController::createPeripheral());
    const QScopedPointer<QLowEnergyService> service(leController->addService(serviceData));
    const QScopedPointer<QLowEnergyService> serviceTemperature(leController->addService(serviceTemperatureData));

    leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData, advertisingData);

	 /**
     * HEARTBEAT
     */
    QTimer heartbeatTimer;
    quint8 currentHeartRate = 60;
    enum ValueChange { ValueUp, ValueDown } valueChange = ValueUp;
    const auto heartbeatProvider = [&service, &currentHeartRate, &leController, &advertisingData, &valueChange]() {
        QByteArray value;
        value.append(char(0)); // Flags that specify the format of the value.
        value.append(char(currentHeartRate)); // Actual value.
        QLowEnergyCharacteristic characteristic = service->characteristic(QBluetoothUuid::HeartRateMeasurement);
        Q_ASSERT(characteristic.isValid());
        service->writeCharacteristic(characteristic, value); // Potentially causes notification.
        if (currentHeartRate == 60)
            valueChange = ValueUp;
        else if (currentHeartRate == 100)
            valueChange = ValueDown;
        if (valueChange == ValueUp)
            ++currentHeartRate;
        else
            --currentHeartRate;         
            
        //Permet le relancement de l'advitising si le client s'est déconnecté
        if (leController.data()->state() == QLowEnergyController::UnconnectedState)
            leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData, advertisingData);
    };
    QObject::connect(&heartbeatTimer, &QTimer::timeout, heartbeatProvider);
    heartbeatTimer.start(1000);

    /**
     * TEMPERATURE
     */
    QTimer tempTimer;   //création d'un timer
    const auto tempProvider = [&serviceTemperature]() { //boucle d'évenement

        QString temp = readValueFromFile("/sys/bus/w1/devices/28-000008cd2c5c/w1_slave");
        
        float data = temp.toInt() / 1000.0;

        float temperature = data;

        //Conversion vers la norme IEEE 11073
        quint32 dataToSend = float754tofloat11073(temperature);

        //Création de la donnée
        QByteArray value;
        value.append(char(0)); // Flags spécifiant le format de la valeur

        //Stockage du quint32 dans un QByteArray
        value.append(reinterpret_cast<const char*>(&dataToSend), sizeof(dataToSend)); // Valeur à envoyer

        // récupération de la caratéristique du service
        QLowEnergyCharacteristic characteristic = serviceTemperature->characteristic(QBluetoothUuid::TemperatureMeasurement);
        Q_ASSERT(characteristic.isValid());

        //mise à jour de la donnée
        serviceTemperature->writeCharacteristic(characteristic, value); // Potentially causes notification.
    };
    //démarrage du timer
    QObject::connect(&tempTimer, &QTimer::timeout, tempProvider);
    tempTimer.start(10000);


    return a.exec();
}

