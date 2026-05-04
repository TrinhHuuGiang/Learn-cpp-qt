Qt support some **QIODevice** sub classes:
- Random access data
    - **QFile**: Accesses files in the local file system and in embedded resources
        - QFileInfo classes, which handle directories and provide information about the
        files inside them
        - QIODevice::seek() function for repositioning the file pointer.
    - **QTemporaryFile**: Creates and accesses temporary files in the local file system
    - **QBuffer**: Reads data from or writes data to a QByteArray
    - **QDataStream**
    - **QTextStream**
- sequential transmission
    - **QProcess**: Runs external programs and handles inter-process communication
        -  launch external programs and to communicate
        with them through their standard input, standard output, and standard error
        channels (cin, cout, and cerr).
    - **QTcpSocket**: Transfers a stream of data over the network using TCP
    - **QUdpSocket**: Sends or receives UDP datagrams over the network

---

## Content


---

