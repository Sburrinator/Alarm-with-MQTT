import mysql.connector
import time
import paho.mqtt.client as paho
from mysql.connector import Error
import smtplib
from email.mime.text import MIMEText



subject = "Allarme"     # email description
body = "Intrusi rilevati"
sender = "email that you use to send"
recipients = ["email reciver"]
password = "dsax rpai mknr lrjw" # check out some videos on how to use gmail as a SMTP server


# function to send the email
def send_email(subject, body, sender, recipients, password):
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = ', '.join(recipients)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp_server:
       smtp_server.login(sender, password)
       smtp_server.sendmail(sender, recipients, msg.as_string())
    print("Email inviata!")


#
def tastierinoInserisceDatabase(condizione):
    try:
        # Connessione al database MySQL
        connection = mysql.connector.connect(
            host='localhost',
            database='sicurezza',
            user='sicurezza',
            password='hamzamihali123'
        )

        if connection.is_connected():
            cursor = connection.cursor()
            # Query per ottenere l'ultimo stato dell'allarme
            if condizione == "on":
                query = """
                    INSERT INTO  iot(ID_ultimostato, stato_allarme, utente_richiesta, log, ip) 
                    VALUES (null, true, 'admin', null, 'localhost')
                """
            elif condizione == "off":
                query = """
                    INSERT INTO  iot(ID_ultimostato, stato_allarme, utente_richiesta, log, ip) 
                    VALUES (null, false, 'admin', null, 'localhost')
                """
            
            cursor.execute(query)
            connection.commit()
    except Error as e:
        print(f"Errore durante la connessione al database: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
          


# Funzione per ottenere l'ultimo stato dell'allarme dal database
def ultimoAccessostatoAllarme():
    value = False
    try:
        # Connessione al database MySQL
        connection = mysql.connector.connect(
            host='localhost',
            database='sicurezza',
            user='sicurezza',
            password='hamzamihali123'
        )

        if connection.is_connected():
            cursor = connection.cursor()
            # Query per ottenere l'ultimo stato dell'allarme
            query = """
                SELECT stato_allarme
                FROM iot
                WHERE ID_ultimostato = (SELECT MAX(ID_ultimostato) FROM iot);
            """
            cursor.execute(query)
            results = cursor.fetchall()

            for result in results:
                value = result[0]   #Inserisce all'interno della variabile 'value' il risultato della query

    except Error as e:
        print(f"Errore durante la connessione al database: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
    return value

# Funzione di callback per la gestione dei messaggi MQTT in arrivo
def onMessage(cliente, userdata, msg):
    messaggio = str(msg.payload.decode())
    if messaggio == "connesso":
        print("Tastierino connesso")
    elif messaggio=="on":
        tastierinoInserisceDatabase(messaggio)
        messaggio=""
        print(f"Tastierino accende allarme")
    elif messaggio=="off":
        tastierinoInserisceDatabase(messaggio)
        messaggio=""
        print(f"Tastierino spegne allarme")
    elif ultimoAccessostatoAllarme():
        if messaggio == "rilevato":
            client.publish("allarme/output", "on")
            print(f"Intruso rilevato")
            send_email(subject, body, sender, recipients, password)
        else:
            client.publish("allarme/output", "off")
            print(f"Nessun intruso")

####################################################################################
def onConnect(client, userdata, flags, rc):
    print(f"Connesso con il codice di risultato {rc}")
    for topic, qos in topics2:
        client.subscribe(topic, qos)
        print(f"Sottoscritto al topic: {topic} con QoS {qos}")
####################################################################################



# ID del client MQTT
id = "Ciao"
client = paho.Client(paho.CallbackAPIVersion.VERSION1, id)
#client.on_connect = onConnect
client.on_message = onMessage
# Connessione al broker MQTT
if client.connect("localhost", 1883, 60) != 0:
    print("no")
    sys.exit(-1)


####################################################################################
# Sottoscrizione topics "allarme/sensore","allarme/movimento","allarme/tastierino"
client.subscribe([("allarme/movimento1", 2), ("allarme/movimento2", 2), ("allarme/movimento3", 2), ("allarme/tastierino", 2)])#qos qualita del servizio,0 una volta non sicuro,1 duplicati se non arriva ack,2 arriva sicuro e una volta(handshake)

# Attesa di mezzo secondo
time.sleep(0.5)

# Loop principale per mantenere il client MQTT in esecuzione
try:
    print("Premi CTRL+C per terminare il programma")
    client.loop_forever()
except:
    print("Terminato, arrivederci!")

client.disconnect()
