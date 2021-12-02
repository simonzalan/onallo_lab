import socket
from datetime import datetime
import requests
import json


# a history lista átlagolásához használt függvény (összes elem összege)/(lista hossza)
def avg_list(lst):
    return sum(lst) / len(lst)


# a cím, amin a blokklánc fut
url = 'http://vm.smallville.cloud.bme.hu:20999'
headers = {'Content-type': 'application/json'}

s = socket.socket()
s.bind(('0.0.0.0', 8090))  # a 8090-es porton nyitunk egy socketet, amire az ESP az adatokat küldi
s.listen(0)

history = []

while True:
    client, addr = s.accept()
    while True:
        content = client.recv(32)
        if len(content) == 0:
            break
        else:
            # az ESP-ről érkező adatokat b'xxxx' formátumban kapjuk meg
            sensorData = int(content)
            print(str(datetime.now()) + ": " + str(sensorData))
            history.append(sensorData)

        # a szerződés felé küldés akkor történik, ha 5 perc mérési anyagát összegyűjtöttem
        # minden küldés után újabb 5 perc mérési eredményeit kezdem el gyűjteni
        if len(history) == 60:  # 5 másodpercenként küldünk adatot, 5 percen keresztül, utána ezeket átlagoljuk
            my_data = "0xa81ccdc50000000000000000000000000000000000000000000000000000000000"  # az átadni kívánt
                                                                                              # érték 6 karakterrel kevesebb, mint 64
            avg = avg_list(history)
            hex_form = str(hex(int(avg)))[2:]  # az átlag hexadecimális formában 0x kezdet nélkül
            print("Average is: " + str(avg) + " and hex is: " + hex_form)

            add = hex_form  # hex_form legfeljebb 4 hosszúságú lehet a szenzor által küldött értékek értékkészlete miatt
            while len(add) != 6:  # 0-kal egészítem ki az elején, amíg nem 6 karakter hosszú
                add = "0" + add

            my_data = my_data + add
            print("my_data: " + my_data + " and length is: " + str(len(my_data)))

            # modify tartalmazza az elküldeni kívánt adatokat JSON formátumban
            # a "from" és "to" mezőket minden alkalommal változtatni kell,
            # amikor a Remix-en belül újra futtatjuk a szerződést
            modify = {"jsonrpc": "2.0", "method": "eth_sendTransaction", "params": [
                {"from": "",
                 "to": "",
                 "data": my_data}], "id": 420}

            # request kérést küldünk a szerződés felé
            r = requests.post(url, data=json.dumps(modify), headers=headers)
            print(r)
            print(r.content)

            history = []  # miután elküldtem az átlagot, history listát kiürítem

    client.close()
