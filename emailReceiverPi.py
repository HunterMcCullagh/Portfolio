# emailReceiverPi
# Jan 17, 2021
# Hunter McCullagh
# This code is meant for a raspberry Pi
# The following code will turn an LED on and off
# when there are emails with the subject line 'ON' and 'OFF' received

import smtplib             # Import Libraries to use gmail
import time
import imaplib
import email
import traceback
import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
from time import sleep     # Import the sleep function from the time module
GPIO.setwarnings(False)    # Ignore warning for now
GPIO.setmode(GPIO.BOARD)   # Use physical pin numbering
GPIO.setup(8, GPIO.OUT, initial=GPIO.LOW)

ORG_EMAIL = "@gmail.com"
FROM_EMAIL = "myEmail" + ORG_EMAIL
FROM_PWD = "myPassword"
SMTP_SERVER = "imap.gmail.com"
SMTP_PORT = 993

def read_email_from_gmail():
    try:
        mail = imaplib.IMAP4_SSL(SMTP_SERVER)
        mail.login(FROM_EMAIL,FROM_PWD)
        mail.select('inbox')

        data = mail.search(None, 'ALL')
        mail_ids = data[1]
        id_list = mail_ids[0].split()
        first_email_id = int(id_list[0])
        latest_email_id = int(id_list[-1])

        for i in range(latest_email_id,first_email_id, -1):
            data = mail.fetch(str(i), '(RFC822)' )
            for response_part in data:
                arr = response_part[0]
                if isinstance(arr, tuple):
                    msg = email.message_from_string(str(arr[1],'utf-8'))
                    email_subject = msg['subject']
                    email_from = msg['from']

                    if email_subject == 'ON':
                        GPIO.output(8, GPIO.HIGH)
                    elif email_subject == 'OFF':
                        GPIO.output(8, GPIO.LOW)


    except Exception as e:
        traceback.print_exc()
        print(str(e))

read_email_from_gmail()
