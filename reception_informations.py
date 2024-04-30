#Groupe : Maxim, Manon, Alexandre, Martin

import paho.mqtt.client as mqtt
import turtle
import json

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, "le groupe des bg")
client.connect("srv-lora.isep.fr")
turtle.penup()


def on_message_callback(client_inst, userdata, message):
    print(message.payload)
    try:
        data = json.loads(message.payload)
    except json.JSONDecodeError as e:
        print(f"Erreur JSON - {e}")
        return

    if "objet" in data and "message" in data["objet"]:
        message_content = data["objet"]["message"]

        if message_content.startswith("Koba"):
            parts = message_content.split(":")
            if len(parts) == 3:
                name, x, y = parts
                try:
                    turtle.goto(int(x), int(y))
                    turtle.dot(10, 'blue')
                    if int(x) > 200:
                        print("Koba sort de la zone")
                    if int(x) < -200:
                        print("Koba sort de la zone")
                    if int(y) > 200:
                        print("Koba sort de la zone")
                    if int(y) < -200:
                        print("Koba sort de la zone")
                except ValueError as e:
                    print(f"Erreur de déplacement - {e}")



        elif message_content.startswith("Ninho"):
            parts = message_content.split(":")
            if len(parts) == 3:
                name, x, y = parts
                try:
                    turtle.goto(int(x), int(y))
                    turtle.dot(10, 'pink')
                    if int(x) > 200:
                        print("Ninho sort de la zone")
                    if int(x) < -200:
                        print("Ninho sort de la zone")
                    if int(y) > 200:
                        print("Ninho sort de la zone")
                    if int(y) < -200:
                        print("Ninho sort de la zone")
                except ValueError as e:
                    print(f"Erreur de déplacement - {e}")


        elif message_content.startswith("Tiakola"):
            parts = message_content.split(":")
            if len(parts) == 3:
                name, x, y = parts
                try:
                    turtle.goto(int(x), int(y))
                    turtle.dot(10, 'black')
                    if int(x) > 200:
                        print("Tiakola sort de la zone")
                    if int(x) < -200:
                        print("Tiakola sort de la zone")
                    if int(y) > 200:
                        print("Tiakola sort de la zone")
                    if int(y) < -200:
                        print("Tiakola sort de la zone")
                except ValueError as e:
                    print(f"Erreur de déplacement - {e}")
    else:
        print("Message JSON invalide")


client.on_message = on_message_callback
client.subscribe("#")
client.loop_start()
turtle.mainloop()

